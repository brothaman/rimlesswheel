clear
close all
clc


% ------------------------- Add Model Path ----------------------------- %
addpath('../../single_pendulum/lib/')
addpath('../model/')
% ------------------------- Add Model Path ----------------------------- %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ------------------------ discretizations ----------------------------- %
N = 150;
M = 90;
% ------------------------ discretizations ----------------------------- %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ------------------------ Set Output Paths ---------------------------- %
output_dir = 'junk/';
if ~exist([output_dir '/data/connected_network/'],'dir')
    mkdir([output_dir '/data/connected_network/'])
end

if ~exist([output_dir '/data/evaluated_network/'],'dir')
    mkdir([output_dir '/data/evaluated_network/'])
end
% ------------------------ Set Output Paths ---------------------------- %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

cogentime = [];
negentime = [];
evgentime = [];
% define the feasible region space
vmax =  0.67;
vmin = -5.6;

% define the actions
amax = 90*pi/180;
amin = 0;

% vectorize the region and actions
velocities = vmin:(vmax-vmin)/N:vmax;
actions = amin:(amax-amin)/M:amax;

% define the type of model for programming the network
fixed = 1;

% build the parameters struct that will contain the characteristic
% information about the system: feasible region, action limits, model
% programming type
parameters = get_parameters(fixed);
parameters.vmin = vmin;
parameters.vmax = vmax;
parameters.amax = amax;
parameters.amin = amin;
parameters.velocities = velocities;
parameters.actions = actions;
parameters.desired_speed = velocities(ceil(N/2));

total_time = tic;
% generate the network 
output_filename = [output_dir '/network.mat'];

%
% timer
evaltime = tic;
% timer

GenerateCostNetwork(output_filename,parameters);

% timer
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Complete network generation after: ' char(evaltime)])
% timer

[connectivity,~,~,conns] = testNetworkConnectivity(output_filename);
if connectivity < 0.1*length(parameters.actions)
	disp('something is wrong. connectivity too low to continue')
	exit();
end
disp('Now Generating Connections')

% run one iteration
for xd = parameters.velocities(any(conns ~=0,1))
	
% -------------------- Generating Network ------------------------------- %
	% timer
	evaltime = tic;
	% timer

	parameters.desired_speed = xd;
	
	output_filename = [output_dir '/data/network_desired_speed_' num2str(xd) '.mat'];
	GenerateCostNetwork(output_filename,parameters);
	disp('Complete network generation now Generating Connections')

	% timer
	evaltime = seconds(toc(evaltime));
	evaltime.Format = 'hh:mm:ss';
	disp(['Complete network generation after: ' char(evaltime)])
	% timer
	
	cogentime = [cogentime; evaltime];
% -------------------- Generating Network Connections ------------------- %
	
	disp('now Generating Connections')

	% timer
	evaltime = tic;
	% timer
	
	input_filename = output_filename;
	output_filename = [output_dir '/data/connected_network/network_desired_speed_' num2str(xd) '.mat'];
	GenerateNetworkConnections(input_filename, output_filename);
% 	disp('Finished generating connections now evaluating connected network')

	% timer
	evaltime = seconds(toc(evaltime));
	evaltime.Format = 'hh:mm:ss';
	disp(['Finished generating connections after: ' char(evaltime)])
	% timer
	
	negentime = [negentime; evaltime];
% -------------------- Evaluating Network Connections ------------------- %

	disp('Now evaluating connected network')
	% timer
	evaltime = tic;
	% timer

	input_filename = output_filename;
	output_filename = [output_dir '/data/evaluated_network/network_desired_speed_' num2str(xd) '.mat'];
	EvaluateConnectedNetwork(input_filename, output_filename);

	load(output_filename);
	for i = 1:20
		before = convertNetwork(network);
		EvaluateConnectedNetwork(output_filename,output_filename);
		load(output_filename);
		after = convertNetwork(network);
		if sum(sum(before - after)) == 0
			break;
		end
	end
	if i == 20
		disp('global minima may not have been found')
	end
	
	% timer
	evaltime = seconds(toc(evaltime));
	evaltime.Format = 'hh:mm:ss';
	disp(['Finished evaluating connections after: ' char(evaltime)])
	% timer
	
	evgentime = [evgentime; evaltime];
% 	disp(['Finished evaluating connections on:	' output_filename])
% 	break;
end
total_time = seconds(toc(total_time));
total_time.Format = 'hh:mm:ss';
disp(['Finished Generating plots After ' char(total_time)])

save([output_dir 'chron.m'],'evgentime','cogentime','negentime');
% exit();


%% Functions
function nnetwork = convertNetwork(network)
	nnetwork = [];
	for i = 1:length(network)
		if isempty(network{i}.optimal_policy)
			continue;
		end
		nnetwork = [ nnetwork; network{i}.state network{i}.connections{network{i}.optimal_policy}(2)];
	end
end
