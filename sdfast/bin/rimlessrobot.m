%% Robert Brothers
% the input for this function are:
% - time  (t)
% - state (check sd_i for state information)
% - dstate
% - torques ( the torques applies are [left_wheel_torque right_wheel_torque]
clear
close all

% number iterations
N = 1;

% number of state variables
nstate = 17; 

% initial state and state velocities are set at zero
state = zeros(nstate,1);
dstate = state;
state_history=zeros(nstate,N);
 
% time vector is composed of the [(current time)  (delta time)]
t = [0 5e-3];

% torques input are the leftwheel and right wheel
torques = [0 0];
anidata = {};

% loop and save the state and reaction torque information
for i = 1:N
    [t,state,dstate,rxnt,bangles,anidata] = mexsim(t,state,dstate,torques,anidata);
		generate_data(anidata);
    state_history(:,i) = state;
end

t = 0:t(2):t(1);
% plot(t,state_history(17,:))
