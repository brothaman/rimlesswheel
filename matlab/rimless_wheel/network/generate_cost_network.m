%% generate the cost network
% begin by getting an array of desired speeds
restoredefaultpath
addpath('../../single_pendulum/lib/','../model/')
xds = -2.76:0.1:0;
for i = 1:length(xds)
    generate_new_state_n_cost(xds(i));
end
exit