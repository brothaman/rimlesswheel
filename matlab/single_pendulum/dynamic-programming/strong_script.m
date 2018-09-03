maxNumCompThreads = 32;
filename = '../lib/strong_cost_network.mat';
addpath ../lib                                 
xd  = [pi 0];
time = 0.01;                                 
anglerange = [0,2*pi];                         
speedrange = [-6,6];                         
torquerange = [-10,10];
angles = 500;
speeds = 200;
torques = 200;
goal = [251,101];

%{
save(filename,...
	'time','anglerange','speedrange',...
	'torquerange','angles','speeds',...
	'goal');
total_time = tic;

disp('Generating Network')
generate_network
disp('Finished Generating Network')

clearvars -except filename total_time
load(filename)

disp('Generating Network Connections')
generate_network_connections
disp('Finished Generating Network Connections')
%}
save(filename,'goal','-append')

clearvars -except filename total_time
load(filename)

disp('Evaluating Network Connections')
N = sum(any(~cellfun('isempty',connections),2));
path = 'images/strong_pend/growth/';
if ~exist(path,'dir')
    mkdir(path)
end
for iter = 1:N
    evaluate_connections
    save(['../lib/strong_pend/strong_network_' int2str(iter) '.mat'],'network')
end
save(filename,'network','ids','previous_ids','-append');
disp('Finished Evaluating Network Connections')
total_time = seconds(toc(total_time));

disp('Generating plots')
for iter = 1:N
	load(['../lib/strong_pend/strong_network_' int2str(iter) '.mat'])
    figure_file_name = ['strong cost network iteration ' int2str(iter)];
    show_cost_network(figure_file_name, path, all_angles, all_speeds, network)
    close all
end
disp('Finished generating plots')
