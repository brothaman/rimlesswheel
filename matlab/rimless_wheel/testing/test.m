format long
close all
clc
clear all
addpath ../../lib/ ../data/ ../model/ ../../single_pendulum/lib/
beta = 1e4;
ddir = ['beta_' num2str(beta) '/'];
network_data_dir = ['../data/' ddir];
load([network_data_dir '/network.mat'])
network_path = [network_data_dir 'evaluated_network/'];
steps = 50;

% switch beta
% 	case 1e-5
% 		network_data_dir = '../network/junk/data/';
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% 	case 0.1
% 		ddir = 'beta_0.1/';
% 		network_data_dir = ['../data/' ddir];
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% 	case 1
% 		ddir = 'beta_1/';
% 		network_data_dir = ['../data/' ddir];
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% 	case 10
% 		ddir = 'beta_10/';
% 		network_data_dir = ['../data/' ddir];
% 		load([network_data_dir '../network.mat'])
% 		network_path = [network_data_dir 'evaluated_network/'];
% end

[network,xds] = convertAllNetworks(parameters.velocities,network_path);
fixed_filename = '../plots/fixed_angle.avi';
dynamic_filename = '../plots/dynamics_accurate.avi';
[~,n1] = nearest2(-2,xds);
[~,n2] = nearest2(-3.5,xds);


%% Fix Angle Rimless Wheel Robot Control
fixed = 1;
data_fixed = generate_data(fixed,network,[n1+1 10;n2+1 10]);

ts = data_fixed{1};
zs = data_fixed{2};
alphas = data_fixed{3};
parms = data_fixed{4};
poincare_map_data = data_fixed{5};

fps = 30;
farview = 0; %=1 to have a farview of the animation
disp('Animating...');
%disp('NOTE: Animation speed can be changed using fps defined in the code');
figure(1)
animater_fixed(ts,zs,parms,steps,fps,farview,alphas,fixed_filename);

len = length(poincare_map_data(:,2));
hlen = floor(len/2);
pmap_fig = figure;hold on;
% c = linspace(1,10,length(poincare_map_data(:,1)));
% scatter(poincare_map_data(:,1),poincare_map_data(:,2),100,'r')
scatter(poincare_map_data(1:hlen,1),poincare_map_data(1:len/2,2),100,'b*','LineWidth',3)
scatter(poincare_map_data(hlen:end,1),poincare_map_data(hlen:end,2),100,'r*','LineWidth',3)
xlabel('$\mathbf{\theta}$ - leg angle','Interpreter','latex','FontSize',18)
ylabel('$\mathbf{\dot\theta}$ - leg angle rate','Interpreter','latex','FontSize',18)
title('Poincare Section of 50 Step Speed Transition','FontSize',18)
axis([-1 1 -5 0])
saveas(pmap_fig,'../plots/PoincareSectionof50StepSpeedTransition.pdf')

leg_radius = 0.26;
v2 = -leg_radius*mean(poincare_map_data(hlen+5:end,2));
v1 = -leg_radius*mean(poincare_map_data(5:hlen,2));
ss_fig = figure;
plot(poincare_map_data(:,2),'o-','LineWidth',3)
xlabel('\textbf{Step} - k','Interpreter','latex','FontSize',18)
ylabel('$\mathbf{\dot\theta}$ - leg angle rate','Interpreter','latex','FontSize',18)
title(['\textbf{Speed Transition} from $\mathbf{', num2str(v1,2), '} \frac{m}{s}$ to $\mathbf{',num2str(v2,2), '} \frac{m}{s}$ in \textbf{5 Steps}'],'Interpreter','latex','FontSize',18)
% xlim([24 40])
saveas(ss_fig,'../plots/SpeedTransition039-082-6steps.pdf')

limitcycle_fig = figure; hold on;
plot(zs(:,1),zs(:,2))
scatter(0,0,100,'y','fill','MarkerEdgeColor','b')
scatter(poincare_map_data(1:hlen,1),poincare_map_data(1:len/2,2),100,'b','LineWidth',3)
scatter(poincare_map_data(hlen:end,1),poincare_map_data(hlen:end,2),100,'r','LineWidth',3)
ylabel('$\dot\theta$ - rate leg angle','Interpreter','latex','FontSize',18)
xlabel('$\theta$ - leg angle','Interpreter','latex','FontSize',18)
title('\textbf{Periodic Orbit} of Rowdy''s $\{\theta,\dot\theta\}$ States','Interpreter','latex','FontSize',18)
annotation('textarrow',[.75 .53],[.8 .92],'String','Start from Here')
annotation('rectangle',[.49 .23 .05 .36],'FaceColor','blue','FaceAlpha',.2)
annotation('textarrow',[.6 .53],[.6 .45],'String','\textbf{Poincar\''e Section}','Interpreter','latex','FontSize',18)
saveas(limitcycle_fig,'../plots/Periodic State Orbit.pdf')

% % animate limit cycle line
% vidObj = VideoWriter('../plots/RWR/AnimatedPeriodicOrbit.avi');
% vidObj.Quality = 100;
% % vidObj.FrameRate = 30;
% open(vidObj);
% 
% animated_line_fig = figure;
% animated_line = animatedline(gca,'Color','b');
% axis([-0.5 0.5 -5 0])
% for i = 1:length(ts)
% 	addpoints(animated_line,zs(i,1),zs(i,2));
% 	drawnow
% 	writeVideo(vidObj,getframe(gcf));
% end
% close(vidObj);


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
data_dynamic = generate_data(fixed,network,35);
data_dynamic{1} = reshape(data_dynamic{1}',[numel(data_dynamic{1}),1]);
ts = data_dynamic{1};
zs = data_dynamic{2};
alphas = data_dynamic{3};
parms = data_dynamic{4};

% fps = 30;
% farview = 0; %=1 to have a farview of the animation
% disp('Animating...');
% %disp('NOTE: Animation speed can be changed using fps defined in the code');
% figure(1)
% animater_dynamics(ts,zs,parms,steps,fps,farview,dynamic_filename);

figure('Position',[0 0 1200 300])
subplot(2,1,1)
plot(ts,zs(:,1),'r','LineWidth',3);
title('Angle Between Stance Leg and Ground')
xlabel('t - time')

subplot(2,1,2)
plot(ts,zs(:,2),'b','LineWidth',3);
title('Translational Velocity of Hip in +x - direction')
xlabel('t - time')

% % subplot(4,1,3)
% % plot(ts,zs(:,3),'r','LineWidth',3);
% % title('Angle Between Torso and Ground')
% % xlabel('t - time')
% % 
% % subplot(4,1,4)
% % plot(ts,alphas,'b','LineWidth',3);
% % title('Desired Angle Between Torso and Ground')
% % xlabel('t - time','LineWidth',3)
saveas(gcf,'../plots/control_of_dynamic_rimlesswheel.jpg')
	
%% Plot Both 
h = figure('Position',[0 0 1200 300]);
hold on
plot(data_fixed{1},moving_average(data_fixed{2}(:,2),75),'b-','DisplayName','Average of Dynamically Accurate','LineWidth',5)
plot(data_fixed{1},data_fixed{2}(:,2),'b-','DisplayName','Dynamically Accurate','LineWidth',.5)
plot(data_dynamic{1},moving_average(data_dynamic{2}(:,2),50),'r-','DisplayName','Average of Fixed Angle','LineWidth',5)
plot(data_dynamic{1},data_dynamic{2}(:,2),'r-','DisplayName','Fixed Angle','LineWidth',.5)
legend('show')

title('Velocity of Hip when Walking')
saveas(gcf,'../plots/Ideal vs Real.jpg')
%% Functions
function [nnetwork,xds] = convertAllNetworks(velocities,path)
	nnetwork{1} = [];
	i = 1;
	xds = [];
	for xd = velocities
		filename = ['network_desired_speed_' num2str(xd) '.mat'];
		if exist([path filename],'file')
			xds = [xds xd];
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

function [val, n] = nearest2(val,arr)
	vec = abs(arr - val);
	[val,n] = min(vec);
	val = arr(val == vec);
end

%% Plotting functions
