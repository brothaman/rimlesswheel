%% network details
% this script will gather information about the cost network
global NODES
load lib/cost_network_v0.2.mat
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
surf(policy_is_set);
colormap  hsv