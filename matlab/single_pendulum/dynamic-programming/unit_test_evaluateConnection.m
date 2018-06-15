%% unit-test for evaluate connections
clear all
addpath('../lib')
global NODES
load('../lib/cost_network.mat')
m = 10;
n = 10;

% check to make sure the numeric functionality is working
connection = 1;
evaluateConnection(m,n,connection)
NODES{n,m}

% validate the array functionality
connection = NODES{n,m}.connections{1};
evaluateConnection(m,n,connection)
NODES{n,m}