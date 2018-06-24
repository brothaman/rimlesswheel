clear 
close all
clc

global model
load('model.mat')

%% integrate between motions
N = 1e3;
model.initial_conditions = [ 0, 0, -pi/2, 0]';
model.t0 		= 0;
model.tf 		= 10;
model.tspan = model.t0:(model.tf - model.t0)/N:model.tf;
options = odeset('RelTol',1e-12,'AbsTol',1e-18,'Events', @myEvent);
[T,Y] = ode45(@(t,x) xdot(t,x), model.tspan, model.initial_conditions, options);

%% animate the pendulum
model.animate = figure;
Y1 = Y(:,1);
Y2 = Y(:,3);
x1s = model.L1.*sin(Y1);
x2s = x1s+model.L2.*sin(Y1+Y2);
y1s = model.L1.*cos(Y1);
y2s = y1s+model.L2.*cos(Y1+Y2);
points = [x1s(:),y1s(:),x2s(:),y2s(:)];
animate_pendulum(points, 'Figure', model.animate,'Pause', 0,  'TimeStep', 1e-2,'GraphDimensions',[-2,2,-2,2]);


%% event function
function [value, isterminal, direction] = myEvent(T,Y)
value      = double(Y(1)>=45*pi/180 || Y(1)<=-45*pi/180);
isterminal = 1;   % Stop the integration
direction  = 0;
end

%% equations of motion to integrate
function [x] = xdot(t,x)
global model
x_ = pinv(model.M(x))*(-model.D(x));
x = [
	x(2)
	x_(1)
	x(4)
	x_(2)
];
end
