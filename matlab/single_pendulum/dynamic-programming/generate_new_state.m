function X = generate_new_state( Xin, Xd, torque, time, anglerange, speedrange, torquerange)
%% GENERATE_NEW_STATE 
%   uses a combination of the xnplusone and cost functions to generate the
%   next state storing the input signal and the cost of transition 

% there are some things we must avoid is repeated state connections as this
% will cause infinite loop recursion
% another scenario to lookout for is the if the state give a connection
% back to itself. 
global NODES
% use xnplus 1 to generate a new state and store it in to the global
% variable NODES
% if X is the same then dont save the state/input signal combo
%% ------------------ discretizations --------------------------- %%
angleresolution = 0.01;
speedresolution = 0.01;
torqueresolution = 1;
nangles = 100;
nspeeds = 200;
ntorques =20;
[Xin(1), mstate] = map(Xin(1),anglerange, nangles);
[Xin(2), nstate] = map(Xin(2),speedrange, nspeeds);
torque = map(torque,torquerange, ntorques);
%% ------------------ discretizations --------------------------- %%

torque = round(torque, 1);
[t,X] = xnplusone(0,Xin,torque,'StepSize',time,...
        'AngleResolution', angleresolution,...
        'SpeedResolution', speedresolution,...
        'TorqueResolution', torqueresolution);
[X(1), mnextstate] = map(X(1), anglerange, nangles);
[X(2), nnextstate] = map(X(2), speedrange, nspeeds);
% if the next state matches the current state then skip this and forgo any
% further computation
if max( Xin ~= X)
    J = cost(Xd,Xin,X,torque);
    % if the currents state's state values haven't been set then do so here
    if isempty(NODES{mstate,nstate}.state)
        NODES{mstate,nstate}.state = Xin; 
    end
    % check each of the connections to see if one to the same state already
    % exist
    for i = 1:length(NODES{mstate,nstate}.connections)
        if NODES{mstate,nstate}.connections{i}(1:2) == [mnextstate, nnextstate]
             % now check if the cost is lower
             if NODES{mstate,nstate}.connections{i}(4) > J
                 % if so swap out the torque and cost and break the loop
                  NODES{mstate,nstate}.connections{i}(3:4) = [torque, J];
             end
             % whether or not the cost is lower or higher there should be
             % any more connections with the same state so break the loop
             % to prevent unnecessary computation and runtime
             return;
             % this additional logic reduced the network memory used to 
        end
    end
    NODES{mstate,nstate}.connections{end+1} = [ mnextstate, nnextstate, torque, J];
end
end