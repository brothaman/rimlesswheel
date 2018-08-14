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

clearvars -except filename total_time
load(filename)

disp('Evaluating Network Connections')
N = sum(any(~cellfun('isempty',connections),2));
path = 'images/very_weak_pend/growth/';
if ~exist(path,'dir')
    mkdir(path)
end
for iter = 1:N
    evaluate_connections
    save(['../lib/very_weak_pend/very_weak_network_' int2str(iter) '.mat'],'network')
    figure_file_name = ['very weak cost network iteration ' int2str(iter)];
    show_cost_network(figure_file_name, path, all_angles, all_speeds, network)
    close all
end
save(filename,'network','ids','previous_ids','-append');
disp('Finished Evaluating Network Connections')


total_time = seconds(toc(total_time));
total_time.Format = 'hh:mm:ss.sss'
