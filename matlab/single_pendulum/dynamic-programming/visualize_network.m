%% Visualize the cost network
addpath ../lib
load ../lib/cost_network.mat
statenvalues = get_state_n_value(network);
fig = figure;
rmean = 100;
k = 10;
kspeeds = k;
kcost = 1/7;
clear x y z

% plot network on a disk
[x,y] = get_CN_disk_data(rmean,k,all_angles,all_speeds);
z = get_disk_cost_height(kcost,all_angles, all_speeds, statenvalues);
[xx,yy,zz] = get_actual_data_for_disk(rmean,qactual,statenvalues,k,kcost);
fig = visualize_cost_network_on_disk(fig,x,y,z,xx,yy,zz);

% plot the network on a cylinder
[x,y,z] = get_CN_cylinder_data(rmean,all_angles,all_speeds,statenvalues);
[xx,yy,zz] = get_actual_data_for_cylinder(rmean,qactual,statenvalues);
fig = visualize_cost_network_on_cylinder(fig,x,y,z,xx,yy,zz);
shading interp
saveas(fig, 'test_plot.tif','tiffn')
saveas(fig, 'test_plot.jpg','jpeg')
saveas(fig, 'test_plot.ppm','ppmraw')
saveas(fig, 'test_plot.pdf','pdf')

% rotate the cyclinder's plot
rotating_the_cylindrical_cost_network(fig,x,y,z)
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
            state_value((i-1)*m + j,:) = [network{i,j}.state network{i,j}.optimal_value];
        end
    end
end

function J = get_value_at_state(state,network)
    J = network(sum(state - network(:,1:2),2) == 0,3);
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
    if length(varargin) ~= 3
        disp('no data for actual plot given or wrong size')
    else
        [xx,yy,zz] = deal(varargin{:});
        plot_every_thing = true;
    end
    
    C = x.^2 +y.^2;
    surf(x,y,z,C,'DisplayName','Cost Network');
    if plot_every_thing
        hold on
        plot3(xx,yy,zz,'k','LineWidth',5,'DisplayName','Path Traveled');
        hold off
    end
    
    title('Cylindrical Representation of Cost Network')
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
    r = sqrt(rmean + k*all_speeds);
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
    if length(varargin) ~= 3
        disp('no data for actual plot given or wrong size')
    else
        [xx,yy,zz] = deal(varargin{:});
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
    title('Discoidal Representation of Cost Network')
    zlabel('Cost to Navigate to the Goal')
    ylabel('y-position of Pendulum')
    xlabel('x-position of Pendulum')
end
