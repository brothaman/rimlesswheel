%% DISCRETE PROP
% propagate through pendulum motion using difference equation
L = 1;
t = 0;
torque = 10;
x = [0 0];
stepsize = 0.01;
thresh = @(x) x > 178/180*pi && x < 182/180*pi;
anglenotreached = true;
fig = figure;
axis([-2 2 -2 2])
phandle = [];

% apply torque to system until the desired angle is reached
while (anglenotreached)
	[t,x] = xnplusone(t,x,...
		'Torque',torque,...
		'Stepsize', stepsize,...
		'AngleResolution',1e-4,...
		'SpeedResolution',1e-3)
	anglenotreached = ~thresh(x(1));
	
	% show pendulum
	P = {L*[0 0 cos(x(1)) sin(x(1))]};
	[fig, phandle] = show_pendulum(fig,phandle, P);
	pause(1e-2)
end

