clear
close all
clc


% ------------------------- Add Model Path ----------------------------- %
addpath('../../single_pendulum/lib/')
addpath('../model/')
% ------------------------- Add Model Path ----------------------------- %

% ------------------------ discretizations ----------------------------- %
N = 150;
M = 90;
% ------------------------ discretizations ----------------------------- %


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ------------------------ Set Output Paths ---------------------------- %
val = 1;
switch val
	case 1
		output_dir = 'junk/';
	case 2
		output_dir = '../';
end

% if directories arent there then make them
conn_dir = [output_dir '/data/connected_network/'];
eval_dir = [output_dir '/data/evaluated_network/'];
if ~exist(conn_dir,'dir')
    mkdir(conn_dir)
end

if ~exist(eval_dir,'dir')
    mkdir(eval_dir)
end
% ------------------------ Set Output Paths ---------------------------- %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



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

% generate the network 
output_filename = ['../data/network.mat'];
GenerateCostNetwork(output_filename,parameters);
[connectivity,~,~,conns] = testNetworkConnectivity(output_filename);
if connectivity < 0.1*length(parameters.actions)
	disp('something is wrong. connectivity too low to continue')
	exit();
end
disp('Complete network generation now Generating Connections')

vels = parameters.velocities(any(conns ~=0,1));
output_filenames = cell(length(vels),3);
for i = 1:length(vels)
	output_filenames(i,1) = {['../data/network_desired_speed_' num2str(vels(i)) '.mat']};
	output_filenames(i,2) = {['../data/connected_network/network_desired_speed_' num2str(vels(i)) '.mat']};
	output_filenames(i,3) = {['../data/evaluated_network/network_desired_speed_' num2str(vels(i)) '.mat']};
end

% timer
evaltime = tic;
% timer

parfor i = 1:length(vels)
	GenerateCostNetwork(output_filenames{i,1},parameters);
end
% timer
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Complete network generation after: ' char(evaltime)])
% timer

% timer
evaltime = tic;
% timer

data = load(output_filenames{1,3},'network');
network = data.network;
after = zeros(150,2);
before = after;
parfor i = 1:length(vels)
	GenerateNetworkConnections(output_filenames{i,1}, output_filenames{i,2});
	disp('Finished generating connections now evaluating connected network')

	EvaluateConnectedNetwork(output_filenames{i,2}, output_filenames{i,3});

	data = load(output_filenames{i,3},'network');
	network = data.network;
	before = convertNetwork(network);
	for j = 1:100
		EvaluateConnectedNetwork(output_filenames{i,3},output_filenames{i,3});
		data = load(output_filenames{i,3},'network');
		network = data.network;
		after = convertNetwork(network);
		sum(sum((before - after).^2))
		before = after;
		if sum(sum(before - after)) == 0
			break;
		end
	end
	if j == 20
		disp('global minima may not have been found')
	end
	disp(['Finished evaluating connections on:	' output_filenames{i,3}])
end

% timer
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Complete network evaluation after: ' char(evaltime)])
% timer

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
