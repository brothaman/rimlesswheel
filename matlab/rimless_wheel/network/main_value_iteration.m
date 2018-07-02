%% unit test for the function value iteration
clear all
close all
clc
addpath('../../single_pendulum/lib/')

val = -1.5;
count = 0;
N = 100;
iterations = 1:10;

% set the goal
goals = -2.76:0.1:0;
[val, goal] = map(val,[-2.76,0],N);
val = goals(min(abs(val - goals)) == abs(val - goals));
date = '_02_Jul_2018';
filename = strcat('../lib/DEBUGcostnetwork_xd_equal_',num2str(val),date,'.mat');
load(filename)


% set the goals optimal value this may be changed if i have enough time to
% work it in to my day
network{goal}.optimal_value = 0;


conn = network_search(goal,N);

for i = iterations
    [conn, count] = value_iteration(conn, count);
end