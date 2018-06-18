function [number_of_connections, nodes_with_policy_set] = get_network_details(filename, size)
    netowrk = load(filename);
    n = size(1);
    m = size(2);
    number_of_connections = zeros(n,m);
    nodes_with_policy_set = zeros(n,m);
    for i = 1:n
        for j = 1:m
            number_of_connections(i,j) = length(network.NODES{i,j}.connections);
            nodes_with_policy_set(i,j) = ~isempty(network.NODES{i,j}.optimal_policy);
        end
    end
end