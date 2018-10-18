function [connectivity, reachable_states, unreachable_states, conns] = testNetworkConnectivity(filename)
% TESTNETWORKCONNECTIVITY  calculates the number of nodes connected to each node.
% [CONNECTIVITY, REACHABLE_STATES, UNREACHABLE_STATES] = TESTNETWORKCONNECTIVITY(FILENAME) accepts a file path and 
% returns the connectivity as well as the reachable and unreachable states.
	data = load(filename);
	conns = zeros(size(data.network));
	for i = 1:length(data.network)
		conns(i) = NetworkSearch( data.network, i);
	end
	connectivity = mean(conns);
	reachable_states = data.network(any(conns ~=0,1));
	unreachable_states = data.network(~any(conns ~=0,1));
end

function [connections] = NetworkSearch(network, id)
	connections = 0;
	for i = 1:length(network)
		for j = 1:length(network{i}.connections)
			if(network{i}.connections{j}(1) == id)
				connections = connections + 1;
			end
		end
	end
end