addpath ../lib/
load ../lib/weak_cost_network.mat
path = 'images/weak_pend/growth/';
for i = 1:125
	load(['../lib/weak_pend/weak_network_' int2str(i) '.mat'])
	show_cost_network(...
		['weak cost network iteration ' int2str(i)],path,all_angles,all_speeds,network)
    close all
end
