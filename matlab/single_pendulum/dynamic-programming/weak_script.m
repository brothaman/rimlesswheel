maxNumCompThreads = 32;
parameters.filename = '../lib/weak_cost_network.mat';
parameters.path = '../lib/weak_pend/';
parameters.evalfname = 'weak_network_';
parameters.plottitle = 'weak cost network iteration ';
parameters.imagepath = 'images/weak_pend/growth/';

addpath ../lib                                 
parameters.xd  = [pi 0];
parameters.time = 0.05;                                 
parameters.anglerange = [0,2*pi];                         
parameters.speedrange = [-10,10];                         
parameters.torquerange = [-1.5,1.5];
parameters.angles = 300;
parameters.speeds = 300;
parameters.torques = 20;
parameters.goal = [151,151];

save(parameters.filename,...
	'parameters');
total_time = tic;

disp('Generating Network')
generate_network(parameters);
disp('Finished Generating Network')

clearvars -except parameters total_time
load(parameters.filename)

disp('Generating Network Connections')
generate_network_connections(parameters);
disp('Finished Generating Network Connections')

clearvars -except parameters total_time
load(parameters.filename)

disp('Evaluating Network Connections')
N = sum(any(~cellfun('isempty',connections),2));
if ~exist(parameters.imagepath,'dir')
    mkdir(parameters.imagepath)
end
save([parameters.path parameters.evalfname int2str(0) '.mat'],'network')
input_filename = parameters.filename;
for iter = 1:N
	iter
	output_filename = [parameters.path parameters.evalfname int2str(iter) '.mat'];
	evaluate_connections(parameters,input_filename,output_filename)
	input_filename = [parameters.path parameters.evalfname int2str(iter) '.mat'];

	load( output_filename)
	save( output_filename, 'network')
end
save(parameters.filename,'network','ids','previous_ids','-append');
disp('Finished Evaluating Network Connections')
total_time = seconds(toc(total_time));

disp('Generating plots')
for iter = 1:N
	load([parameters.path parameters.evalfname int2str(iter) '.mat'])
	figure_file_name = [parameters.plottitle int2str(iter)];
	show_cost_network(figure_file_name, parameters.imagepath, all_angles, all_speeds, network)
	close all
end
disp('Finished generating plots')
exit()
