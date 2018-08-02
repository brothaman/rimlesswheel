% this script drive from a state where an optimal path is known to the goal
% state
clear all
close all
addpath ../lib/
load ../lib/cost_network.mat

time = 0.05;
xd  = [pi 0];
phi = -pi/2;

t = 0;
tf = 3;
x = [.75*pi 6];
[x(1),n] = nearest2(x(1),all_angles);
[x(2),m] = nearest2(x(2),all_speeds);
goalnotmet = true;
txs = [0,0,0];
xd = [pi,0];
xd(1) = nearest2(xd(1),all_angles);
xd(2) = nearest2(xd(2),all_speeds);
P = {};

clear taus
taus = 0;
qactual = [];
% driver signal
while max(t) < tf
    torque = get_control_signal(network,n,m);
    taus(end+1) = torque;
    [~,x] = xnplusone(x,torque,time);
    txs(end+1,:) = [t,x];
    % map variables back over
    [x(1),n] = nearest2(x(1),all_angles);
    [x(2),m] = nearest2(x(2),all_speeds);
    P{end+1} = {1*[0 0 cos(x(1)+phi) sin(x(1)+phi)]};
    if (x == xd)
        goalnotmet = false;
    end
    t = t + time;
    if(goalnotmet)
        qactual(end+1,:) = x;
    end
end

% plot value function and policy. 
%% animate the pendulum
fig = figure;
axis([-2 2 -2 2]);
phandle = [];
xlabel('meters')
ylabel('meters')

for i = 1:length(P)
    [fig,phandle] = show_pendulum(fig,phandle,P{i});
    pause(0.03);
end
% plot the torque over time
fig2 = figure;
plot(txs(:,1),taus)
%% functions
function [val, n] = nearest2(val,arr)                                                                                                                                                                       
vec = abs(arr - val);                                                                                                                                                                                       
[val,n] = min(vec);                                                                                                                                                                                         
val = arr(val == vec);                                                                                                                                                                                      
end

function [torque] = get_control_signal(network, n,m)
    torque = network{n,m}.connections{network{n,m}.optimal_policy}(3);
end