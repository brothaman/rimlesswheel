% maxNumCompThreads = 32;
% parameters.filename = '../lib/weak_cost_network.mat';
% parameters.path = '../lib/weak_pend/';
% parameters.evalfname = 'weak_network_';
% parameters.plottitle = 'weak cost network iteration ';
% parameters.imagepath = 'images/weak_pend/growth/';
% parameters.maxNumCompThreads = 32;
% 
% addpath ../lib                                 
% parameters.xd  = [pi 0];
% parameters.time = 0.05;                                 
% parameters.anglerange = [0,2*pi];                         
% parameters.speedrange = [-10,10];                         
% parameters.torquerange = [-1.5,1.5];
% parameters.angles = 300;
% parameters.speeds = 300;
% parameters.torques = 20;
% parameters.goal = [151,151];
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
N = sum(any(~cellfun('isempty',connections),2));
% if ~exist(parameters.imagepath,'dir')
%     mkdir(parameters.imagepath)
% end
% save([parameters.path parameters.evalfname int2str(0) '.mat'],'network')
% input_filename = parameters.filename;
% for iter = 1:N
% 	iter
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
% --------------------------adding movie--------------------------------- %
myPathVid = [parameters.imagepath 'DiskNetworkGrowth.avi'];
DiskVidObj = VideoWriter(myPathVid,'Uncompressed AVI');
open(DiskVidObj);

myPathVid = [parameters.imagepath 'CylindricalNetworkGrowth.avi'];
CylVidObj = VideoWriter(myPathVid,'Uncompressed AVI');
open(CylVidObj);
% ----------------------------------------------------------------------- 

for iter = 1:N
	load([parameters.path parameters.evalfname int2str(iter) '.mat'])
	figure_file_name = [parameters.plottitle int2str(iter)];
	[fig1,fig2] = show_cost_network(figure_file_name, parameters.imagepath, all_angles, all_speeds, network, stats);
	% ----------------------------------------------------------------------- %
	writeVideo(DiskVidObj,getframe(fig1));
	
	figure(fig2)
	view(120,30)
	writeVideo(CylVidObj,getframe(fig2));
	% ----------------------------------------------------------------------- %
	close all
end
close(DiskVidObj);
close(CylVidObj0);
disp('Finished generating plots')
exit();

%% Functions
function stats = netstats(network)
	sz = size(network);
	values = zeros(1,prod(sz));
	for i = 1:sz(1)
		for j = 1:sz(2)
			if ~isempty(network{i,j}.optimal_value)
                values((i-1)*sz(2) + j) = network{i,j}.optimal_value;
			end
		end
	end
	stats.mean = mean(values);
	stats.median = median(values);
	stats.max = max(values);
	stats.min = min(values);
	stats.std = std(values);
end