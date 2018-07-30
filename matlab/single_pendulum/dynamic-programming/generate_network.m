%% generate all possible states and state transitions
N = maxNumCompThreads;
p = gcp('nocreate'); % If no pool, do not create new one.
if isempty(p)
    poolsize = 0;
    m = parcluster;
    m.NumWorkers = N;
    p = parpool(N);
else 
    poolsize = p.NumWorkers;
    if poolsize < N
        delete(gcp('nocreate'));
        m = parcluster;
        m.NumWorkers = N;
        parpool(N)
    end
end

[xd,time,anglerange,speedrange,torquerange,filename] = very_weak_actuation_init();

angles = 100;
speeds = 200;
torques = 100;

all_angles = min(anglerange):diff(anglerange)/angles:max(anglerange);
all_speeds = min(speedrange):diff(speedrange)/speeds:max(speedrange);
all_torques= min(torquerange):diff(torquerange)/torques:max(torquerange);

nodes = initialize_nodes(all_angles, all_speeds);
new_nodes = cell(length(all_angles), length(all_speeds));
parfor i = 1:length(all_angles)
    node = cell(1,length(all_speeds));
    for j = 1:length(all_speeds)
        node{j} = nodes{i,j};
        for torque = all_torques
            node{j} = generate_new_state(node{j},xd,torque,time,all_angles,all_speeds);
        end
    end
    new_nodes(i,:) = node;
end
network = new_nodes;
save(filename, 'network');
clearvars
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
        node.connections{1} = [n m torque J];
        return
    end
    for i = 1:22
        if i > length(node.connections)
            node.connections{i} = [n m torque J];
            return
        end
        if node.connections{i}(1:2) == [n m]
            if node.connections{i}(4) > J
                node.connections{i} = [n m torque J];
            end
            return
        else
        end
    end
end

function J = getcost(x, xd, torque)
    Qx = [1/pi^2 0; 0 1/36];
    ka = 1/100;
    state_error = (x-xd)*Qx*( x-xd)';
    input_error = torque^2 * ka;
    time_error = 1;
    J = state_error + input_error + time_error;
end

function [val, n] = nearest2(val,arr)                                                                                                                                                                       
vec = abs(arr - val);                                                                                                                                                                                       
[val,n] = min(vec);                                                                                                                                                                                         
val = arr(val == vec);                                                                                                                                                                                      
end  

function [xd,time,anglerange,speedrange,torquerange,filename] = standard_init()
    clear
    addpath ../lib
    xd  = [pi 0];
    time = 0.05;

    anglerange = [0,2*pi];
    speedrange = [-6,6];
    torquerange = [-10,10];
    filename = '../lib/cost_network.mat';
end

function [xd,time,anglerange,speedrange,torquerange,filename] = underactuated_init()
    clear
    addpath ../lib
    xd  = [pi 0];
    time = 0.05;

    anglerange = [0,2*pi];
    speedrange = [-6,6];
    torquerange = [-5,5];
    filename = '../lib/underactuated_cost_network.mat';
end

function [xd,time,anglerange,speedrange,torquerange,filename] = very_weak_actuation_init()
    clear
    addpath ../lib
    xd  = [pi 0];
    time = 0.05;

    anglerange = [0,2*pi];
    speedrange = [-6,6];
    torquerange = [-1,1];
    filename = '../lib/very_weak_cost_network.mat';
end