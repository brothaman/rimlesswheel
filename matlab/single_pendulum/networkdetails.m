%% network details
% this script will gather information about the cost network
global NODES
m = 201;
n = 101;
p = 21;
% average number of connections per node
num_nodes = m*n;
nodeconnectionarr = zeros(m*n,1);
policy_is_set = zeros(m*n,1);
for i = 1:n
    for j = 1:m
        index = (i-1)*m + j;
        nodeconnectionarr(index) = length(NODES{i,j}.connections);
        policy_is_set(index) = ~isempty(NODES{i,j}.optimal_policy);
    end
end
average_connections_per_node = mean(nodeconnectionarr);
percent_validated_nodes = sum(policy_is_set)/num_nodes;
fig = figure;
x = 1:length(policy_is_set);
y = policy_is_set.*x;
plot(x,y)
