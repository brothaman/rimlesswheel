function show_cost_network(figure_file_name,path,all_angles,all_speeds,network)
statenvalues = get_state_n_value(network);
rmean = 200;
k = 10;
kcost = 1/7;

fig1 = figure;
fig2 = figure;

% plot network on a disk
% [x,y] = get_CN_disk_data(rmean,k,all_angles,all_speeds);
% z = get_disk_cost_height(kcost,all_angles, all_speeds, statenvalues);
% visualize_cost_network_on_disk(fig1,x,y,z,figure_file_name);
% view(0, 45)
% zlim([0 50])
% xlim([-320 320])
% ylim([-320 320])
% saveas(fig1, [path 'discoidal_' figure_file_name '.jpg'],'jpeg')

% plot the network on a cylinder
[x,y,z] = get_CN_cylinder_data(rmean,all_angles,all_speeds,statenvalues);
fig2 = visualize_cost_network_on_cylinder(fig2,x,y,z,figure_file_name);
shading interp
zlim([-10 10])
xlim([-550 550])
ylim([-550 550])
saveas(fig2, [path 'cylindrical_' figure_file_name '.jpg'],'jpeg')
end

%% functions
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
