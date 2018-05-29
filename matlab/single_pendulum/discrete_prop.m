%% DISCRETE PROP
% propagate through pendulum motion using difference equation
t = 0;
torque = 5;
x = [0 0];
stepsize = 0.01;
thresh = @(x) x > 178/180*pi && x < 182/180*pi;
T = [];
X = [];
anglenotreached = true;
% apply torque to system until the desired angle is reached
while (anglenotreached)
	[t,x] = xnplusone(t,x,'Torque',torque,'Stepsize', stepsize,'AngleResolution',1e-4,'SpeedResolution',1e-3);
	anglenotreached = ~thresh(x(1));
end

% show pendulum
show_pendulum(x);
