%% Robert Brothers BSME
% this program will generate the limit cycle for a single over simplified rimless wheel
% using ODE45
clear 
close all
addpath('/Users/rbrothers/GitHub/rimlesswheel/matlab/EOM')
syms m1 m2 l1 l2 g theta_1 thetadot_1 thetaddot_1 theta_2 thetadot_2 thetaddot_2 real

%% generate lagrangian
lcm1 = l1;
lcm2 = l2;
h1 = -lcm1*cos(theta_1);
h2 = h1 - lcm2*cos(theta_2 + theta_1)
v1 = lcm1*thetadot_1;
v2 = lcm2*thetadot_2;
% make edits here to change from ideal to real pendulum
I1 = m1*lcm1^2;
I2 = m2*lcm2^2;
K1 = I1*thetadot_1^2/2;
K2 = I2*thetadot_2^2/2
P1 = m1*g*h1;
P2 = m2*g*h2
lagrangian = (K1+K2) - (P1+P2);

%% form the equations of motion
theta = [
	theta_1, thetadot_1
	thetadot_1, thetaddot_1
	theta_2, thetadot_2
	thetadot_2, thetaddot_2
];
dldtheta1 = diff(lagrangian, theta_1);
dldthetadot1 = diff(lagrangian, thetadot_1);
ddtdldthetadot1 = ddt(dldthetadot1, theta);
EOM1 = dldtheta1 - ddtdldthetadot1;

dldtheta2 = diff(lagrangian, theta_2);
dldthetadot2 = diff(lagrangian, thetadot_2);
ddtdldthetadot2 = ddt(dldthetadot2, theta);
EOM2 = dldtheta2 - ddtdldthetadot2;


%% set up the state space equation
% theta1 = x1, theta2 = x2, thetadot1 = x3, thetadot2 = x4
syms x1 x2 x3 x4 
M1 = 1;
M2 = 1;
G = 9.81; % in the +x direction
L1 = 1;
L2 = 1;
x2dot = solve(EOM1, thetaddot_1);
x2dot = vpa(subs(x2dot,[m,g,l,theta_1, theta_2, thetadot_1 thetadot_2], [M,G,Length,x1,x2,x3,x4]));
x2dot = str2func(strcat('@(x1,x2,x3,x4) ',char(x2dot)));

x4dot = solve(EOM2, thetaddot_2);
x4dot = vpa(subs(x4dot,[m,g,l,theta_1, theta_2, thetadot_1, thetadot_2], [M,G,Length,x1,x2,x3,x4]));
x4dot = str2func(strcat('@(x1,x2,x3,x4) ',char(x4dot)));

x_dot = @(t,x)... 
	[
		x(2)
 		x2dot(x(1),x(2))
		x(4)
		x4dot(x(1),x(2))
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
