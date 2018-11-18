% parameters.filename = '../lib/moderately_weak_cost_network.mat';
% parameters.path = '../lib/moderately_weak_pend/';
% parameters.evalfname = 'moderately_weak_network_';
% parameters.plottitle = 'moderately weak cost network iteration ';
% parameters.imagepath = 'images/moderately_weak_pend/growth/';
% 
% addpath ../lib                                 
% parameters.xd  = [pi 0];
% parameters.time = 0.05;                                 
% parameters.anglerange = [0,2*pi];                         
% parameters.speedrange = [-6,6];                         
% parameters.torquerange = [-3,3];
% parameters.angles = 100;
% parameters.speeds = 200;
% parameters.torques = 200;
% parameters.goal = [51,101];
%  
% 
% % save(parameters.filename,...
% % 	'parameters');
% % total_time = tic;
% % 
% % disp('Generating Network')
% % generate_network(parameters);
% % disp('Finished Generating Network')
% % 
% % clearvars -except parameters total_time
% % load(parameters.filename)
% % 
% % disp('Generating Network Connections')
% % generate_network_connections(parameters);
% % disp('Finished Generating Network Connections')
% % 
% % clearvars -except parameters total_time
% % load(parameters.filename)
% % 
% % disp('Evaluating Network Connections')
% % N = sum(any(~cellfun('isempty',connections),2));
% % if ~exist(parameters.imagepath,'dir')
% %     mkdir(parameters.imagepath)
% % end
% % save([parameters.path parameters.evalfname int2str(0) '.mat'],'network')
% % for iter = 1:N
% %     evaluate_connections(parameters)
% % 	load(parameters.filename)
% % 	save([parameters.path parameters.evalfname int2str(iter) '.mat'],'network')
% % end
% % save(parameters.filename,'network','ids','previous_ids','-append');
% % disp('Finished Evaluating Network Connections')
% % total_time = seconds(toc(total_time));
% % 
% % disp('Generating plots')
% % for iter = 1:N
% % 	load([parameters.path parameters.evalfname int2str(iter) '.mat'])
% %     figure_file_name = [parameters.plottitle int2str(iter)];
% %     show_cost_network(figure_file_name, parameters.imagepath, all_angles, all_speeds, network)
% %     close all
% % end
% % disp('Finished generating plots')
% 
% save(parameters.filename,...
% 	'parameters');
% total_time = tic;
% 
% disp('Generating Network')
% generate_network(parameters);
% disp('Finished Generating Network')
% 
% clearvars -except parameters total_time
% load(parameters.filename)
% 
% disp('Generating Network Connections')
% generate_network_connections(parameters);
% disp('Finished Generating Network Connections')
% 
% clearvars -except parameters total_time
% load(parameters.filename)
% 
% disp('Evaluating Network Connections')
% N = sum(any(~cellfun('isempty',connections),2));
% if ~exist(parameters.imagepath,'dir')
%     mkdir(parameters.imagepath)
% end
% save([parameters.path parameters.evalfname int2str(0) '.mat'],'network')
% input_filename = parameters.filename;
% for iter = 1:N
% 	output_filename = [parameters.path parameters.evalfname int2str(iter) '.mat'];
% 	evaluate_connections(parameters,input_filename,output_filename)
% 	input_filename = [parameters.path parameters.evalfname int2str(iter) '.mat'];
% 
% 	load( output_filename)
% 	save( output_filename, 'network')
% end
% save(parameters.filename,'network','ids','previous_ids','-append');
% disp('Finished Evaluating Network Connections')
% total_time = seconds(toc(total_time));

disp('Generating plots')
stats = netstats(network);
for iter = 1:N
	load([parameters.path parameters.evalfname int2str(iter) '.mat'])
	figure_file_name = [parameters.plottitle int2str(iter)];
	show_cost_network(figure_file_name, parameters.imagepath, all_angles, all_speeds, network, stats)
	close all
end
disp('Finished generating plots')

function stats = netstats(network)
	sz = size(network);
	values = zeros(1,prod(sz));
	for i = 1:sz(1)
		for j = 1:sz(2)
			values((i-1)*sz(2) + j) = network{i,j}.optimal_value;
		end
	end
	stats.mean = mean(values);
	stats.median = median(values);
	stats.max = max(values);
	stats.min = min(values);
	stats.std = std(values);
end
exit();
