function [num_of_connections, policy_set, cost_prof] = getNetworkDetails(network,networkShape)
network = reshape(network,[prod(networkShape),1]);
policy_set = zeros(networkShape);
cost_prof = zeros(networkShape);
for i = 1:length(network)
    num_of_connections(i) = length(network{i}.connections);
    policy_set(i) = ~isempty(network{i}.optimal_value);
    if policy_set(i)
        cost_prof(i) = network{i}.optimal_value;
    end
end
end