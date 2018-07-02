%% unit test for the function value iteration
clear all
close all
clc

load ../lib/costnetwork_xd_equal_-1.5_26_Jun_2018.mat
count = 0;
N = 100;
iterations = 1:10;

% set the goal
[val, goal] = map(-1.5,[-2.76,0],N);

% set the goals optimal value this may be changed if i have enough time to
% work it in to my day
network{goal}.optimal_value = 0;


conn = network_search(goal,N);

for i = iterations
    [conn, count] = value_iteration(conn, count);
end