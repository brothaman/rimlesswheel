%% Visualize the cost network
addpath ../lib
load ../lib/underactuated_cost_network.mat

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
%% functions
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