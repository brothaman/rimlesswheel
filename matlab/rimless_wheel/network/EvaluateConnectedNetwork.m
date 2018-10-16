function EvaluateConnectedNetwork(input_filename, output_filename)
% 	to avoid conflicts in matlab i have to pull data from an input file
% 	into a variable and store those variables in there original syntactic
% 	containers
	data = load(input_filename);
	connections = data.connections;
	network = data.network;
	maxconns = data.maxconns;
	connection_network = data.connection_network;
	ids_to_search = data.ids_to_search;
	searched_ids = data.searched_ids;
	parameters = data.parameters;
	
	
	len = length(connections);
	iterations = 2;
	net = cell(size(network));
	N = size(network,2);
	n = sum(any(~cellfun('isempty',connections),1));
	% loop through each stage and evaluate the connections
	for i = 1:n
	% 	check to see if the stage has any connection
		if isempty(connections{i})
			break;
		end
		tic
	% 	determine the actual number of connections in the stage
		m = find(~cellfun('isempty',connections{i}))';
		nodes = cell(length(m),maxconns);

	% 	for each connection in the stage
		for l = 1:length(m)
			j = m(l);
			len = size(connections{i}{j},1);
			node = cell(1,maxconns);
			for k = 1:len

				node(k)  = evaluate_connection(...
					network,...
					network{connections{i}{j}(k,1)},...
					[network{connections{i}{j}(k,1)}.connections{connections{i}{j}(k,2)} connections{i}{j}(k,2)]);
			end
			nodes(l,:) = node;
		end
		nodes = reshape(nodes,[numel(nodes),1]);
		for j = 1:length(nodes)
			if ~isempty(nodes{j})
				network{nodes{j}(1)}.optimal_policy = nodes{j}(2);
				network{nodes{j}(1)}.optimal_value = nodes{j}(3);
			end
		end
		teval(i) = seconds(toc);
	end
	teval.Format = 'hh:mm:ss';
	save(output_filename,'network','searched_ids','ids_to_search','connections','teval','maxconns','connection_network','parameters');
end
%% functions
function conn = evaluate_connection(network,node, connection)
    conn = {[]};
    if isempty(network{connection(1)}.optimal_value)
        return
    else
        % since the destination node has been evaluated we can now
        % determine whether the connection is desireable
        % if the policy and value do not exit
        % if  isempty(node.optimal_value) && isempty(node.optimal_policy)
        value = connection(3) + network{connection(1)}.optimal_value;
        if  isempty(node.optimal_value) || isnan(node.optimal_value)
%             optimal_policy = connection(5);
%             optimal_value = value;
%             conn = [node.ID optimal_policy optimal_value];
            conn = {[node.ID connection(4) value]};
        else
            % compare the node and update if a better policy exist
            % otherwise do nothing
            if node.optimal_value > value
%                 optimal_policy = connection(5);
%                 optimal_value = value;
%                 conn = [node.ID optimal_policy optimal_value];
                conn = {[node.ID connection(4) value]};
            end
        end
    end
end
