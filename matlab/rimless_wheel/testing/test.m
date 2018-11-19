format long
close all
clc
clear all
addpath ../../lib/ ../data/ ../model/
load ../data/network.mat

network = convertAllNetworks(parameters.velocities);
fixed_filename = '../plots/fixed_angle.avi';
dynamic_filename = '../plots/dynamics_accurate.avi';


%% Fix Angle Rimless Wheel Robot Control
fixed = 1;
steps = 20;
data_fixed = generate_data(fixed,steps,network);

ts = data_fixed{1};
zs = data_fixed{2};
alphas = data_fixed{3};
parms = data_fixed{4};

% fps = 30;
% farview = 0; %=1 to have a farview of the animation
% disp('Animating...');
% %disp('NOTE: Animation speed can be changed using fps defined in the code');
% figure(1)
% animater_fixed(ts,zs,parms,steps,fps,farview,alphas,fixed_filename);

figure('Position',[0 0 1200 300])
subplot(2,1,1)
plot(ts,zs(:,1),'r','LineWidth',3);
title('Angle Between Stance Leg and Ground')
xlabel('t - time')

subplot(2,1,2)
plot(ts,zs(:,2),'b','LineWidth',3);
title('Translational Velocity of Hip in +x - direction')
xlabel('t - time')
saveas(gcf,'../plots/control_of_fixed_rimlesswheel.jpg')

%% Dynamically (more)Accurate Rimless Wheel Robot
fixed = 0;
steps = 20;
data_dynamic = generate_data(fixed,steps,network);

ts = data_dynamic{1};
zs = data_dynamic{2};
alphas = data_dynamic{3};
parms = data_dynamic{4};

% fps = 30;
% farview = 0; %=1 to have a farview of the animation
% disp('Animating...');
% %disp('NOTE: Animation speed can be changed using fps defined in the code');
% figure(1)
% animater_dynamics(ts,zs,parms,steps,fps,farview,myPathVid);

figure('Position',[0 0 1200 300])
subplot(4,1,1)
plot(ts,zs(:,1),'r','LineWidth',3);
title('Angle Between Stance Leg and Ground')
xlabel('t - time')

subplot(4,1,2)
plot(ts,zs(:,2),'b','LineWidth',3);
title('Translational Velocity of Hip in +x - direction')
xlabel('t - time')

subplot(4,1,3)
plot(ts,zs(:,3),'r','LineWidth',3);
title('Angle Between Torso and Ground')
xlabel('t - time')

subplot(4,1,4)
plot(ts,alphas,'b','LineWidth',3);
title('Desired Angle Between Torso and Ground')
xlabel('t - time','LineWidth',3)
saveas(gcf,'../plots/control_of_dynamic_rimlesswheel.jpg')
	
%% Plot Both 
h = figure('Position',[0 0 1200 300]);
hold on
plot(data_dynamic{1},data_dynamic{2}(:,2),'b.','DisplayName','Fixed Angle','LineWidth',.5)
plot(data_fixed{1},moving_average(data_fixed{2}(:,2),100),'r-','DisplayName','Average of Dynamically Accurate','LineWidth',5)
plot(data_fixed{1},data_fixed{2}(:,2),'r.','DisplayName','Dynamically Accurate','LineWidth',.5)
plot(data_dynamic{1},moving_average(data_dynamic{2}(:,2),100),'b-','DisplayName','Average of Fixed Angle','LineWidth',5)
legend('show')

title('Velocity of Hip when Walking')
saveas(gcf,'../plots/Ideal vs Real.jpg')
%% Functions
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

function output_vec = moving_average(input_vec, n)
	if min(size(input_vec)) ~=1
		% throw error
	else
		if size(input_vec,2) == length(input_vec)
		else
			% reshape
			input_vec = reshape(input_vec,[1,length(input_vec)]);
		end
		
	end
	mat = zeros(2*n+1,length(input_vec));
	mat(n+1,:) = input_vec;
	for i=1:n
		% left side position as a function of i
		% k_left = middle - i
		kl = (n+1) - i;
		temp = [input_vec(i+1:end) input_vec(end)*ones(1,i)];
		mat(kl,:) = temp;
		
		% right side position as a function of i
		% k_right = middle + i
		kr = (n+1) + i;
		temp = [input_vec(end)*ones(1,i) input_vec(1:end-i)];
		mat(kr,:) = temp;	
	end
	
	% now squish the matrix to a vector
	output_vec = sum(mat,1)/(2*n+1);
end