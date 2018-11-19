addpath ../lib

if ~exist('ptype','var')
	disp('no pendulum type designated')
else

switch ptype
	case 0
		clearvars
		parameters.filename = 'jnk/test_cost_network.mat';
		parameters.path = 'jnk/test_pend/';
		parameters.evalfname = 'test_network_';
		parameters.plottitle = 'test cost network iteration ';
		parameters.imagepath = 'jnk/images/growth/';
		
		parameters.time = 0.1;                                 
		parameters.anglerange = [0,2*pi];                         
		parameters.speedrange = [-6,6];                         
		parameters.torquerange = [-10,10];
		parameters.angles = 30;
		parameters.speeds = 30;
		parameters.torques = 20;
		parameters.goal = [15,15];
	case 1
		clearvars
		parameters.filename = '../lib/strong_cost_network.mat';
		parameters.path = '../lib/strong_pend/';
		parameters.evalfname = 'strong_network_';
		parameters.plottitle = 'strong cost network iteration ';
		parameters.imagepath = 'images/strong_pend/growth/';
		
		parameters.time = 0.025;                                 
		parameters.anglerange = [0,2*pi];                         
		parameters.speedrange = [-6,6];                         
		parameters.torquerange = [-10,10];
		parameters.angles = 300;
		parameters.speeds = 300;
		parameters.torques = 200;
		parameters.goal = [151,151];
	case 2
		clearvars
		parameters.filename = '../lib/moderately_weak_cost_network.mat';
		parameters.path = '../lib/moderately_weak_pend/';
		parameters.evalfname = 'moderately_weak_network_';
		parameters.plottitle = 'moderately weak cost network iteration ';
		parameters.imagepath = 'images/moderately_weak_pend/growth/';
		
		parameters.time = 0.05;                                 
		parameters.anglerange = [0,2*pi];                         
		parameters.speedrange = [-6,6];                         
		parameters.torquerange = [-3,3];
		parameters.angles = 100;
		parameters.speeds = 200;
		parameters.torques = 60;
		parameters.goal = [51,101];
	case 3
		clearvars
		parameters.filename = '../lib/weak_cost_network.mat';
		parameters.path = '../lib/weak_pend/';
		parameters.evalfname = 'weak_network_';
		parameters.plottitle = 'weak cost network iteration ';
		parameters.imagepath = 'images/weak_pend/growth/';
		
		parameters.time = 0.05;                                 
		parameters.anglerange = [0,2*pi];                         
		parameters.speedrange = [-10,10];                         
		parameters.torquerange = [-1.5,1.5];
		parameters.angles = 300;
		parameters.speeds = 300;
		parameters.torques = 30;
		parameters.goal = [151,151];
	case 4
		parameters.filename = '../lib/very_weak_cost_network.mat';
		parameters.path = '../lib/very_weak_pend/';
		parameters.evalfname = 'very_weak_network_';
		parameters.plottitle = 'very weak cost network iteration ';
		parameters.imagepath = 'images/very_weak_pend/growth/';
		
		parameters.time = 0.05;                                 
		parameters.anglerange = [0,2*pi];                         
		parameters.speedrange = [-10,10];                         
		parameters.torquerange = [-1,1];
		parameters.angles = 300;
		parameters.speeds = 300;
		parameters.torques = 20;
		parameters.goal = [151,151];
	otherwise
		disp('pendulum type given must be between or equal to 1 and 4')
		disp('you gave')
		ptype
		exit();
end

parameters.maxNumCompThreads = 10;
parameters.xd  = [pi 0];

save(parameters.filename,...
	'parameters');
total_time = tic;

% ------------------------ Generate Network ----------------------------- %

% timer
evaltime = tic;
% timer


disp('Generating Network')
generate_network(parameters);
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Finished Generating Network After ' char(evaltime)])
% timer

clearvars -except parameters total_time
load(parameters.filename)


% ---------------------- Generate Connections --------------------------- %
disp('Generating Network Connections')
evaltime = tic;
generate_network_connections(parameters);
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Finished Generating Network Connections After ' char(evaltime)])

clearvars -except parameters total_time
load(parameters.filename)

% ---------------------- Evaluate Connections --------------------------- %
disp('Evaluating Network Connections')

% timer
evaltime = tic;
% timer

N = sum(any(~cellfun('isempty',connections),2));
if ~exist(parameters.imagepath,'dir')
    mkdir(parameters.imagepath)
end
save([parameters.path parameters.evalfname int2str(0) '.mat'],'network')
input_filename = parameters.filename;
for iter = 1:N
	disp(['completed iteration ' num2str(iter)])
	output_filename = [parameters.path parameters.evalfname int2str(iter) '.mat'];
	evaluate_connections(parameters,input_filename,output_filename)
	input_filename = [parameters.path parameters.evalfname int2str(iter) '.mat'];

	load( output_filename)
	save( output_filename, 'network')
end
save(parameters.filename,'network','ids','previous_ids','-append');
disp('Finished Evaluating Network Connections')
total_time = seconds(toc(total_time));

% timer
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Finished Generating Network Connections After ' char(evaltime)])
% timer

disp('Generating plots')
stats = netstats(network);
% --------------------- Network Growth Movie ---------------------------- %


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

for iter = 1:N
	load([parameters.path parameters.evalfname int2str(iter) '.mat'])
	figure_file_name = [parameters.plottitle int2str(iter)];
	[fig1,fig2] = show_cost_network(figure_file_name, parameters.imagepath, all_angles, all_speeds, network, stats);
	% ------------------------------------------------------------------- %
	writeVideo(DiskVidObj,getframe(fig1));
	
	figure(fig2)
	view(0,30)
	writeVideo(CylVidObj,getframe(fig2));
	view(120,30)
	writeVideo(CylVidObj120,getframe(fig2));
	view(240,30)
	writeVideo(CylVidObj240,getframe(fig2));
	% ------------------------------------------------------------------- %
	close all
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