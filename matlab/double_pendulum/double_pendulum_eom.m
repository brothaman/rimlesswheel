%% calculate the lagrangian
clear 
close all 
clc

lagrangian
eom

%% perform the ODE45
options = odeset('RelTol',1e-12,'AbsTol',1e-18,'Events', @myEvent);
t0 = 0;
tf = 5;
x0 = [15*pi/180 0 0 0];
tspan = t0:1e-3:tf;
[T,Y] = ode45(@(t,x)xdot(t,x,M,D), tspan, x0, options);


%% plots
% plot of state
fig1 = figure;
hold on
plot(T, Y(:,1), "b-o",'DisplayName','$$\theta_1$$')
plot(T, Y(:,2), "r-+",'DisplayName','$$\dot\theta_1$$')
plot(T, Y(:,3), "g-o",'DisplayName','$$\theta_2$$')
plot(T, Y(:,4), "y-+",'DisplayName','$$\dot\theta_2$$')
xmax = T(Y(:,2)==max(Y(:,2)));
vline(xmax)
x_1 = xmax;
x_2 = x_1;
y_1 = Y(T==xmax,1);
y_2 = Y(T==xmax,2);
str1 = strcat('\leftarrow Max occuring at (', string(x_1), ', ', string(y_1), ')');
str2 = strcat('\leftarrow Max occuring at (', string(x_2), ', ', string(y_2), ')');
text(x_1,y_1,str1)
text(x_2,y_2,str2)
hold off
leg = legend('show');
set(leg,'Interpreter','latex')

%% Plot the total Kinetic Energy
PE = subs(PE,symbolic_variables, physical_variables);
KE = subs(KE,symbolic_variables, physical_variables);
PE = str2func(strcat('@(x1,x2,x3,x4)', char(PE)));
KE = str2func(strcat('@(x1,x2,x3,x4)', char(KE)));

PEs = zeros(length(T),1);
KEs = zeros(length(T),1);

for i = 1:length(T)
	PEs(i) = PE(Y(i,1),Y(i,2), Y(i,3),Y(i,4));
	KEs(i) = KE(Y(i,1),Y(i,2), Y(i,3),Y(i,4));
end
fig3 = figure;
plot(T,PEs+KEs, 'b-o', 'DisplayName', 'Total Kinetic Energy')
legend('show')
hold off

%% animate the pendulum
fig4 = figure
tstep = t0:tf:(tf-t0)/1e3;
Y1 = Y(:,1);
Y2 = Y(:,3);
x1s = L1.*sin(Y1);
x2s = x1s+L2.*sin(Y1+Y2);
y1s = L1.*cos(Y1);
y2s = y1s+L2.*cos(Y1+Y2);
points = [x1s(:),y1s(:),x2s(:),y2s(:)];
fig4 = animate_pendulum(fig4,points,0.0001,[-2,2,-2,2])


function [x, isterminal, direction] = xdot(t,x,M,D)
x_ = pinv(M(x))*(-D(x));
x = [
	x(2)
	x_(1)
	x(4)
	x_(2)
	];
end

function [value, isterminal, direction] = myEvent(T,Y)
value      = double(Y(1)>=45*pi/180);
isterminal = 1;   % Stop the integration
direction  = 0;
end
