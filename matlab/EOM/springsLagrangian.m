% pkg load symbolic
syms k g m1 m2 l2 l0 l ldot lddot phi theta phidot thetadot phiddot thetaddot gamma real

l1 = l0+l;
x = [1,0,0]'; y = [0,1,0]'; z = [0,0,1]';
l1_ = l1*[sin(theta), cos(theta),0]';
l2_ = l2*[cos(phi-pi/2), sin(phi-pi/2), 0]';

h1 = dot(y,l1_) + dot(y,l1*[cos(gamma);sin(gamma);0]);
h2 = h1 + dot(y, l2_) + dot(y,l2*[cos(gamma);sin(gamma);0]);

thetadot_ = thetadot*z;
phidot_   = phidot*z;

%% calculate the Lagrangian
% potential and kinetic energy of the wheel
PEm = m1*g*h1 + k*l^2;
KEm = m1/2*(l1^2*thetadot^2 + ldot^2) + I1*thetadot^2/2;

% potential and kinetic energy of the torso
PEM = m2*g*h2;
KEM = m2/2*(norm(cross(thetadot_,l1_) + cross(phidot_, l2_) + ldot*l1_/l1)^2) + I2*phidot^2/2;

% Lagrangian is the combination of Poential Energy - Kinetic Energy https://en.wikipedia.org/wiki/Lagrangian_mechanics
L = KEm+KEM - PEm-PEM;

x_xdot = [
	theta,    thetadot
	thetadot, thetaddot
	l,        ldot
	ldot,     lddot
	phi,      phidot
	phidot,   phiddot
];
