%% generate all possible states and state transitions
addpath ../lib
xd  = [pi 0];
torque = 1;
time = 0.05;

anglerange = [0,2*pi];
speedrange = [-6,6];
torquerange = [-10,10];

all_angles = [0:diff(anglerange)/100:2*pi];
all_speeds = [-6:12/200:6];
all_torques= [-10:1:10];

nodes = initialize_nodes(all_angles, all_speeds);
parfor i = 1:length(all_angles)
    for j = 1:length(all_speeds)
        node = nodes{i,j};
        for torque = all_torques
            node = generate_new_state(node,xd,torque,time,all_angles,all_speeds);
        end
%         new_nodes{i,j} = node;
    end
end
% save('lib/cost_network_v0.1.mat', 'NODES');

%% functions
function nodes = initialize_nodes(angles,speeds)
    n = length(angles);
    m = length(speeds);
    nodes = cell(n,m);
    nodes(:) = {nNode};
    for i = 1:n
        for j = 1:m
            nodes{i,j}.ID = [i,j];
            nodes{i,j}.state = [angles(i) speeds(j)];
        end
    end
end

function node = generate_new_state(node,xd,torque,time,angles,speeds)
    x = [angles(node.ID(1)) speeds(node.ID(2))];
    upper_angle = max(angles);
    upper_speed = max(speeds);
    lower_angle = min(angles);
    lower_speed = min(speeds);
    [~,xx] = xnplusone(x,torque,time);
    % make sure its not the same
    if xx == x
        return
    end
    
    % make sure the value is with in range
    if ( xx(1)>upper_angle || xx(2) > upper_speed || ...
            xx(1)<lower_angle || xx(2) < lower_speed)
        return
    end
    [xx(1), n] = nearest2(xx(1), angles);
    [xx(2), m] = nearest2(xx(2), speeds);
    J = getcost(xx, xd, torque);
    if isempty(node.connections)
        node.connections{1} = [xx torque J];
        return
    end
    for i = 1:22
        if i > length(node.connections)
            node.connections{i+1} = [xx torque J];
            return
        end
        if node.connections{i}(1:2) == xx
            if node.connections{i}(4) > J
                node.connections{i} = [xx torque J];
            end
        else
            return
        end
    end
end

function J = getcost(x, xd, torque)
    kx = 1;
    ka = 1;
    state_error = dot(x-xd, x-xd) * kx;
    input_error = torque^2 * ka;
    J = state_error + input_error;
end

function [val, n] = nearest2(val,arr)                                                                                                                                                                       
vec = abs(arr - val);                                                                                                                                                                                       
[val,n] = min(vec);                                                                                                                                                                                         
val = arr(val == vec);                                                                                                                                                                                      
end  
% function X = generate_new_state( Xin, Xd, torque, time, anglerange, speedrange, torquerange)
% %   uses a combination of the xnplusone and cost functions to generate the
% %   next state storing the input signal and the cost of transition 
% 
% % there are some things we must avoid is repeated state connections as this
% % will cause infinite loop recursion
% % another scenario to lookout for is the if the state give a connection
% % back to itself. 
% global NODES
% % use xnplus 1 to generate a new state and store it in to the global
% % variable NODES
% % if X is the same then dont save the state/input signal combo
% % ------------------ discretizations --------------------------- %%
% angleresolution = 0.01;
% speedresolution = 0.01;
% torqueresolution = 1;
% nangles = 100;
% nspeeds = 200;
% ntorques =20;
% [Xin(1), mstate] = map(Xin(1),anglerange, nangles);
% [Xin(2), nstate] = map(Xin(2),speedrange, nspeeds);
% torque = map(torque,torquerange, ntorques);
% % ------------------ discretizations --------------------------- %%
% 
% torque = round(torque, 1);
% [t,X] = xnplusone(0,Xin,torque,'StepSize',time,...
%         'AngleResolution', angleresolution,...
%         'SpeedResolution', speedresolution,...
%         'TorqueResolution', torqueresolution);
% [X(1), mnextstate] = map(X(1), anglerange, nangles);
% [X(2), nnextstate] = map(X(2), speedrange, nspeeds);
% % if the next state matches the current state then skip this and forgo any
% % further computation
% if max( Xin ~= X)
%     J = cost(Xd,Xin,X,torque);
%     % if the currents state's state values haven't been set then do so here
%     if isempty(NODES{mstate,nstate}.state)
%         NODES{mstate,nstate}.state = Xin; 
%     end
%     % check each of the connections to see if one to the same state already
%     % exist
%     for i = 1:length(NODES{mstate,nstate}.connections)
%         if NODES{mstate,nstate}.connections{i}(1:2) == [mnextstate, nnextstate]
%              % now check if the cost is lower
%              if NODES{mstate,nstate}.connections{i}(4) > J
%                  % if so swap out the torque and cost and break the loop
%                   NODES{mstate,nstate}.connections{i}(3:4) = [torque, J];
%              end
%              % whether or not the cost is lower or higher there should be
%              % any more connections with the same state so break the loop
%              % to prevent unnecessary computation and runtime
%              return;
%              % this additional logic reduced the network memory used to 
%         end
%     end
%     NODES{mstate,nstate}.connections{end+1} = [ mnextstate, nnextstate, torque, J];
% end
% end