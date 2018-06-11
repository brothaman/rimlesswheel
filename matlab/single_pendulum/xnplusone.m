function [t,x] = xnplusone(t, x, Torque, varargin)
%% discretized time-invariant single tone pendulum
	global model
	defaults.direction = 1;
	defaults.stepsize = 1e-3;
	defaults.pres = 0.001;
	defaults.sres = 0.01;
	defaults.tres = 0.01;
	defaults.options = odeset('RelTol',1e-8,'AbsTol',1e-10);
	p = inputParser;
	addRequired(p, 't', @(x) isnumeric(x));
	addRequired(p, 'x', @(x) isnumeric(x));
	addRequired(p, 'Torque', @(x) isnumeric(x));
	addParameter(p, 'StepSize', defaults.stepsize, @(x) isnumeric(x));
	addParameter(p, 'Direction', defaults.direction, @(x) x==1 || x==0);
	addParameter(p, 'AngleResolution', defaults.pres, @(x) isnumeric(x));
	addParameter(p, 'SpeedResolution', defaults.sres, @(x) isnumeric(x));
	addParameter(p, 'TorqueResolution', defaults.tres, @(x) isnumeric(x));
	addParameter(p, 'options', defaults.options);
	parse(p,t,x,Torque,varargin{:});

	% if model isn't loaded load it
	if ~isstruct(model)
		disp('Loading model *')
		load('lib/model.mat');
		disp('Model loaded *')
    end
	% set up the differential equations of motion
	xdot = @(t,x) [x(2); (-p.Results.Torque-model.D(x(1),x(2)))/model.M(x(1),x(2))];

	% update current model characteristics 
	model.t0 = p.Results.t;
	model.tf = p.Results.t+p.Results.StepSize;
	model.tspan = [model.t0 model.tf];
	model.initial_conditions = x;

	% integrate to the next step
	[T,X] = ode45(@(t,x) xdot(t,x), model.tspan, model.initial_conditions, p.Results.options);
	t = T(end);
	x = X(end,:);

	% map angular values over
	if(x(1) > 2*pi)
		x(1) = wrapTo2Pi(x(1));
	end

	if(x(1) < 0)
		x(1) = wrapTo2Pi(x(1));
    end
end
