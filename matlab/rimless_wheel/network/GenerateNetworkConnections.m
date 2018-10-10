%% Generate Network Connections

function GenerateNetworkConnections(input_filename, output_filename)
% 	to avoid conflicts in matlab i have to pull data from an input file
% 	into a variable and store those variables in there original syntactic
% 	containers
	data = load(input_filename);
	network = data.network;
	parameters = data.parameters;
	
	careful = false;
	goal_speed = parameters.desired_speed;
	steps = 20;
	skinny_network = network_state_n_id(network);
	connection_network = convert_network(network);
	ids_to_search = get_ID_from_state(goal_speed, skinny_network);
	searched_ids = [];
	maxconns = 0;

	for i = 1:steps
		% perform a network search to find all the nodes with connections to
		% the goal node.
		[connections{i},maxcon] = NetworkSearch( connection_network, ids_to_search, searched_ids);
		if maxcon > maxconns
			maxconns = maxcon;
		end
		if careful
			% store the IDs of the nodes with connections to the node in interest
			save(output_filename, 'i','connection_network','connections', 'ids_to_search', 'searched_ids','maxconns');
		end
		ids_to_search = cell2mat(connections{i});
		searched_ids = [searched_ids; unique(ids_to_search,'rows')];
		ids_to_search = ids_to_search(:,[1]);
		ids_to_search = unique(ids_to_search,'rows');
		if isempty(ids_to_search)
			break;
		end
		% also store the 
	end
	save(output_filename, 'i','connection_network','connections', 'ids_to_search', 'searched_ids','maxconns','network');
end

%% Functions
function [connections, maxcons] = NetworkSearch(network, ids_to_search, searched_ids)
	len = size(ids_to_search,1);
	connections = cell(len,1);
	maxcons = 0;
	for i = 1:len
		connections{i} = network(~any(ids_to_search(i,[1]) - network(:,[3]),2),:);
		
		for j = 1:size( searched_ids)
			if isempty(connections{i})
				break;
			end
			connections(i) = {connections{i}(any(searched_ids(j,[1 3]) - connections{i}(:,[1 3]),2),:)};
			if isempty(connections{i})
				break;
			end
		end
	end
	for i = 1:length(connections)
        if ~isempty(connections{i})
            if size(connections{i},1) > maxcons
                maxcons = size(connections{i},1);
            end
        end
    end
end

function new_network = convert_network(network)
    n = size(network,2);
    max_cons = 100;
    new_network = zeros(n*max_cons,1+1+1);
    for i = 1:n
		len = length(network{i}.connections);
		for k = 1:max_cons
			if k > len
				break;
			end
			new_network((i-1)*max_cons + k,:) = ...
				[ i k network{i}.connections{k}(1)];
		end
    end
    new_network = new_network(any(new_network,2),:);
end

function new_network = network_state_n_id(network)
    n = size(network,2);
    new_network = zeros(n,2);
    for i = 1:n
		new_network(i,:) = [i,network{i}.state];
    end
end

function ID = get_ID_from_state(speed, skinny_network)
	[~,indx] = min(abs(speed - skinny_network(:,2)));
	ID = skinny_network(indx,1);
end
			