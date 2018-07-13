addpath ./matlab_torso_dynamics ../single_pendulum/lib
N = 40;
M = 20;
P = 15;
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
% A = network_template(N,M,P);

% enter the desired state of the system
zd = [0 -2.76 0 0];
tic
parfor i = 1:N
    for j = 1:M
        for k = 1:P
            for T = torque_arr
                warning('off','all')
                parms = get_parms;
                parms.control.T2 = T;
                q1 = 0;%angle should always be zero
                u1 = velocity_arr(j);%mid-stance velocity 
                q2 = body_angle_arr(i); %parms.control.q2;
                u2 = body_angle_rate_arr(k);
                z0 = [q1 u1 q2 u2];% [angle rate];
                [z,t,thetadotmid,Avg_Velocity,error_flag] = ...
                    onestep(z0, parms, 1);
                A{i,j,k}.ID = [i j k];
                A{i,j,k}.state = [velocity_arr(i) body_angle_arr(j) body_angle_rate_arr(k)];
                if z0 ~= z | error_flag 
                    continue;
                end
                if (    z(2) > max(velocity_arr) || z(2) < min(velocity_arr) ||...
                        z(3) > max(body_angle_arr) || z(3) < min(body_angle_arr) ||...
                        z(4) > max(body_angle_rate_arr) || z(4) < min(body_angle_rate_arr))
                    continue;
                end
                [z(2), n] = nearest2(z(2), velocity_arr);
                [z(3), m] = nearest2(z(3), body_angle_arr); 
                [z(4), p] = nearest2(z(4), body_angle_rate_arr);
                J = cost(z, zd, T, t);
                if isempty(A{i,j,k}.connections)
                    A{i,j,k}.connections{1} = [n m p T J];
                else
                    conn = compare_connections(A{i,j,k}.connections, [n m p T J]);
                    if conn
                        A{i,j,k}.connections{conn} = [n m p T J];
                    end
                end
            end
        end
    end
end
t = toc
save('parallel_network_test.mat','t','A')
%% extra functions 
function J = cost(state, state_plus_one, input_signal, time)
err = state - state_plus_one;
err = err([2 4]);

% gain parameters
state_error_gain = 1;
input_signal_gain = 1;
time_gain =1;

% calculate individual cost
state_cost = dot(err,err)*state_error_gain;
input_cost = input_signal^2*input_signal_gain;
time_cost  = time^2*time_gain;

% sum the individual cost to produce the total cost J
J = state_cost + input_cost + time_cost;
end
function network = network_template(N,M,P)
network = cell(N,M,P);
network(:,:,:) = {nNode};
end

function vec = vecof(values,N)
vec = values(1):diff(values)/N:values(2);
end

function [val, n] = nearest2(val,arr)
vec = abs(arr - val);
[val,n] = min(vec);
val = arr(val == vec);
end

function n = compare_connections(connections, connection)
for i = 1:length(connections)
    if connection(1:3) == connections{i}(1:3)
        if connection(4) < connections{i}(4)
            return;
        else
            n = 0;
            return
        end
    end
end
end