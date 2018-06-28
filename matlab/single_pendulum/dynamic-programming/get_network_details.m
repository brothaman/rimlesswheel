function [number_of_connections, nodes_with_policy_set, cost_surface] = get_network_details(filename, size)
    network = load(filename);
    n = size(1);
    m = size(2);
    number_of_connections = zeros(n,m);
    nodes_with_policy_set = zeros(n,m);
    cost_surface = zeros(n,m);
    for i = 1:n
        for j = 1:m
            number_of_connections(i,j) = length(network.NODES{i,j}.connections);
            nodes_with_policy_set(i,j) = ~isempty(network.NODES{i,j}.optimal_policy);
            if ~isempty(network.NODES{i,j}.optimal_value)
                cost_surface(i,j) = network.NODES{i,j}.optimal_value;
        end
    end
end