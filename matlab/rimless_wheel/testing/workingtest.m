format long
close all
clc
clear all
addpath ../../lib/ ../data/ ../model/
load ../data/network.mat

fixed = 1;
network = convertAllNetworks(parameters.velocities);
parms = get_parameters(fixed);
ts = [];

steps = 20;
alphas = [];
data = generate_data(fixed,steps,network);

ts = data{1};
zs = data{2};
alphas = data{3};

if parms.fixed == 1
	fps = 30;
	farview = 0; %=1 to have a farview of the animation
	disp('Animating...');
	%disp('NOTE: Animation speed can be changed using fps defined in the code');
	figure(1)
	animater_fixed(ts,zs,parms,steps,fps,farview,alphas);

	figure(2)
	subplot(2,1,1)
	plot(ts,zs(:,1),'r');
	title('Angle Between Stance Leg and Ground')
	xlabel('t - time')
	
	subplot(2,1,2)
	plot(ts,zs(:,2),'b');
	title('Translational Velocity of Hip in +x - direction')
	xlabel('t - time')
	saveas(gcf,'../plots/control_of_fixed_rimlesswheel.jpg')
else

	fps = 30;
	farview = 0; %=1 to have a farview of the animation
	disp('Animating...');
	%disp('NOTE: Animation speed can be changed using fps defined in the code');
	figure(1)
	animate_dynamics(ts,zs,parms,steps,fps,farview);

	figure(2)
	subplot(4,1,1)
	plot(ts,zs(:,1),'r');
	title('Angle Between Stance Leg and Ground')
	xlabel('t - time')
	
	subplot(4,1,2)
	plot(ts,zs(:,2),'b');
	title('Translational Velocity of Hip in +x - direction')
	xlabel('t - time')
	
	subplot(4,1,3)
	plot(ts,zs(:,3),'r');
	title('Angle Between Torso and Ground')
	xlabel('t - time')
	
	subplot(4,1,4)
	plot(ts,alphas,'b');
	title('Desired Angle Between Torso and Ground')
	xlabel('t - time')
	saveas(gcf,'../plots/control_of_dynamic_rimlesswheel.jpg')
end
function nnetwork = convertAllNetworks(velocities)
	path = '../data/evaluated_network/';
	nnetwork{1} = [];
	i = 1;
	for xd = velocities
		filename = ['network_desired_speed_' num2str(xd) '.mat'];
		if exist([path filename],'file')
			data = load([path filename]);
			intermediate = convertNetwork(data.network);
			if ~isempty(intermediate)
				i = i+1;
				nnetwork{i} = intermediate;
				nnetwork{1} = [nnetwork{1}; xd i];
			end
		end
	end
end
function nnetwork = convertNetwork(network)
	nnetwork = [];
	for i = 1:length(network)
		if isempty(network{i}.optimal_policy)
			continue;
		end
		nnetwork = [ nnetwork; network{i}.state network{i}.connections{network{i}.optimal_policy}(2)];
	end
end