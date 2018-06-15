clear all
t = 0;
x = [0,0];
torque = 10;
tic
[t,x] = xnplusone(t,x,torque)
[t,x] = xnplusone(t,x,torque, 'StepSize',0.1,...
		'AngleResolution',1e-1,'SpeedResolution', 1e-1,...
		'TorqueResolution', 1e-1)