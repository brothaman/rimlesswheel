%% Robert Brothers BSME
% this program will generate the limit cycle for a single over simplified rimless wheel
% using ODE45
clear 
close all
addpath('../EOM')
syms m1 m2 l1 l2 g theta_1 thetadot_1 thetaddot_1 theta_2 thetadot_2 thetaddot_2 real
theta = [
	theta_1, thetadot_1
	thetadot_1, thetaddot_1
	theta_2, thetadot_2
	thetadot_2, thetaddot_2
];
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
% unit vector pointing from the origin to the center of mass
r_cm1 = R_theta1*[0 -1 0]'; 
% unit vector pointing from cm1 to cm2
r_cm2 = R_theta1*R_theta2*[0 -1 0]'; 
lcm1 = l1;
lcm2 = l2;
pcm1 = lcm1*r_cm1;
pcm2 = lcm2*r_cm2;

% height of each of the pendulums where theta is the absolute angles from the global ordinate
h1 = dot(j, pcm1);
h2 = dot(j, pcm2);
%h1 = -l1*cos(theta_1)
%h2 = -l1*cos(theta_1) - l2*cos(theta_1+theta_2); % testing temporary

% velocity is the derivative wrst time
v1 = simplify(cross(thetadot_1*k, pcm1))
v2 = simplify(v1 + cross(thetadot_2*k, pcm2))
%v1 = simplify(ddt(pcm1, theta))
%v2 = simplify(ddt(pcm2, theta))

% make edits here to change from ideal to real pendulum
I1 = m1*lcm1^2/12;
I2 = m2*lcm2^2/12;
K1 = m1*dot(v1,v1)/2 + I1 * thetadot_1^2;
K2 = m2*dot(v2,v2)/2 + I2 * thetadot_2^2;
K1 = m1*dot(v1,v1)/2 ;
K2 = m2*dot(v2,v2)/2 ;

% kinetic energy
KE = simplify(K1+K2);
%KE = 1/2*m1*l1^2*thetadot_1^2 + 1/2*m2*(l1^2*thetadot_1^2 + l2^2*thetadot_2^2 + 2*l1*l2*thetadot_1*thetadot_2*cos(theta_1 - theta_2));
% change potential energy 
P1 = m1*g*h1;
P2 = m2*g*h2;

% potential energy
PE = simplify(P1 + P2);

% lagrangian KE - PE
L = KE - PE;


