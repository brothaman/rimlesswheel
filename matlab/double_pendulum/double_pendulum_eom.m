%% Robert Brothers BSME
% this program will generate the limit cycle for a single over simplified rimless wheel
% using ODE45
clear 
close all
addpath('../EOM')
syms m1 m2 l1 l2 g theta_1 thetadot_1 thetaddot_1 theta_2 thetadot_2 thetaddot_2 real
i = [1 0 0]'; j = [0 1 0]'; k = [0 0 1]';
c1 = cos(theta_1); s1 = sin(theta_1);
c2 = cos(theta_2); s2 = sin(theta_2);
R_theta1 = [
	c1 -s1 0
	s1  c1 0
	0    0 1
]

R_theta2 = [
	c2 -s2 0
	s2  c2 0
	0    0 1
]
%% generate lagrangian -  matrices
r_cm1 = [0 -1 0]'; % unit vector pointing from the origin to the center of mass
r_cm2 = [0 -1 0]'; % unit vector pointing from cm1 to cm2
lcm1 = l1;
lcm2 = l2;
pcm1 = R_theta1*(lcm1*r_cm1);
pcm2 = pcm1 + R_theta1*R_theta2*(lcm2*r_cm2);

% height of each of the pendulums where theta is the absolute angles from the global ordinate
h1 = dot(j, pcm1);
h2 = dot(j, pcm2);

% velocities of each of the pendulums as a function of thetadot
W1 = [
	0 -thetadot_1 0
	thetadot_1 0 0
	0 0 0
];

W2 = [
	0 -thetadot_2 0
	thetadot_2 0 0
	0 0 0
];

v1 = W1*R_theta1*(lcm1*r_cm1)
v2 = v1 + W2*R_theta2*(lcm2*r_cm2)

% make edits here to change from ideal to real pendulum
I1 = m1*lcm1^2/12;
I2 = m2*lcm2^2/12;
K1 = m1*dot(v1,v1)/2 + I1 * thetadot_1^2;
K2 = m2*dot(v2,v2)/2 + I2 * thetadot_2^2;
P1 = m1*g*h1;
P2 = m2*g*h2;
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
EOM1 = simplify(dldtheta1 - ddtdldthetadot1);
EOM1 = collect(EOM1, [thetaddot_1, thetaddot_2, sin(theta_1), sin(theta_2)])
MM = 
M11 = 
dldtheta2 = diff(lagrangian, theta_2);
dldthetadot2 = diff(lagrangian, thetadot_2);
ddtdldthetadot2 = ddt(dldthetadot2, theta);
EOM2 = simplify(dldtheta2 - ddtdldthetadot2);
EOM2 = collect(EOM2, [thetaddot_1, thetaddot_2, sin(theta_1), sin(theta_2)])


%{
%% set up the state space equation
% theta1 = x1, theta2 = x2, thetadot1 = x3, thetadot2 = x4
syms x1 x2 x3 x4 
M1 = 1;
M2 = 1;
G = 9.81; % in the +x direction
L1 = 1;
L2 = 1;
symbolic_variables = [m1,m2,l1,l2,g,theta_1,thetadot_1,theta_2,thetadot_2];
physical_variables = [M1,M2,L1,L2,g,     x1,        x2,     x3,        x4];
%M11 = simplify(subs(eqn3,{thetaddot_1, thetaddot_2, thetadot_1, thetadot_2, g, m1, m2},{1,0,0,0,0,0,0}))
x2dot = solve(EOM1, thetaddot_1);
x2dot = vpa(subs(x2dot,symbolic_variables,physical_variables));
x2dot = str2func(strcat('@(x1,x2,x3,x4) ',char(x2dot)));

x4dot = solve(EOM2, thetaddot_2);
x4dot = vpa(subs(x4dot,symbolic_variables,physical_variables));
x4dot = str2func(strcat('@(x1,x2,x3,x4) ',char(x4dot)));
%}
%{
x_dot = @(t,x)... 
	[
		x(2)
 		x2dot(x(1),x(2),x(3),x(4))
		x(4)
		x4dot(x(1),x(2),x(3),x(4))
	];

%% perform the ODE45
options = odeset('RelTol',1e-12,'AbsTol',1e-18);
t0 = 0;
tf = 5;
x0 = [15*pi/180 0 0 0];
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
L = vpa(subs(lagrangian, symbolic_variables, physical_variables));
L = str2func(strcat('@(x1,x2,x3,x4) ',char(L)));
P = vpa(subs(P, symbolic_variables, physical_variables));
P = str2func(strcat('@(x1,x2,x3,x4) ',char(P)));
K = vpa(subs(K, symbolic_variables, physical_variables));
K = str2func(strcat('@(x1,x2,x3,x4) ',char(K)));
for i = 1:length(T)
	KE(i) = K(Y(i,1),Y(i,2), Y(i,3), Y(i,4));
	PE(i) = P(Y(i,1),Y(i,2), Y(i,3), Y(i,4));
    E(i) = KE(i) + PE(i);
end
hold on
plot(T, E, 'DisplayName', 'Energy')
% plot(T,PE, 'DisplayName', 'Potential Energy');
% plot(T,KE, 'DisplayName', 'Kinetic Energy')
title('Totla Energy of Pendulum')
xlabel('time')
ylabel('$$Energy\ E(\theta,\dot\theta)$$','Interpreter','latex')
%}
