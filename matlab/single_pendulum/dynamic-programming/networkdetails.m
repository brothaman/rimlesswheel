%% network details
% this script will gather information about the cost network
global NODES count
load ../lib/cost_network_v0.4i3.mat
m = 201;
n = 101;
p = 21;
% average number of connections per node
num_nodes = m*n;
nodeconnectionarr = zeros(n,m);
policy_is_set = zeros(n,m);
for i = 1:n
    for j = 1:m
        nodeconnectionarr(i,j) = length(NODES{i,j}.connections);
        policy_is_set(i,j) = ~isempty(NODES{i,j}.optimal_policy);
    end
end
average_connections_per_node = mean2(nodeconnectionarr);
percent_validated_nodes = sum(policy_is_set)/num_nodes;
fig = figure;
contour(policy_is_set);
xlabel('angle \theta mapped [0,2\pi] -> [0, 101]','Interpreter','latex')
ylabel('anglular velocity $\dot{\theta}$ mapped [-6,6] -> [0, 201]','Interpreter','latex')
title({'Contour plot of nodes that','have a connection to the goal'})