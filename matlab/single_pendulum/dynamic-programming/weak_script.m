filename = '../lib/weak_cost_network.mat';
addpath ../lib                                 
xd  = [pi 0];
time = 0.05;                                 
anglerange = [0,2*pi];                         
speedrange = [-10,10];                         
torquerange = [-1.5,1.5];
angles = 300;
speeds = 300;
torques = 20;
goal = [151,151];


save(filename,...
	'time','anglerange','speedrange',...
	'torquerange','angles','speeds',...
	'goal');
total_time = tic;

disp('Generating Network')
generate_network
disp('Finished Generating Network')

clearvars -except filename
load(filename)

disp('Generating Network Connections')
generate_network_connections
disp('Finished Generating Network Connections')

clearvars -except filename
load(filename)

disp('Evaluating Network Connections')
evaluate_connections
disp('Finished Evaluating Network Connections')


total_time = seconds(toc(total_time));
total_time.Format = 'hh:mm:ss.sss'

