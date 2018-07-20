function [t,x] = xnplusone( x, Torque, stepsize)
%% discretized time-invariant single tone pendulum
% 	global model
	options = odeset('RelTol',1e-8,'AbsTol',1e-10);
	

    M = @(theta,thetadot)-1;
    D = @(theta,thetadot)-(981*sin(theta))/100;
	xdot = @(t,x) [x(2); (Torque-D(x(1),x(2)))/M(x(1),x(2))];
    
	% integrate to the next step
	[T,X] = ode45(@(t,x) xdot(t,x), [0 stepsize], x, options);
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
