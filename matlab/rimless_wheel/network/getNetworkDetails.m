function [num_of_connections] = getNetworkDetails(network,networkShape)
network = reshape(network,[prod(networkShape),1]);
for i = 1:length(network)
    num_of_connections(i) = length(network{i}.connections);
end
end