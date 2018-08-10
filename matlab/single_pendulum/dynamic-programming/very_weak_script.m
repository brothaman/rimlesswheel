filename = '../lib/very_weak_cost_network.mat';
addpath ../lib                                 
xd  = [pi 0];
time = 0.05;                                 
anglerange = [0,2*pi];                         
speedrange = [-10,10];                         
torquerange = [-1,1];
angles = 300;
speeds = 300;
torques = 20;
goal = [151,151];

total_time = tic;


disp('Generating Network')
generate_network
disp('Finished Generating Network')

disp('Generating Network Connections')
generate_network_connections
disp('Finished Generating Network Connections')

disp('Evaluating Network Connections')
evaluate_connections
disp('Finished Evaluating Network Connections')


total_time = seconds(toc(total_time));
total_time.Format = 'hh:mm:ss.sss'
