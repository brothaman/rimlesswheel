clear
connection_data = load('cost_network_v1.1.mat');
data = load('../lib/cost_network_v1.1.mat');
network = data.network;
connections = connection_data.connections;
clearvars -except network connections
addpath ../lib/

% set the goal node 
network{51,101}.optimal_value = 0;
network{51,101}.optimal_policy = 9;
% for each level of connection in the connection network cycle through all
% the nodes and evaluate the connection. if a connection exist and the
% compare the value and store the policy and value of the lower value
len = length(connections);
iterations = 2;
net = cell(size(network));
[N,M] = size(network);
n = size(connections,1);
for i = 1:n
    m = size(connections{i},1);
    for j = 1:m
        [l,p] = size(network);
        for k = 1:size(connections{i}{j},1)
            connection = connections{i}{j}(k,:);
            
            for l = 1:N
                for p = 1:M
                    if connection(1:2) == [l p]
                        network{l,p} = evaluate_connection(network,network{l,p}, connection);
                    end
                end
            end
        end
        j
    end
    i
end

% get a slice of the network parfor goes here
% parfor i = 1:iterations
%     for j =  1:size(network,1)
%         nodes = network(j,:);
%         for l = 1:len
%             for p = 1:size(connections{l},1)
%                 if isempty(connections{l})
%                     continue
%                 end
%                 for m = 1:size(connections{l}{p},1)
%                     % if the ids match perform the calcualtion otherwise forget
%                     % it
%                     connection = connections{l}{p}(m,:);
%                     if isempty(connection)
%                         continue
%                     end
%                     if nodes{l}.ID == connection(1:2)
%                         nodes{l} = evaluate_connection(network,network{j,l}, connection)
%                     end
%                 end
%             end
%         end
%     end
% 	net(j,:) = nodes;
% 
% end
%% functions
function node = evaluate_connection(network,node, connection)
    if isempty(network{connection(4), connection(5)}.optimal_value)
        return
    else
        % since the destination node has been evaluated we can now
        % determine whether the connection is desireable
        % if the policy and value do not exit
        % if  isempty(node.optimal_value) && isempty(node.optimal_policy)
        value = connection(7) + network{connection(4), connection(5)}.optimal_value;
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