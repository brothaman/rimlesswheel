%% Visualize the cost network
close all
addpath ../lib
pendulum_type = 3;
switch pendulum_type
	case 0
		load jnk/test_cost_network.mat;
		pendulum_type = 'Test Pendulum';
		path = 'jnk/plots/';
	case 1
		load ../lib/strong_cost_network.mat
		pendulum_type = 'Strong Pendulum';
		path = 'images/strong_pend/figures/';
	case 2
		load ../lib/moderately_weak_cost_network.mat
		pendulum_type = 'Moderately Weak Pendulum';
		path = 'images/moderately_weak_pend/figures/';
	case 3
		load ../lib/weak_cost_network.mat
		pendulum_type = 'Weak Pendulum';
		path = 'images/weak_pend/figures/';
	case 4
		load ../lib/very_weak_cost_network.mat
		pendulum_type = 'Very Weak Pendulum';
		path = 'images/very_weak_pend/figures/';
end
if ~exist(path,'dir')
    mkdir(path)
end
stats = netstats(network);
statenvalues = get_state_n_value(network);
fig = figure;
fig1 = figure;
fig2 = figure;
fig3 = figure;
fig4 = figure;
rdisk = 20;
rcyl = stats.max;
k = 1;
kcost = 1;
N = sum(any(~cellfun('isempty',connections),2));
flag = 1;
clear x y z
[J,q,qdot,inputs] = get_other_data_cost('../lib/pdata.csv');
% animate the pendulum and generate the q_actual
if flag
    [qactual,txs,torques] = animate_pendulum(fig, parameters, network, N, all_angles, all_speeds,[ pendulum_type ' Pendulum [0,0] to [\pi,0]'],path,1);
end

% plot the torque and state
if flag
    plot_state_parameters(fig4,txs, torques,[pendulum_type ' System Response'],q,qdot,inputs)
    saveas(fig4, [path pendulum_type ' Response Plot.pdf'],'pdf'); %pause;
end
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%% plot network on a disk %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[x,y] = get_CN_disk_data(rdisk,k,all_angles,all_speeds);
plot_low_density_scatter(fig1,x,y,[3,3]);
saveas(fig1, [path pendulum_type 'Template Cost Network on a Disk Scatter.pdf'],'pdf'); %pause;
clf(fig1)

plot_low_density_surf(fig1,x,y,[3,3]);
saveas(fig1, [path pendulum_type 'Template Cost Network on a Disk.pdf'],'pdf'); %pause;
clf(fig1)


z = get_disk_cost_height(kcost,all_angles, all_speeds, statenvalues);
switch flag
	case 1 
		[xx,yy,zz] = get_actual_data_for_disk(rdisk,qactual,statenvalues,k,kcost);
		fig1 = visualize_cost_network_on_disk(fig1,x,y,z,xx,yy,zz,['Discoidal Representation of ' pendulum_type ' Pendulum''s Cost Network']);
	case 0
		fig1 = visualize_cost_network_on_disk(fig1,x,y,z,['Discoidal Representation of ' pendulum_type ' Pendulum''s Cost Network']);
end
maxx = max(max(x));
minx = min(min(x));
maxy = max(max(y));
miny = min(min(y));
stdx = std(max(x));
stdy = std(max(y));
axis([(minx-stdx) (maxx+stdx) (miny-stdy) (maxy+stdy) (stats.min-stats.std) (stats.max+stats.std)])
view(0, 45)
colorbar
saveas(fig1, [path pendulum_type 'Discoidal Cost Network.pdf'],'pdf')

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%% plot network on a cylinder %%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% plot the network on a cylinder
plot_low_density_cylinder(fig,rcyl,all_angles,all_speeds,[3,3])
saveas(fig, [path pendulum_type 'Cylindrical Network Template.pdf'],'pdf'); %pause;
[x,y,z] = get_CN_cylinder_data(rcyl,all_angles,all_speeds,statenvalues);
optimal_policy_cost = 0;
switch flag
	case 1
		[xx,yy,zz,optimal_policy_cost] = get_actual_data_for_cylinder(rcyl,qactual,statenvalues);
		fig2 = visualize_cost_network_on_cylinder(fig2,x,y,z,xx,yy,zz,['Cylindrical Representation of the ' pendulum_type ' Pendulum''s Cost Network']);
	case 0
		fig2 = visualize_cost_network_on_cylinder(fig2,x,y,z,['Cylindrical Representation of the ' pendulum_type ' Pendulum''s Cost Network']);
end

colorbar
shading interp
saveas(fig2, [path pendulum_type ' cost network on cylinder-isometric.pdf'],'pdf')
[az,el] = view;

view(0,30)
saveas(fig2, [path pendulum_type ' cost network on cylinder 0deg.pdf'],'pdf')
view(120,30)
saveas(fig2, [path pendulum_type ' cost network on cylinder 120deg.pdf'],'pdf')
view(240,30)
saveas(fig2, [path pendulum_type ' cost network on cylinder 240deg.pdf'],'pdf')

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%% rotating network plot  %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
az = 180-90; el = 15;
rotx = 180/pi*(qactual(1:end-1,1) - qactual(2:end,1))';
roty = 180/pi*(atan(qactual(2:end,2))/6)';
if flag
    rotating_the_cylindrical_cost_network(fig3,x,y,z,'Cylindrical Representation of Cost Network',1,[az,15-5],rotx,roty,path,xx,yy,zz)    
end

disp('Optimal Policy Cost is: ')
disp(optimal_policy_cost)

%% functions
function [val, n] = nearest2(val,arr)                                                                                                                                                                       
vec = abs(arr - val);                                                                                                                                                                                       
[val,n] = min(vec);                                                                                                                                                                                         
val = arr(val == vec);                                                                                                                                                                                      
end

function [torque] = get_control_signal(network, n,m)
    torque = network{n,m}.connections{network{n,m}.optimal_policy}(3);
end

function state_value = get_state_n_value(network)
    [n,m] = size(network);
    for i = 1:n
        for j = 1:m
            if isempty(network{i,j}.optimal_value) || isnan(network{i,j}.optimal_value)
                state_value((i-1)*m + j,:) = [network{i,j}.state nan];
            else
                state_value((i-1)*m + j,:) = [network{i,j}.state network{i,j}.optimal_value];
            end
        end
    end
end

function J = get_value_at_state(state,network)
    J = network(sum(state - network(:,1:2),2) == 0,3);
    if isempty(J)
        disp('here')
    end
end

function plot_circle(fig, radius,center,linename)
    figure(fig);
    N = ceil(pi*2*radius/.1);
    theta = 0:2*pi/ceil(pi*2*radius/.1):2*pi;
    x = center(1) + radius*cos(theta');
    y = center(2) + radius*sin(theta');
    plot(x,y,'LineWidth',5, 'DisplayName',linename)
end

%% Functions for Plotting Cylinder
function [x,y,z] = get_CN_cylinder_data(rmean,all_angles,all_speeds,statenvalues)
    x = zeros(length(all_angles),length(all_speeds));
    y = zeros(length(all_angles),length(all_speeds));
    for i = 1:length(all_angles)
        for j = 1:length(all_speeds)
            x(i,j) = (rmean + get_value_at_state([all_angles(i) all_speeds(j)], statenvalues)) * cos(all_angles(i));
            y(i,j) = (rmean + get_value_at_state([all_angles(i) all_speeds(j)], statenvalues)) * sin(all_angles(i));
        end
    end
    z = ones(size(x)).*all_speeds;
end

function [x,y,z,J] = get_actual_data_for_cylinder(rmean,qactual,statenvalues)
    ractual = zeros(size(qactual(:,1)));
	J = 0;
    for i = 1: length(qactual(:,1))
        ractual(i) = (rmean + get_value_at_state(qactual(i,:), statenvalues));
		J = J+get_value_at_state(qactual(i,:), statenvalues);
    end
    x = ractual.*cos(qactual(:,1));
    y = ractual.*sin(qactual(:,1));
    z = qactual(:,2);
end

function fig = visualize_cost_network_on_cylinder(fig,x,y,z,varargin)
    figure(fig)
    plot_every_thing = false;
    if length(varargin) ~= 4
        disp('no data for actual plot given or wrong size')
        titl = varargin{1};
    else
        [xx,yy,zz,titl] = deal(varargin{:});
        plot_every_thing = true;
    end
    
    C = x.^2 +y.^2;
    surf(x,y,z,C,'DisplayName','Cost Network');
    if plot_every_thing
        hold on
        plot3(xx,yy,zz,'k','LineWidth',10,'DisplayName','Path Traveled');
        hold off
    end
    
    title(titl,'FontSize',14)
    zlabel('Angular Velocity of Pendulum','FontSize',14)
	colorbar;
%     ylabel('y-position of Pendulum - Radius Indicates Cost')
%     xlabel('x-position of Pendulum - Radius Indicates Cost')
end

function fig = rotating_the_cylindrical_cost_network(fig,x,y,z,titl,flag,desc,rotx,roty,path,varargin)
    figure(fig)
	% --------------------------adding movie--------------------------------- %
	myPathVid = [path 'RotatingCylindricalNetwork.avi'];
	vidObj = VideoWriter(myPathVid,'Uncompressed AVI');
	open(vidObj);
	% ----------------------------------------------------------------------- 
    C = x.^2 +y.^2;
    h = surf(x,y,z,C,'DisplayName','Cost Network');
    if ~isempty(varargin)
        [xx,yy,zz] = deal(varargin{:});
        hold on
        p = plot3(xx,yy,zz,'k','LineWidth',10,'DisplayName','Path Traveled');
        hold off
    end
    title(titl)
    view(desc(1), desc(2));
    shading interp
    j = 1;
    for i = [rotx;roty]
        rotate(h,[0 0 1],i(1))
        view(desc(1), i(2));
        if ~isempty(varargin)
            rotate(p,[0 0 1],i(1))
        end
        if flag
			% ----------------------------------------------------------------------- %
			writeVideo(vidObj,getframe(fig));
			% ----------------------------------------------------------------------- %
        end
        pause(0.1)
        j = j + 1;
	end
	close(vidObj);
end

function plot_low_density_cylinder(fig,r,all_angles,all_speeds,res)
    figure(fig)
	x = zeros(length(all_angles),length(all_speeds));
    y = zeros(length(all_angles),length(all_speeds));
    for i = 1:length(all_angles)
        for j = 1:length(all_speeds)
            x(i,j) = r * cos(all_angles(i));
            y(i,j) = r * sin(all_angles(i));
        end
    end
	z = ones(size(x)).*all_speeds;
	
	% reduce resolution of the network
	x = x(1:res(1):end,1:res(2):end);
    y = y(1:res(1):end,1:res(2):end);
	z = z(1:res(1):end,1:res(2):end);
	
    C = x.^2 +y.^2;
    surf(x,y,z,C,'DisplayName','Cost Network');
    
    title('Template Cost Network on a Cylinder','FontSize',18)
end
%% Functions for Plotting Disk
function [x,y] = get_CN_disk_data(rmean,k,all_angles,all_speeds)
    r = rmean + k*all_speeds;
    x = cos(all_angles').*r;
    y = sin(all_angles').*r;
end

function z = get_disk_cost_height(k,all_angles, all_speeds, statenvalues)
    z = zeros(length(all_angles), length(all_speeds));
    for i = 1:length(all_angles)
        for j = 1:length(all_speeds)
            z(i,j) = get_value_at_state([all_angles(i) all_speeds(j)], statenvalues);
        end
    end
end

function [x,y,z] = get_actual_data_for_disk(rmean,qactual,statenvalues,k,kcost)
    ractual = rmean + k*qactual(:,2);
    x = ractual.*cos(qactual(:,1));
    y = ractual.*sin(qactual(:,1));
    z = zeros(size(x));
    for j = 1:length(qactual(:,1))
        z(j) = get_value_at_state(qactual(j,:),statenvalues);
    end
end

function fig = visualize_cost_network_on_disk(fig,x,y,z,varargin)
    figure(fig)
    plot_every_thing = false;
    if length(varargin) ~= 4
        disp('no data for actual plot given or wrong size')
        titl = varargin{1};
    else
        [xx,yy,zz,titl] = deal(varargin{:});
        plot_every_thing = true;
    end
    
    rmax = max(x(1,:));
    rmin = min(x(1,:));
    hold on
    surf(x,y,z, 'DisplayName', 'Cost Network')
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    hold off
    
    shading interp
    if plot_every_thing
        hold on
        plot3(xx,yy,zz,'k','LineWidth',10);
        hold off
    end
%     title('Discoidal Representation of Cost Network')
    title(titl)
    zlabel('Cost to Navigate to the Goal')
    ylabel('y-position of Pendulum')
    xlabel('x-position of Pendulum')
end

function plot_low_density_scatter(fig, x, y, res)
    x = x(1:res(1):end,1:res(2):end);
    y = y(1:res(1):end,1:res(2):end);
    rmax = max(x(1,:));
    rmin = min(x(1,:));
    figure(fig)
    hold on
	title('Template Cost Network on a Disk Scatter','FontSize',18)
    scatter(x(:),y(:),'b','filled','DisplayName','States')  
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    hold off
end

function plot_low_density_surf(fig, x, y, res)
    x = x(1:res(1):end,1:res(2):end);
    y = y(1:res(1):end,1:res(2):end);
    rmax = max(x(1,:));
    rmin = min(x(1,:));
    figure(fig)
    hold on
	title('Template Cost Network on a Disk','FontSize',18)
    surf(x,y,zeros(size(x)),'DisplayName','States')  
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    hold off
end

%% Animate the pendulum
function [qactual,txs, torque] = animate_pendulum(fig,parameters,network,N,all_angles,all_speeds,titl,path,flag)
	t = parameters.time;
    torque = zeros(1,N);
    txs = zeros(N,3);
    phi = -pi/2;
    x = [0 0];
    [x(1),n] = nearest2(x(1),all_angles);
    [x(2),m] = nearest2(x(2),all_speeds);
    xd = [pi 0];
    P = {};
    for i =1:N
        torque(i) = get_control_signal(network,n,m);
        [~,x] = xnplusone(x,torque(i),t);
        [x(1),n] = nearest2(x(1),all_angles);
        [x(2),m] = nearest2(x(2),all_speeds);
        txs(i,:) = [i*t,x];
        P{end+1} = {1*[0 0 cos(x(1)+phi) sin(x(1)+phi)]};
        if round(x,4) == round(xd,4)
            break
        end
    end
    qactual = txs(1:i,2:3);
    figure(fig)
    axis([-2 2 -2 2]);
    phandle = [];
    xlabel('meters')
    ylabel('meters')
    title(titl)
    
	% --------------------------adding movie--------------------------------- %
	myPathVid = [path 'pendulumControl.avi'];
	vidObj = VideoWriter(myPathVid,'Uncompressed AVI');
	open(vidObj);
	% ----------------------------------------------------------------------- 
    for i = 1:length(P)
        [fig,phandle] = show_pendulum(fig,phandle,P{i});
        if flag
			% ----------------------------------------------------------------------- %
			writeVideo(vidObj,getframe(fig));
			% ----------------------------------------------------------------------- %
        end
        pause(0.03);
	end
	close(vidObj);
end

function plot_state_parameters(fig, txs, torques, titl,q,qdot,inputs)
    figure(fig)
    txs = txs(~any(sum(txs,2)==0,2),:);
    torques = torques(~any(sum(txs,2)==0,2));
    
    subplot(3,1,1)
    hold on
    plot(txs(:,1),wrapTo2Pi(pi+txs(:,2))-pi,'b','LineWidth',4,'DisplayName','Angular Position $\theta$ in rad')
%     plot(0.05*(1:length(q))',q,'k','LineWidth',4,'DisplayName','Pranav''s Angular Position $\theta$ in rad')
    plot(txs(:,1),ones(size(txs(:,1)))*pi,'--b','DisplayName','Desired Angular Position')
    hold off
    title('Positional Response')
    xlabel('time (t) in seconds','interpreter','latex')
    ylabel('Position $(\theta$) in radians','interpreter','latex')
    l = legend('show');
    l.Interpreter = 'latex';
    l.Location = 'eastoutside';
    
    subplot(3,1,2)
    hold on
    plot(txs(:,1),txs(:,3),'b','LineWidth',3,'DisplayName','Angular Speed $\dot\theta$ in $\frac{rad}{sec}$')
%     plot(0.05*(1:length(q))',qdot,'k','LineWidth',3,'DisplayName','Pranav''s Angular Speed $\dot\theta$ in $\frac{rad}{sec}$')
    plot(txs(:,1),zeros(size(txs(:,1))),'--k','DisplayName','Desired Angular Speed')
    hold off
    title('Velocity Response')
    xlabel('time (t) in seconds','interpreter','latex')
    ylabel('Velocity $(\dot\theta)$ in $\frac{radians}{seconds}$','interpreter','latex')
    l = legend('show');
    l.Interpreter = 'latex';
    l.Location = 'eastoutside';
    
    subplot(3,1,3)
    hold on
    plot(txs(:,1),torques,'b','LineWidth',3,'DisplayName', 'Torque Input $\tau$ in N*m');
%     plot(0.05*(1:length(q))',inputs,'k','LineWidth',3,'DisplayName', 'Pranav''s Torque Input $\tau$ in N*m');
    hold off
    title(titl)
    title('Torque Input (Control Signal)')
    xlabel('time (t) in seconds','interpreter','latex')
    ylabel('Torque $(\tau)$ in $Nm$','interpreter','latex')
    l = legend('show');
    l.Interpreter = 'latex';
    l.Location = 'eastoutside';
end

%% Visualizing Other Optimization 
function [J,q,qdot,input] = get_other_data_cost(filename)
    data = csvread(filename);
    q = data(:,1);
    qdot = data(:,2);
    input = data(:,3);
    J = zeros(size(q));
    for i = 1:length(q)
        J(i) = getcost([q(i),qdot(i)],[pi,0],input(i));
    end
    for i = 1:length(q)
        J(i) = sum(J(i:end));
    end
end

function [x,y,z] = get_other_cylindrical_cost(rmean,qactual,J,kcost)
    ractual = zeros(size(qactual(:,1)));
    for i = 1: length(qactual(:,1))
        ractual(i) = (rmean + J(i))+10;
    end
    x = ractual.*cos(qactual(:,1));
    y = ractual.*sin(qactual(:,1));
    z = qactual(:,2);
end

function J = getcost(x, xd, torque)
    Qx = [1/pi^2 0; 0 1/36];
    ka = 1/100;
    state_error = (x-xd)*Qx*( x-xd)';
    input_error = torque^2 * ka;
    time_error = 1;
    J = state_error + input_error + time_error;
end

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