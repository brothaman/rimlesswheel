function [DDT] = ddt(X, var)

DDT = 0;
for i = 1:length(var)
	DDT = DDT + diff(X,var(i,1))*var(i,2);
end
end
