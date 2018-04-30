%{
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
];

R_theta2 = [
	c2 -s2 0
	s2  c2 0
	0    0 1
];
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
%h1 = -l1*cos(theta_1)
h2 = -l1*cos(theta_1) - l2*cos(theta_1+theta_2); % testing temporary

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

v1 = W1*R_theta1*(lcm1*r_cm1);
v2 = v1 + W2*R_theta2*(lcm2*r_cm2);

% make edits here to change from ideal to real pendulum
I1 = m1*lcm1^2/12;
I2 = m2*lcm2^2/12;
K1 = m1*dot(v1,v1)/2 + I1 * thetadot_1^2;
K2 = m2*dot(v2,v2)/2 + I2 * thetadot_2^2;
K1 = m1*dot(v1,v1)/2 ;
K2 = m2*dot(v2,v2)/2 ;

% kinetic energy
KE = simplify(K1+K2)
KE = 1/2*m1*l1^2*thetadot_1^2 + 1/2*m2*(l1^2*thetadot_1^2 + l2^2*thetadot_2^2 + 2*l1*l2*thetadot_1*thetadot_2*cos(theta_1 - theta_2));
% change potential energy 
P1 = m1*g*h1;
P2 = m2*g*h2;

% potential energy
PE = simplify(P1 + P2)

% lagrangian KE - PE
lagrangian = KE - PE;

%% form the equations of motion
theta = [
	theta_1, thetadot_1
	thetadot_1, thetaddot_1
	theta_2, thetadot_2
	thetadot_2, thetaddot_2
];
% -------------------------------------
% differentiation with respect to theta
% -------------------------------------
dldtheta1 = diff(lagrangian, theta_1);
dldthetadot1 = diff(lagrangian, thetadot_1);
ddtdldthetadot1 = ddt(dldthetadot1, theta);
EOM1 = simplify(dldtheta1 - ddtdldthetadot1);
EOM1 = collect(EOM1, [thetaddot_1, thetaddot_2, sin(theta_1), sin(theta_2)]);

% seperation of variables to produce the form M*xddot + D = 0
MM = subs(EOM1,[thetadot_2, g],[0,0]);
M11 = subs(MM, [thetaddot_1,thetaddot_2],[1,0]);
M12 = subs(MM, [thetaddot_1,thetaddot_2],[0,1]);
D1 = EOM1 - MM;

% ---------------------------------------
% differentiation with respect to theta 2
% ---------------------------------------
dldtheta2 = diff(lagrangian, theta_2);
dldthetadot2 = diff(lagrangian, thetadot_2);
ddtdldthetadot2 = ddt(dldthetadot2, theta);
EOM2 = simplify(dldtheta2 - ddtdldthetadot2);
EOM2 = collect(EOM2, [thetaddot_1, thetaddot_2, sin(theta_1), sin(theta_2)]);

% seperation of variables from the second equation
MM = subs(EOM2,[thetadot_1,g],[0,0])
M21 = subs(MM, [thetaddot_1,thetaddot_2],[1,0]);
M22 = subs(MM, [thetaddot_1,thetaddot_2],[0,1]);
D2 = EOM2 - MM

%}
lagrangian
eom
%% set up the state space equation
% theta1 = x1, theta2 = x2, thetadot1 = x3, thetadot2 = x4
syms x1 x2 x3 x4 
M1 = 1;
M2 = 2;
G = -9.81; % in the +x direction
L1 = 1;
L2 = 1;
symbolic_variables = [m1,m2,l1,l2,g,theta_1,thetadot_1,theta_2,thetadot_2];
physical_variables = [M1,M2,L1,L2,G,     x1,        x2,     x3,        x4];
M11 = subs(M11,symbolic_variables, physical_variables);
M12 = subs(M12,symbolic_variables, physical_variables);
M21 = subs(M21,symbolic_variables, physical_variables);
M22 = subs(M22,symbolic_variables, physical_variables);
D1 = subs(D1,symbolic_variables, physical_variables);
D2 = subs(D2,symbolic_variables, physical_variables);
M11 = str2func(strcat('@(x1,x2,x3,x4)', char(M11)));
M21 = str2func(strcat('@(x1,x2,x3,x4)', char(M21)));
M12 = str2func(strcat('@(x1,x2,x3,x4)', char(M12)));
M22 = str2func(strcat('@(x1,x2,x3,x4)', char(M22)));
D1 = str2func(strcat('@(x1,x2,x3,x4)', char(D1)));
D2 = str2func(strcat('@(x1,x2,x3,x4)', char(D2)));
M = @(x) [M11(x(1),x(2),x(3),x(4)), M12(x(1),x(2),x(3),x(4)); M21(x(1),x(2),x(3),x(4)), M22(x(1),x(2),x(3),x(4))];
D = @(x) [D1(x(1),x(2),x(3),x(4));D2(x(1),x(2),x(3),x(4))];


%% perform the ODE45
options = odeset('RelTol',1e-12,'AbsTol',1e-18);
t0 = 0;
tf = 5;
x0 = [45*pi/180 0 45*pi/180 0];
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
plot(T,PEs-KEs, 'b-o', 'DisplayName', 'Total Kinetic Energy')
legend('show')
hold off

%% animate the pendulum
% get the endpoints of each of the pendulums
% get equal timesteps
tstep = t0:tf:(tf-t0)/1e3;
Y1 = Y(:,1);
Y2 = Y(:,3);
x1s = L1.*sin(Y1);
x2s = x1s+L2.*sin(Y1+Y2);
y1s = -L1.*cos(Y1);
y2s = y1s-L2.*cos(Y1+Y2);
points = [x1s(:),y1s(:),x2s(:),y2s(:)];
animate_pendulum(points,0.001,[-2,2,-2,1])


function [x] = xdot(t,x,M,D)
x_ = M(x)\D(x);
x = [
	x(2)
	x_(1)
	x(4)
	x_(2)
	];
end


