% clear
% connection_data = load('cost_network_v1.1.mat');
% data = load('../lib/cost_network_v1.1.mat');
% network = data.network;
% connections = connection_data.connections;
% clearvars -except network connections
% addpath ../lib/

len = length(connections);
iterations = 2;
% get a slice of the network parfor goes here
parfor i = 1:iterations
    for j =  1:size(network,1)
        nodes = network(j,:);
        for k = 1:len
            for l = 1:size(connections{k},1)
                if isempty(connections{k})
                    continue
                end
                for m = 1:size(connections{k}{l},1)
                    % if the ids match perform the calcualtion otherwise forget
                    % it
                    connection = connections{k}{l}(m,:);
                    if isempty(connection)
                        continue
                    end
                    if nodes{k}.ID == connection(1:2)
                        nodes(k) = evaluate_connection(network,network{j,k}, connection)
                    end
                end
            end
        end
        network(j,:) = nodes;
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