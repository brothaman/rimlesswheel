clear
load '../data/RimlessStiffEOM.mat'

%{
	x1 = theta
	x2 = thetadot
	x3 = phi
	x4 = phidot
%}
% add the physical characteristics of the system
M1 = 1.0;% kg
M2 = 3.5;% kg
L1 = 0.5;% m
L2 = 0.2;% m
i1 = M1*L1^2/2;
i2 = M2*L2^2/3;
G = -9.81;% m/s^2

% substitue all the system's constant variables
syms I1 I2 m1 m2 l1 l2 g theta thetadot phi phidot x1 x2 x3 x4 gamma real
thetadoubledot__ = thetadoubledot_;
phidoubledot__ = phidoubledot_;
thetadoubledot_ = subs(thetadoubledot_,...
	[I1,I2,m1,m2,l1,l2,g,theta, thetadot, phi, phidot],...
	[i1,i2,M1,M2,L1,L2,G,x1,    x2,       x3,  x4]);
phidoubledot_   = subs(phidoubledot_  ,...
	[I1,I2,m1,m2,l1,l2,g,theta, thetadot, phi, phidot], ...
	[i1,i2,M1,M2,L1,L2,G,x1,    x2,       x3,  x4]);

pow = @(x,y) x^y;
thetadoubledot_ = str2func(strcat('@(x1,x2,x3,x4)',char(vpa(thetadoubledot_))));
phidoubledot_ = str2func(strcat('@(x1,x2,x3,x4)',char(vpa(phidoubledot_))));
% generat3 the state space equations
%{
	x1 = theta
	x2 = thetadot
	x3 = phi
	x4 = phidot

	x1dot = x2
	x2dot = f(x1,x2,x3,x4)
	x3dot = x4
	x4dot = g(x1,x2,x3,x4)	
%}
xdot = @(t,x) ...
[
	x(2)
	thetadoubledot_(x(1),x(2),x(3),x(4))
	x(4)
	phidoubledot_(x(1),x(2),x(3),x(4))
];
% use ODE45 to cycle through some movement
init_cons = [5*pi/180,0,45*pi/180,0];
tspan = [0 5];
[T,Y] = ode45(xdot, tspan, init_cons);

%% visualization
fig = figure;
hold on
plot(T,Y(:,1),'DisplayName','angle \theta')
plot(T,Y(:,2),'DisplayName','angle \theta_{dot}')
plot(T,Y(:,3),'DisplayName','angle \phi')
plot(T,Y(:,4),'DisplayName','angle \phi_{dot}')

legend('show')
dlmwrite('../data/jointdata.txt', Y)

% sum the kinetic and potential energy at each step
L = vpa(...
	subs(...
		L, ...
		[I1,I2,m1,m2,l1,l2,g,theta, thetadot, phi, phidot, gamma], ...
		[i1,i2,M1,M2,L1,L2,G,x1,x2,x3,x4,0]));
L = str2func(strcat('@(x1,x2,x3,x4) ',char(L)));
P = vpa(...
	subs(...
		P, ...
		[I1,I2,m1,m2,l1,l2,g,theta, thetadot, phi, phidot, gamma], ...
		[i1,i2,M1,M2,L1,L2,G,x1,x2,x3,x4,0]));
P = str2func(strcat('@(x1,x2,x3,x4) ',char(P)));
K = vpa(...
	subs(...
		K, ...
		[I1,I2,m1,m2,l1,l2,g,theta, thetadot, phi, phidot, gamma], ...
		[i1,i2,M1,M2,L1,L2,G,x1,x2,x3,x4,0]));
K = str2func(strcat('@(x1,x2,x3,x4) ',char(K)));
for i = 1:length(Y)
% 	 E(i) = L(Y(i,1),Y(i,2),Y(i,3),Y(i,4));
	KE(i) = K(Y(i,1),Y(i,2),Y(i,3),Y(i,4));
	PE(i) = P(Y(i,1),Y(i,2),Y(i,3),Y(i,4));
    E(i) = KE(i) + PE(i);
end

fig2 = figure;
hold on
plot(T, E,'DisplayName','Energy')
% plot(T,KE,'DisplayName', 'Kinetic Energy')
% plot(T,PE,'DisplayName', 'Potential Energy')
