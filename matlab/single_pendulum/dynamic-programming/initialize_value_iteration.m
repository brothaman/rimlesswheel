% script to initialize value iteration and set the workspace environment
clear all
global NODES 
load lib/cost_network_v0.1.mat 
m = 51; n = 101; % the goal
NODES{m,n}.optimal_value = 0;
i = 1;
[m,n,connections] = network_search(m,n);