clear
% connection_data = load('cost_network_v1.1.mat');
% data = load('../lib/cost_network_v2.0.mat');
% network = data.network;
% connections = connection_data.connections;
% clearvars -except network connections
% addpath ../lib/
% 
% % set the goal node 
% network{51,101}.optimal_value = 0;
% network{51,101}.optimal_policy = 9;

[filename,i,network,connection_network,connections, t, ids,previous_ids] = very_weak_actuation_init();
% for each level of connection in the connection network cycle through all
% the nodes and evaluate the connection. if a connection exist and the
% compare the value and store the policy and value of the lower value
len = length(connections);
iterations = 2;
net = cell(size(network));
[N,M] = size(network);
n = size(connections,1);
for i = 1:n
    if isempty(connections{i})
        break;
    end
    m = find(~cellfun('isempty',connections{i}))';
    tic
    for j = m
        [l,p] = size(network);
        for k = 1:size(connections{i}{j},1)
            connection = connections{i}{j}(k,:);
            
            for l = 1:N
                for p = 1:M
                    if connection(1:2) == [l p]
                        network{l,p} = evaluate_connection(network,network{l,p}, [network{l,p}.connections{connection(3)} connection(3)]);
                    end
                end
            end
        end
    end
    teval(i) = seconds(toc);
    teval(i)
    i
end
teval.Format = 'hh:mm:ss'
save(filename,'network','ids','previous_ids','-append');
%% functions
function node = evaluate_connection(network,node, connection)
    if isempty(network{connection(1), connection(2)}.optimal_value)
        return
    else
        % since the destination node has been evaluated we can now
        % determine whether the connection is desireable
        % if the policy and value do not exit
        % if  isempty(node.optimal_value) && isempty(node.optimal_policy)
        value = connection(4) + network{connection(1), connection(2)}.optimal_value;
        if  isempty(node.optimal_value)
            node.optimal_policy = connection(5);
            node.optimal_value = value;
        else
            % compare the node and update if a better policy exist
            % otherwise do nothing
            if node.optimal_value > value
                node.optimal_policy = connection(5);
                node.optimal_value = value;
            end
        end
    end
end

function [filename,i,network,connection_network,connections, t, ids,previous_ids] = underactuated_init()
    filename = '../lib/underactuated_cost_network.mat';
    load(filename);
    % set the goal node 
    network{51,101}.optimal_value = 0;
    network{51,101}.optimal_policy = 5;
end

function [filename,i,network,connection_network,connections, t, ids,previous_ids] = very_weak_actuation_init()
    filename = '../lib/very_weak_cost_network.mat';    
    load(filename);
    % set the goal node 
    network{51,101}.optimal_value = 0;
    network{51,101}.optimal_policy = 1;
end
