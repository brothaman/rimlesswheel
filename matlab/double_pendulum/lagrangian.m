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
g_ = [0 -g 0];
i = [1 0 0]'; j = [0 1 0]'; k = [0 0 1]';
c1 = cos(theta_1); s1 = sin(theta_1);
c2 = cos(theta_2); s2 = sin(theta_2);

% rotate from frame 1 to frame 0
R10 = [
	c1 -s1 0
	s1  c1 0
	0    0 1
];

% rotate from frame 2 to frame 1
R21 = [
	c2 -s2 0
	s2  c2 0
	0    0 1
];

%% generate lagrangian -  matrices
% position of the center of masses with respect to the global frame
lcm1 = l1;
lcm2 = l2;
p11 = lcm1*[1 0 0]';
p22 = lcm2*[1 0 0]';
p21 = R21*p22;
p10 = R10*p11;
p20 = R10*(l1*[1 0 0]' + p21);

% height of each of the pendulums where theta is the absolute angles from the global ordinate
h1 = dot(j, p10);
h2 = dot(j, p20);
h1 = -l1*cos(theta_1);
h2 = h1 -l2*cos(theta_2);

% velocity is the derivative wrst time
v1 = simplify(cross(thetadot_1*k, p10))
v2 = simplify(v1 + cross(thetadot_2*k, p20))

% make edits here to change from ideal to real pendulum
I1 = m1*lcm1^2/12;
I2 = m2*lcm2^2/12;
K1 = m1*dot(v1,v1)/2 + I1 * thetadot_1^2;
K2 = m2*dot(v2,v2)/2 + I2 * thetadot_2^2;
K1 = m1*dot(v1,v1)/2 ;
K2 = m2*dot(v2,v2)/2 ;

% kinetic energy
KE = simplify(K1+K2);
KE = 1/2*m1*l1^2*thetadot_1^2 + 1/2*m2*(l1^2*thetadot_1^2 + l2^2*thetadot_2^2 + 2*l1*l2*thetadot_1*thetadot_2*cos(theta_1 - theta_2));
% change potential energy 
P1 = m1*dot(g_, p10);
P2 = m2*dot(g_, p20);

% potential energy
PE = simplify(P1 + P2);

% lagrangian KE - PE
L = KE - PE;


