connection_data = load('cost_network_v1.0.mat');
data = load('../lib/cost_network_v1.0.mat');
network = data.network;
connections = connection_data.connections;
clearvars -except network connections
addpath ../lib/

len = length(connections);
% get a slice of the network
parfor i =  1:size(network,2)
    nodes = network(:,i);
    for j = 1:len
        % if the ids match perform the calcualtion otherwise forget it
        if nodes{j}.ID == connections{j}(1:2)
            nodes(j) = evaluate_connection(nodes(j), connection);
        end
    end
end
%% functions
function node = evaluate_connection(node, connection)
end