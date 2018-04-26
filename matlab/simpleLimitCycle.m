%% Robert Brothers BSME
% this program will generate the limit cycle for a single over simplified rimless wheel
% using ODE45
clear 
close all
syms m g l I theta thetadot thetaddot real
addpath('double_pendulum/')

%% generate lagrangian
lcm = l;
h = -lcm*cos(theta);
v = lcm*thetadot;
I = m*l^2/3;
K = I*thetadot^2/2;
K = m*v^2/2;
P = m*g*h;
lagrangian = K - P;

%% form the equations of motion
dldtheta = diff(lagrangian, theta);
dldthetadot = diff(lagrangian, thetadot);
ddtdldthetadot = diff(dldthetadot, theta)*thetadot + diff(dldthetadot, thetadot)*thetaddot;
EOM = dldtheta - ddtdldthetadot;

%% set up the state space equation
syms x1 x2
M = 1;
G = 9.81; % in the +x direction
Length = 1;
pow = @(x,y) x^y;
x2dot = solve(EOM, thetaddot);
pretty(x2dot)
x2dot = vpa(subs(x2dot,[m,g,l,theta,thetadot], [M,G,Length,x1,x2]));
x2dot = str2func(strcat('@(x1,x2) ',char(x2dot)));

x_dot = @(t,x)... 
	[
		x(2)
 		x2dot(x(1),x(2))
	];

%% perform the ODE45
options = odeset('RelTol',1e-12,'AbsTol',1e-18);
t0 = 0;
tf = 5;
x0 = [15*pi/180 0];
tspan = [t0 tf];
[T,Y] = ode45(x_dot, tspan, x0, options);

%% plots
% plot of state
fig1 = figure;
hold on
plot(T, Y(:,1), "b-o",'DisplayName','$$\theta$$')
plot(T, Y(:,2), "r-+",'DisplayName','$$\dot\theta$$')
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

% Plot of Limit Cycle
fig2 = figure;
plot(Y(:,1), Y(:,2))
title("Limit Cycle")
xlabel("$$\theta$$",'Interpreter','latex')
ylabel("$$\dot\theta$$",'Interpreter','latex')

% plot of energy
fig3 = figure;
L = vpa(subs(lagrangian, [m,g,l,theta,thetadot], [M,G,Length,x1,x2]));
L = str2func(strcat('@(x1,x2) ',char(L)));
P = vpa(subs(P, [m,g,l,theta,thetadot], [M,G,Length,x1,x2]));
P = str2func(strcat('@(x1,x2) ',char(P)));
K = vpa(subs(K, [m,g,l,theta,thetadot], [M,G,Length,x1,x2]));
K = str2func(strcat('@(x1,x2) ',char(K)));
for i = 1:length(T)
	KE(i) = K(Y(i,1),Y(i,2));
	PE(i) = P(Y(i,1),Y(i,2));
    E(i) = KE(i) + PE(i);
end
hold on
plot(T, E, 'DisplayName', 'Energy')
% plot(T,PE, 'DisplayName', 'Potential Energy');
% plot(T,KE, 'DisplayName', 'Kinetic Energy')
title('Totla Energy of Pendulum')
xlabel('time')
ylabel('$$Energy\ E(\theta,\dot\theta)$$','Interpreter','latex')


x1s = Length.*sin(Y(:,1));
y1s = -Length.*cos(Y(:,1));
points = [x1s(:),y1s(:)];
animate_pendulum(points,0)
