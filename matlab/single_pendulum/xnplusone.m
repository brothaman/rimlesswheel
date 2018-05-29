function [t,x] = xnplusone(t, x, varargin)
%% discretized time-invariant single tone pendulum
	defaults.torque = 0.0;
	defaults.direction = 1;
	defaults.stepsize = 1e-3;
	defaults.pres = 0.01;
	defaults.sres = 0.1;
	defaults.tres = 0.01;
	defaults.options = odeset('RelTol',1e-8,'AbsTol',1e-10);
	p = inputParser;
	addRequired(p, 't', @(x) isnumeric(x));
	addRequired(p, 'x', @(x) isnumeric(x));
	addParameter(p, 'Torque', defaults.torque, @(x) isnumeric(x));
	addParameter(p, 'StepSize', defaults.stepsize, @(x) isnumeric(x));
	addParameter(p, 'Direction', defaults.direction, @(x) x==1 || x==0);
	addParameter(p, 'AngleResolution', defaults.pres, @(x) isnumeric(x));
	addParameter(p, 'SpeedResolution', defaults.sres, @(x) isnumeric(x));
	addParameter(p, 'TorqueResolution', defaults.tres, @(x) isnumeric(x));
	addParameter(p, 'options', defaults.options)
	parse(p,t,x,varargin{:});

	p.Results
	% trucate input values
	x(1) = round(p.Results.x(1),-log10(p.Results.AngleResolution));
	x(2) = round(p.Results.x(2),-log10(p.Results.SpeedResolution));
	torque = round(p.Results.Torque, -log10(p.Results.TorqueResolution));

	% if model isn't loaded load it
	if exist('model') == 0
		load('lib/model.mat');
	end

	% set up the differential equations of motion
	xdot = @(t,x) [x(2); torque-model.D(x(1),x(2))/model.M(x(1),x(2))];

	% update current model characteristics 
	model.t0 = p.Results.t;
	model.tf = p.Results.t+p.Results.StepSize;
	model.tspan = [model.t0 model.tf];
	model.initial_conditions = x;

	% integrate to the next step
	[T,X] = ode45(@(t,x) xdot(t,x), model.tspan, model.initial_conditions, p.Results.options);
	t = T(end);
	x = X(end,:);
end
