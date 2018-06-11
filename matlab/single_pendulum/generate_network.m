%% generate all possible states and state transitions
clear all
global NODES

Xin = [0 0];
Xd  = [pi 0];
torque = 1;
time = 0.05;

anglerange = [0,2*pi];
speedrange = [-6,6];
torquerange = [-10,10];

all_angles = [0:diff(anglerange)/100:2*pi];
all_speeds = [-6:12/200:6];
initialize_NODES(length(all_angles), length(all_speeds));

for torque = -10:1:10
    % generate new state
    for x1 = all_angles
        for x2 = all_speeds
            [Xin] = generate_new_state( Xin, Xd, torque, time,...
                anglerange, speedrange, torquerange);
            pause
        end
        pause
    end
end