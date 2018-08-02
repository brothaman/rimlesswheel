%% Visualize the cost network
addpath ../lib
load ../lib/cost_network.mat
statenvalues = get_state_n_value(network);
fig = figure;
rmean = 100;
k = 10;

clear x y z

r = rmean + k*all_speeds;
x = cos(all_angles').*r;
y = sin(all_angles').*r;
for i = 1:length(all_angles)
    for j = 1:length(all_speeds)
        z(i,j) = 1/7*get_value_at_state([all_angles(i) all_speeds(j)], statenvalues);
    end
end
surf(x,y,z)
shading interp
% x = reshape(x,[prod(size(x)),1]);
% y = reshape(y,[prod(size(y)),1]);

hold on
% scatter3(x,y,z(:),'DisplayName','States')
plot_circle(fig, max(r), [0 0],'Max Velocity')
plot_circle(fig, min(r), [0 0],'Min Velocity')
ractual = rmean + k*qactual(:,2);
xactual = ractual.*cos(qactual(:,1));
yactual = ractual.*sin(qactual(:,1));
for j = 1:length(qactual(:,1))
    zactual(j) = 1/7*get_value_at_state(qactual(j,:),statenvalues)+.1;
end
plot3(xactual,yactual,zactual,'k','LineWidth',5,'DisplayName','Path traveled')
title('2-D Representation of Cost network')
legend('show')

%% plot the network on a cylinder
fig2 = figure;
x = [];
y = [];
for i = 1:length(all_angles)
    for j = 1:length(all_speeds)
        x(i,j) = (rmean + get_value_at_state([all_angles(i) all_speeds(j)], statenvalues)) * cos(all_angles(i));
        y(i,j) = (rmean + get_value_at_state([all_angles(i) all_speeds(j)], statenvalues)) * sin(all_angles(i));
    end
end
z = ones(size(x)).*all_speeds;
C = x.^2 +y.^2;
cyl_cost = surf(x,y,z,C)
for i = 0:45
    rotate(cyl_cost,[0 0 1],i)
    pause(0.3)
end
% scatter3(x(:),y(:),z(:),'DisplayName','States')
%% functions
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
function show_3d_scatter()
    x = r*cos(theta);
    y = r*sin(theta);
    z = k*velocity;
end

function show_2d_scatter(fig)
    figure(fig);
    rmean = 15;
    k = 1/2;
    r = rmean + k*all_speeds;
    x = cos(all_angles).*r;
    y = sin(all_angles).*r;
    x = reshape(x,[prod(size(x)),1]);
    y = reshape(y,[prod(size(y)),1]);
    plot(x,y)
    title('2-D Representation of Cost network')
end
function radius = get_radius(rmean, velocity, k)
    radius = rmean + k*velocity;
end

function plot_circle(fig, radius,center,linename)
    figure(fig);
    N = ceil(pi*2*radius/.1);
    theta = 0:2*pi/ceil(pi*2*radius/.1):2*pi;
    x = center(1) + radius*cos(theta');
    y = center(2) + radius*sin(theta');
    plot(x,y,'LineWidth',5, 'DisplayName',linename)
end