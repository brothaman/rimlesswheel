function [J] = cost(Xd, Xin, X, torque)
% maybe consider reducing the average cost to 1 currently it is set at 100
deltaX = (Xd-Xin).^2 - (Xd - X).^2;
Qabs = [
    100/pi 0
    0  100/6];
Qdelta = [
    10 0
    0  2
    ];
Absolute_positional_error = X*Qabs*X';
Change_in_positional_error = deltaX*Qdelta*abs(deltaX');
J = torque^2 + Change_in_positional_error + Absolute_positional_error;
end