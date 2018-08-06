%% Visualize the cost network
addpath ../lib
load ../lib/cost_network.mat
statenvalues = get_state_n_value(network);
fig = figure;
fig1 = figure;
fig2 = figure;
rmean = 100;
k = 10;
kspeeds = k;
kcost = 1/7;
N = 50;
clear x y z

% animate the pendulum and generate the q_actual
[qactual,txs,torques] = animate_pendulum(fig, network, N, all_angles, all_speeds,'Strong Pendulum [0,0] to [\pi,0]',0);

% plot network on a disk
[x,y] = get_CN_disk_data(rmean,k,all_angles,all_speeds);
% plot_low_density_scatter(fig1,x,y,[4,20])
% plot_low_density_surf(fig1,x,y,[4,20])
z = get_disk_cost_height(kcost,all_angles, all_speeds, statenvalues);
[xx,yy,zz] = get_actual_data_for_disk(rmean,qactual,statenvalues,k,kcost);
fig1 = visualize_cost_network_on_disk(fig1,x,y,z,xx,yy,zz,'Discoidal Representation of Strong Pendulum''s Cost Network');
view(0, 45)
saveas(fig1, 'images/underactuated_network_on_disk_isometric.pdf','pdf')

% plot the network on a cylinder
[x,y,z] = get_CN_cylinder_data(rmean,all_angles,all_speeds,statenvalues);
[xx,yy,zz] = get_actual_data_for_cylinder(rmean,qactual,statenvalues);
fig2 = visualize_cost_network_on_cylinder(fig2,x,y,z,xx,yy,zz,'Cylindrical Representation of the Strong Pendulum''s Cost Network');
shading interp
saveas(fig1, 'images/underactuated_network_on_cylinder_isometric.pdf','pdf')

% saveas(fig1, 'test_plot.tif','tiffn')
% saveas(fig1, 'test_plot.jpg','jpeg')
% saveas(fig1, 'test_plot.ppm','ppmraw')
% saveas(fig1, 'test_plot.pdf','pdf')

% rotate the cyclinder's plot
% rotating_the_cylindrical_cost_network(fig,x,y,z)
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
            if isempty(network{i,j}.optimal_value)
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

function [x,y,z] = get_actual_data_for_cylinder(rmean,qactual,statenvalues)
    ractual = zeros(size(qactual(:,1)));
    for i = 1: length(qactual(:,1))
        ractual(i) = (rmean + get_value_at_state(qactual(i,:), statenvalues))+5;
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
        plot3(xx,yy,zz,'k','LineWidth',5,'DisplayName','Path Traveled');
        hold off
    end
    
    title(titl)
    zlabel('Cost to Navigate to the Goal')
    ylabel('y-position of Pendulum - Radius Indicates Cost')
    xlabel('x-position of Pendulum - Radius Indicates Cost')
end

function fig = rotating_the_cylindrical_cost_network(fig,x,y,z)
    figure(fig)
    C = x.^2 +y.^2;
    h = surf(x,y,z,C,'DisplayName','Cost Network');
    title('Cylindrical Representation of Cost Network')
    shading interp
    for i = 1:10
        rotate(h,[0 0 1],5)
        saveas(fig,['images/test_plot' int2str(i) '.eps'],'epsc')
    end
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
            z(i,j) = k*get_value_at_state([all_angles(i) all_speeds(j)], statenvalues);
        end
    end
end

function [x,y,z] = get_actual_data_for_disk(rmean,qactual,statenvalues,k,kcost)
    ractual = rmean + k*qactual(:,2);
    x = ractual.*cos(qactual(:,1));
    y = ractual.*sin(qactual(:,1));
    z = zeros(size(x));
    for j = 1:length(qactual(:,1))
        z(j) = kcost*get_value_at_state(qactual(j,:),statenvalues)+.1;
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
        plot3(xx,yy,zz,'k','LineWidth',5);
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
    scatter(x,y,zeros(size(x)),'b','DisplayName','States')  
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    legend('show')
    hold off
end

function plot_low_density_surf(fig, x, y, res)
    x = x(1:res(1):end,1:res(2):end);
    y = y(1:res(1):end,1:res(2):end);
    rmax = max(x(1,:));
    rmin = min(x(1,:));
    figure(fig)
    hold on
    surf(x,y,zeros(size(x)),'DisplayName','States')  
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    legend('show')
    hold off
end

%% Animate the pendulum
function [qactual,txs, torque] = animate_pendulum(fig,network,N,all_angles,all_speeds,titl,flag)
    torque = zeros(1,N);
    txs = zeros(N,3);
    phi = -pi/2;
    t = 0.05;
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
    
    for i = 1:length(P)
        [fig,phandle] = show_pendulum(fig,phandle,P{i});
        if flag
            saveas(fig, ['images/pend' int2str(i) '.jpg'],'jpeg')
        end
        pause(0.03);
    end
end