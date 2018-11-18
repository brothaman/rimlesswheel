function [alpha] = getControlSignal(state, network)
	%UNTITLED3 Summary of this function goes here
	%   Detailed explanation goes here
	[~,indx] = min(abs(state - network(:,1)));
	alpha = network(indx,2);
end
% 
% function indx = getIndex(state, network)
% 	vec = min(abs(state - network(1,:)));
% 	

