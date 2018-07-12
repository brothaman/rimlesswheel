%% Begin by generating the cost network with a predetermined size
addpath ./matlab_torso_dynamics ../single_pendulum/lib
warning('off','all')
N = 40;
M = 20;
P = 10;
torque_range = [-10 10];
velocity_range = [-2.76 0];
body_angle_range = [0 pi/2];
body_angle_rate_range = [-6 6];

% set up arrays of values
torque_arr = vecof(torque_range, 20); % N*m
velocity_arr = vecof(velocity_range, N);
body_angle_arr = vecof(body_angle_range, M); % possibly going to change
body_angle_rate_arr = vecof(body_angle_rate_range, P);

% generate the network template
N = length(velocity_arr);
M = length(body_angle_arr);
P = length(body_angle_rate_arr);
network = network_template(N,M,P);
parms = get_parms;
xd = [0 -2.76 0 0];
%% populate the network with cost
global costs count
costs = zeros(N*M*P*length(torque_range), 3);
count = 1;
generate_cost_network(...
    network, torque_arr,...
    body_angle_arr, velocity_arr, body_angle_rate_arr,...
    parms, N, M, P, xd);
save('details.mat','costs')
exit
%% extra functions 
function network = network_template(N,M,P)
network = cell(N,M,P);
network(:,:,:) = {nNode};
end

function vec = vecof(values,N)
vec = values(1):diff(values)/N:values(2);
end
