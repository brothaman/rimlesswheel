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

vmax =  0.67;
vmin = -5.6;
amax = 90*pi/180;
amin = 0;
velocities = vmin:(vmax-vmin)/N:vmax;
actions = amin:(amax-amin)/M:amax;
fixed = 1;

flag = 0;
steps = 1;
parameters = get_parameters(fixed);

parameters.vmin = vmin;
parameters.vmax = vmax;
parameters.amax = amax;
parameters.amin = amin;
parameters.velocities = velocities;
parameters.actions = actions;

for xd = parameters.velocities
	parameters.desired_speed = xd;
	
	output_filename = ['../data/network_desired_speed_' num2str(xd) '.mat'];
	GenerateCostNetwork(output_filename,parameters);
	disp('Complete network generation now Generating Connections')

	input_filename = output_filename;
	output_filename = ['../data/connected_network/network_desired_speed_' num2str(xd) '.mat'];
	GenerateNetworkConnections(input_filename, output_filename);
	disp('Finished generating connections now evaluating connected network')

	input_filename = output_filename;
	output_filename = ['../data/evaluated_network/network_desired_speed_' num2str(xd) '.mat'];
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
	disp('Finished evaluating connections')
end

exit();
function nnetwork = convertNetwork(network)
	nnetwork = [];
	for i = 1:length(network)
		if isempty(network{i}.optimal_policy)
			continue;
		end
		nnetwork = [ nnetwork; network{i}.state network{i}.connections{network{i}.optimal_policy}(2)];
	end
end
