function [J] = cost(X, a)
	t = 0;
	J = a^2;	
	[t,X] = xnplusone(t,X,'StepSize',0.01,...
		'AngleResolution',1e-4,'SpeedResolution', 1e-3,...
		'TorqueResolution', 1e-2);
	Xd = zeros(size(X)); Xd(1) = pi;
	J = J + dot(Xd-X,Xd-X);
end
