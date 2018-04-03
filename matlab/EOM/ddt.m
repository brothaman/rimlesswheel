function [DDT] = ddt(X, var)
% calculate the derivative of a function with respect to time when the
% function depends on time dependent variables using chain rule

DDT = 0;
for i = 1:length(var)
	DDT = DDT + diff(X,var(i,1))*var(i,2);
end
end
