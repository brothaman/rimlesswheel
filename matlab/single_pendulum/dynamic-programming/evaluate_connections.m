function evaluate_connections(parameters,input_filename,output_filename)
	% connection_data = load('cost_network_v1.1.mat');
	% data = load('../lib/cost_network_v2.0.mat');
	% network = data.network;
	% connections = connection_data.connections;
	% clearvars -except network connections
	% addpath ../lib/
	% 
	% % set the goal node 
	data = load(parameters.filename,'connections');
	connections = data.connections;
	data = load(input_filename,'network');
	network = data.network;
	network{parameters.goal(1),parameters.goal(2)}.optimal_value = 0;
	network{parameters.goal(1),parameters.goal(2)}.optimal_policy = nan;
	%[filename,i,network,connection_network,connections, t, ids,previous_ids,maxconns] = weak_actuation_init();
	% for each level of connection in the connection network cycle through all
	% the nodes and evaluate the connection. if a connection exist and the
	% compare the value and store the policy and value of the lower value
% 	len = length(connections);
% 	iterations = 2;
% 	net = cell(size(network));
% 	[N,M] = size(network);
	n = sum(any(~cellfun('isempty',connections),2));
	% loop through each stage and evaluate the connections
	for i = 1:n
	% 	check to see if the stage has any connection
		if isempty(connections{i})
			break;
		end
		tic
	% 	determine the actual number of connections in the stage
		m = find(~cellfun('isempty',connections{i}))';
		nodes = cell(length(m),parameters.maxconns);

	% 	for each connection in the stage
		for l = 1:length(m)
			j = m(l);
			len = size(connections{i}{j},1);
			node = cell(1,parameters.maxconns);
			for k = 1:len

				node(k)  = evaluate_connection(...
					network,...
					network{connections{i}{j}(k,1),connections{i}{j}(k,2)},...
					[network{connections{i}{j}(k,1),connections{i}{j}(k,2)}.connections{connections{i}{j}(k,3)} connections{i}{j}(k,3)]);
			end
			nodes(l,:) = node;
		end
		nodes = reshape(nodes,[numel(nodes),1]);
		for j = 1:length(nodes)
			if ~isempty(nodes{j})
				network{nodes{j}(1),nodes{j}(2)}.optimal_policy = nodes{j}(3);
				network{nodes{j}(1),nodes{j}(2)}.optimal_value = nodes{j}(4);
			end
		end
		teval(i) = seconds(toc);
	end
	teval.Format = 'hh:mm:ss';
	save(output_filename,'network','-append');
end

%% functions
function conn = evaluate_connection(network,node, connection)
    conn = {[]};
    if isempty(network{connection(1), connection(2)}.optimal_value)
        return
    else
        % since the destination node has been evaluated we can now
        % determine whether the connection is desireable
        % if the policy and value do not exit
        % if  isempty(node.optimal_value) && isempty(node.optimal_policy)
        value = connection(4) + network{connection(1), connection(2)}.optimal_value;
        if  isempty(node.optimal_value) || isnan(node.optimal_value)
%             optimal_policy = connection(5);
%             optimal_value = value;
%             conn = [node.ID optimal_policy optimal_value];
            conn = {[node.ID connection(5) value]};
        else
            % compare the node and update if a better policy exist
            % otherwise do nothing
            if node.optimal_value > value
%                 optimal_policy = connection(5);
%                 optimal_value = value;
%                 conn = [node.ID optimal_policy optimal_value];
                conn = {[node.ID connection(5) value]};
            end
        end
    end
end

function [filename,i,network,connection_network,connections, t, ids,previous_ids, maxconns] = standard_init()
    maxconns = 50;
    filename = '../lib/cost_network.mat';
    load(filename);
    % set the goal node 
    network{51,101}.optimal_value = 0;
    network{51,101}.optimal_policy = 9;
end

function [filename,i,network,connection_network,connections, t, ids,previous_ids, maxconns] = underactuated_init()
    maxconns = 50;
    filename = '../lib/underactuated_cost_network.mat';
    load(filename);
    % set the goal node 
    network{51,101}.optimal_value = 0;
    network{51,101}.optimal_policy = 5;
end

function [filename,i,network,connection_network,connections, t, ids,previous_ids, maxconns] = very_weak_actuation_init()
    maxconns = 50;
    filename = '../lib/very_weak_cost_network.mat';    
    load(filename);
    % set the goal node 
    network{51,101}.optimal_value = 0;
    network{51,101}.optimal_policy = 1;
end

function [filename,i,network,connection_network,connections, t, ids,previous_ids, maxconns] = weak_actuation_init()
    maxconns = 50;
    filename = '../lib/weak_cost_network.mat';    
    load(filename);
    % set the goal node 
    network{51,101}.optimal_value = 0;
    network{51,101}.optimal_policy = 1;
end
