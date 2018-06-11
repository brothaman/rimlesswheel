function [J] = cost(Xd, Xin, X, torque)
% 	t = 0;
% 	R = 0.001;
% 	Q = [
% 		15 0
% 		0 1
% 	];
% 	Arc = [
% 		0 0
% 		0 0
% 	];
% 	X(1) = round2(X(1),pi,1,1);
% 	X(2) = round2(X(2),1,1,1);
% 	X0 = X;
% 	[t,X] = xnplusone(t,X,'StepSize',0.1,'Torque',a,...
% 		'AngleResolution',1e-1,'SpeedResolution', 1e-1,...
% 		'TorqueResolution', 1e-1);
% 	X = X';
% 	Xd = zeros(size(X)); Xd(1) = pi;
% 	X0  = reshape(X0,size(X));
% 	Xerr = Xd - X;
% 	Xstag = Xerr./(X0-X);
% 	input_cost = a*R*a;
% 	state_error_cost = Xerr'*Q*Xerr;
% 	stagnation_cost = 0;%(Xstag)'*Arc*(Xstag)
% 	J = input_cost + state_error_cost + stagnation_cost;
err_in = dot(Xd - Xin,Xd - Xin);
err_2  = dot(Xd - X, Xd - X);
err = err_in - err_2;
J = torque^2 + err + err_2;
end
