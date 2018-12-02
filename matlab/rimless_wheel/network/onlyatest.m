% clear
% close all
% clc


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

% set beta in the cost function normthetadoterr + normtorsoangle
ddir = ['beta_' num2str(beta) '/'];
network_data_dir = ['../data/' ddir];
% switch beta
% 	case 1e-5
% 		ddir = ['beta_' beta '/'];
% 		network_data_dir = ['../data/' ddir];
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% 	case 0.1
% 		ddir = ['beta_' beta '/'];
% 		network_data_dir = ['../data/' ddir];
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% 	case 1
% 		ddir = ['beta_' beta '/'];
% 		network_data_dir = ['../data/' ddir];
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% 	case 10
% 		ddir = ['beta_' beta '/'];
% 		network_data_dir = ['../data/' ddir];
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% end

% if directories arent there then make them
conn_dir = [network_data_dir '/connected_network/'];
eval_dir = [network_data_dir '/evaluated_network/'];
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
parameters.beta = beta;

% generate the network 
% output_filename = [network_data_dir '/network.mat'];
% GenerateCostNetwork(output_filename,parameters,velocities(ceil(N/2)));
% [connectivity,~,~,conns] = testNetworkConnectivity(output_filename);
% if connectivity < 0.1*length(parameters.actions)
% 	disp('something is wrong. connectivity too low to continue')
% 	exit();
% end
% disp('Complete network generation now Generating Connections')

vels = parameters.velocities(any(conns ~=0,1));
[~,n1] = nearest2(-1,vels);
[~,n2] = nearest2(-4,vels);
vels = vels([n1 n2]);
output_filenames = cell(length(vels),3);
for i = 1:length(vels)
	output_filenames(i,1) = {[network_data_dir '/network_desired_speed_' num2str(vels(i)) '.mat']};
	output_filenames(i,2) = {[conn_dir '/network_desired_speed_' num2str(vels(i)) '.mat']};
	output_filenames(i,3) = {[eval_dir '/network_desired_speed_' num2str(vels(i)) '.mat']};
end

% timer
evaltime = tic;
% timer

for i = 1:length(vels)
	xd = vels(i)
	GenerateCostNetwork(output_filenames{i,1},parameters,xd);
end
% timer
evaltime = seconds(toc(evaltime));
evaltime.Format = 'hh:mm:ss';
disp(['Complete network generation after: ' char(evaltime)])
% timer

% timer
evaltime = tic;
timer

% data = load(output_filenames{1,3},'network');
% network = data.network;
% after = zeros(150,2);
% before = after;
for i = 1:length(vels)
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

function [val, n] = nearest2(val,arr)
	vec = abs(arr - val);
	[val,n] = min(vec);
	val = arr(val == vec);
end
