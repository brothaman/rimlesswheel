addpath ../lib

if ~exist('ptype','var')
	disp('no pendulum type designated')
else

switch ptype
	case 0
		clearvars
		load('jnk/test_cost_network.mat');
% 		parameters.path = 'jnk/test_pend/';
% 		parameters.evalfname = 'test_network_';
% 		parameters.plottitle = 'test cost network iteration ';
% 		parameters.imagepath = 'jnk/images/growth/';
% 		
% 		parameters.time = 0.1;                                 
% 		parameters.anglerange = [0,2*pi];                         
% 		parameters.speedrange = [-6,6];                         
% 		parameters.torquerange = [-10,10];
% 		parameters.angles = 30;
% 		parameters.speeds = 30;
% 		parameters.torques = 20;
% 		parameters.goal = [15,15];
	case 1
		clearvars
		load('../lib/strong_cost_network.mat');
% 		parameters.path = '../lib/strong_pend/';
% 		parameters.evalfname = 'strong_network_';
% 		parameters.plottitle = 'strong cost network iteration ';
% 		parameters.imagepath = 'images/strong_pend/growth/';
% 		
% 		parameters.time = 0.05;                                 
% 		parameters.anglerange = [0,2*pi];                         
% 		parameters.speedrange = [-6,6];                         
% 		parameters.torquerange = [-10,10];
% 		parameters.angles = 150;
% 		parameters.speeds = 150;
% 		parameters.torques = 200;
% 		parameters.goal = [76,76];
	case 2
		clearvars
		load('../lib/moderately_weak_cost_network.mat');
        iter = 66;
% 		parameters.path = '../lib/moderately_weak_pend/';
% 		parameters.evalfname = 'moderately_weak_network_';
% 		parameters.plottitle = 'moderately weak cost network iteration ';
% 		parameters.imagepath = 'images/moderately_weak_pend/growth/';
% 		
% 		parameters.time = 0.05;                                 
% 		parameters.anglerange = [0,2*pi];                         
% 		parameters.speedrange = [-6,6];                         
% 		parameters.torquerange = [-3,3];
% 		parameters.angles = 150;
% 		parameters.speeds = 150;
% 		parameters.torques = 60;
% 		parameters.goal = [76,76];
	case 3
		clearvars
		load('../lib/weak_cost_network.mat');
        iter=76;
% 		parameters.path = '../lib/weak_pend/';
% 		parameters.evalfname = 'weak_network_';
% 		parameters.plottitle = 'weak cost network iteration ';
% 		parameters.imagepath = 'images/weak_pend/growth/';
% 		
% 		parameters.time = 0.05;                                 
% 		parameters.anglerange = [0,2*pi];                         
% 		parameters.speedrange = [-10,10];                         
% 		parameters.torquerange = [-1.5,1.5];
% 		parameters.angles = 300;
% 		parameters.speeds = 300;
% 		parameters.torques = 30;
% 		parameters.goal = [151,151];
	case 4
		load('../lib/very_weak_cost_network.mat');
        iter = 61;
% 		parameters.path = '../lib/very_weak_pend/';
% 		parameters.evalfname = 'very_weak_network_';
% 		parameters.plottitle = 'very weak cost network iteration ';
% 		parameters.imagepath = 'images/very_weak_pend/growth/';
% 		
% 		parameters.time = 0.05;                                 
% 		parameters.anglerange = [0,2*pi];                         
% 		parameters.speedrange = [-10,10];                         
% 		parameters.torquerange = [-1,1];
% 		parameters.angles = 300;
% 		parameters.speeds = 300;
% 		parameters.torques = 20;
% 		parameters.goal = [151,151];
	otherwise
		disp('pendulum type given must be between or equal to 1 and 4')
		disp('you gave')
		ptype
		exit();
end
% parameters.plottitle = 'Iteration ';
% parameters.maxNumCompThreads = 6;
% parameters.xd  = [pi 0];

% save(parameters.filename,...
% 	'parameters');
% total_time = tic;
% 
% % ------------------------ Generate Network ----------------------------- %
% 
% % timer
% evaltime = tic;
% % timer
% 
% 
% disp('Generating Network')
% generate_network(parameters);
% evaltime = seconds(toc(evaltime));
% evaltime.Format = 'hh:mm:ss';
% disp(['Finished Generating Network After ' char(evaltime)])
% % timer
% 
% clearvars -except parameters total_time
% load(parameters.filename)
% 
% 
% % ---------------------- Generate Connections --------------------------- %
% disp('Generating Network Connections')
% evaltime = tic;
% generate_network_connections(parameters);
% evaltime = seconds(toc(evaltime));
% evaltime.Format = 'hh:mm:ss';
% disp(['Finished Generating Network Connections After ' char(evaltime)])
% 
% clearvars -except parameters total_time
% load(parameters.filename)
% 
% % ---------------------- Evaluate Connections --------------------------- %
% disp('Evaluating Network Connections')
% 
% if ~exist(parameters.imagepath,'dir')
%     mkdir(parameters.imagepath)
% end
% if ~exist(parameters.path,'dir')
%     mkdir(parameters.path)
% end 
% % timer
% evaltime = tic;
% % timer
% 
% % stop after 100 iterations if convergence does not occur
% N = 100;%sum(any(~cellfun('isempty',connections),2));
% save([parameters.path parameters.evalfname int2str(0) '.mat'],'network')
% iteration_error = nan(N,1);
% for iter = 1:N
% 	disp(['completed iteration ' num2str(iter)])
% 	before = convertNetwork(network);
% 	output_filename = [parameters.path parameters.evalfname int2str(iter) '.mat'];
% 	network = evaluate_connections(parameters,output_filename,network);
% 	if iter == 1
% 		stats = netstats(network);
% 	end
% 	after = convertNetwork(network);
% 	
% 	% stopping criteria
% 	iteration_error(iter) = sum(sum(abs(before - after)));
% 	if iteration_error(iter) == 0
% 		break;
% 	end
% end
% iteration_error = iteration_error(~isnan(iteration_error));
% save(parameters.filename,'network','ids','previous_ids','iteration_error','stats','-append');
% disp('Finished Evaluating Network Connections')
% total_time = seconds(toc(total_time));
% 
% % timer
% evaltime = seconds(toc(evaltime));
% evaltime.Format = 'hh:mm:ss';
% disp(['Finished Evaluating Network Connections After ' char(evaltime)])
% % timer

% --------------------- Network Growth Movie ---------------------------- %
disp('Generating plots')

% timer
evaltime = tic;
% timer


myPathVid = [parameters.imagepath 'DiskNetworkGrowth.avi'];
DiskVidObj = VideoWriter(myPathVid,'Uncompressed AVI');
open(DiskVidObj);

myPathVid = [parameters.imagepath 'CylindricalNetworkGrowth.avi'];
CylVidObj = VideoWriter(myPathVid,'Uncompressed AVI');
open(CylVidObj);

myPathVid = [parameters.imagepath 'CylindricalNetworkGrowth120.avi'];
CylVidObj120 = VideoWriter(myPathVid,'Uncompressed AVI');
open(CylVidObj120);

myPathVid = [parameters.imagepath 'CylindricalNetworkGrowth240.avi'];
CylVidObj240 = VideoWriter(myPathVid,'Uncompressed AVI');
open(CylVidObj240);
% ----------------------------------------------------------------------- %
fig1 = figure;
fig2 = figure;
set(fig1,'Visible','off')
set(fig2,'Visible','off')
for iter = 1:iter
	load([parameters.path parameters.evalfname int2str(iter) '.mat'])
	figure_file_name = [parameters.plottitle int2str(iter)];
	[fig1,fig2] = show_cost_network(fig1,fig2,figure_file_name, parameters.imagepath, all_angles, all_speeds, network, stats);
	% ------------------------------------------------------------------- %
	writeVideo(DiskVidObj,getframe(fig1));
	
% 	set(0,'CurrentFigure',fig2)
	figure(fig2)
	view(0,30)
	writeVideo(CylVidObj,getframe(fig2));
	view(120,30)
	writeVideo(CylVidObj120,getframe(fig2));
	view(240,30)
	writeVideo(CylVidObj240,getframe(fig2));
	% ------------------------------------------------------------------- %
	disp(['completed plot ' num2str(iter)])
end
close(DiskVidObj);
close(CylVidObj);
close(CylVidObj120);
close(CylVidObj240);

% timer
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Finished Generating plots After ' char(evaltime)])
% timer
end
% exit();

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

function nnetwork = convertNetwork(network)
	sz = size(network);
	nnetwork = zeros(prod(sz),3);
	for i = 1:sz(1)
		for j = 1:sz(2)
			if isempty(network{i,j}.optimal_policy)
				continue;
			end
			if isnan(network{i,j}.optimal_policy)
				continue;
			end
			nnetwork((i-1)*sz(2)+j,:) = [ network{i,j}.ID network{i,j}.connections{network{i,j}.optimal_policy}(4)];
		end
	end
end