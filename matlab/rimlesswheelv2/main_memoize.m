%% Begin by generating the cost network with a predetermined size
addpath ./matlab_torso_dynamics ../single_pendulum/lib
N = 100;
M = 100;
P = 100;
torque_range = [0 10];
velocity_range = [0 2*pi];
body_angle_range = [0 pi/2];
body_angle_rate_range = [-6 6];

% set up arrays of values
torque_arr = vecof(torque_range, 20); % N*m
body_angle_arr = vecof(body_angle_range, N); % possibly going to change
velocity_arr = vecof(velocity_range, M);
body_angle_rate_arr = vecof(body_angle_rate_range, P);

% generate the network template
N = length(body_angle_arr);
M = length(velocity_arr);
P = length(body_angle_rate_arr);
network = network_template(N,M,P);
parms = get_parms;

%% populate the network with cost
generate_cost_network(...
    network, torque_range,...
    body_angle_range, velocity_range, body_angle_rate_range,...
    parms, N, M, P);

%% extra functions 
function network = network_template(N,M,P)
network = cell(N,M,P);
netowrk(:,:,:) = {nNode};
end

function vec = vecof(values,N)
vec = values(1):diff(values)/N:values(2);
end