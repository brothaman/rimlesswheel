%% Robert Brothers BSME
% this program will generate the limit cycle for a single over simplified rimless wheel
% using ODE45
clear 
close all
syms m g l I theta thetadot thetaddot

% generate lagrangian
h = -l*cos(theta);
v = l*thetadot;
I = m*l^2/3;
P = m*g*h;
%K = I*thetadot^2/2;
K = m*v^2/2;
lagrangian = K - P;

% form the equations of motion
dldtheta = diff(lagrangian, theta)
dldthetadot = diff(lagrangian, thetadot)
ddtdldthetadot = diff(dldthetadot, theta)*thetadot + diff(dldthetadot, thetadot)*thetaddot;
EOM = dldtheta - ddtdldthetadot

% set up the state space equation
syms x1 x2
M = 1;
G = 9.81; % in the +x direction
L = 1;
inertia = M*L^2/3;
pow = @(x,y) x^y;
x2dot = solve(EOM, thetaddot);
x2dot = vpa(subs(x2dot,[m,g,l,theta,thetadot], [M,G,L,x1,x2]));
x2dot = str2func(strcat('@(x1,x2) ',ccode(x2dot)));

x_dot = @(t,x)... 
	[
		x(2)
 		x2dot(x(1),x(2))
	];

x_dot = @(t,x)... 
	[
		x(2)
 		-9.81*sin(x1)
	];

% perform the ODE45
options = odeset('RelTol',1e-10)
t0 = 0;
tf = 5;
x0 = [15*pi/180 0];
tspan = [t0 tf];
[T,Y] = ode45(x_dot, tspan, x0, options);

fig1 = figure;
plot(T, Y, "b-o")

fig2 = figure;
plot(Y(:,1), Y(:,2))
title("Limit Cycle")
xlabel("theta")
ylabel("theta_dot")

fig3 = figure
L = vpa(subs(lagrangian, [m,g,l,I,theta,thetadot], [M,G,L,inertia,x1,x2]));
L = str2func(strcat('@(x1,x2) ',ccode(L)));
P = vpa(subs(P, [m,g,l,I,theta,thetadot], [M,G,L,inertia,x1,x2]));
P = str2func(strcat('@(x1,x2) ',ccode(P)));
K = vpa(subs(K, [m,g,l,I,theta,thetadot], [M,G,L,inertia,x1,x2]));
K = str2func(strcat('@(x1,x2) ',ccode(K)));
for i = 1:length(T)
	E(i) = L(Y(i,1),Y(i,2));
	KE(i) = K(Y(i,1),Y(i,2));
	PE(i) = P(Y(i,1),Y(i,2));
end
hold on
plot(T, E, 'DisplayName', 'Energy')
%plot(T,PE, 'DisplayName', 'Potential Energy');
%plot(T,KE, 'DisplayName', 'Kinetic Energy')
title('Totla Energy of Pendulum')
xlabel('time')
ylabel('Energy E(\theta,$\dot\theta$)')
