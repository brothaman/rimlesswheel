connection_data = load('cost_network_v1.0.mat');
data = load('../lib/cost_network_v1.0.mat');
network = data.network;
connections = connection_data.connections;
clearvars -except network connections
addpath ../lib/

len = length(connections);
iterations = 2;
% get a slice of the network
parfor i = 1:iterations
    for j =  1:size(network,2)
        nodes = network(:,j);
        for k = 1:len
            % if the ids match perform the calcualtion otherwise forget it
            if nodes{k}.ID == connections{k}(1:2)
                nodes(k) = evaluate_connection(network,nodes{k}, connections{k});
            end
        end
    end
end
%% functions
function node = evaluate_connection(network,node, connection)
    if isempty(network{connection(4), connection(5)}.optimal_value)
        return
    else
        % since the destination node has been evaluated we can now
        % determine whether the connection is desireable
        % if the policy and value do not exit
        % if  isempty(node.optimal_value) && isempty(node.optimal_policy)
        value = connections(7) + network{connection(4), connection(5)}.optimal_value;
        if  isempty(node.optimal_value)
            node.optimal_policy = connection(3);
            node.optimal_value = value;
        else
            % compare the node and update if a better policy exist
            % otherwise do nothing
            if node.optimal_value > value
                node.optimal_policy = connection(3);
                node.optimal_value = value;
            end
        end
    end
end