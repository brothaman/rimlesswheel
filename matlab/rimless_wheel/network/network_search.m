function [connections] = network_search(n_,N)
global network
connections = [];

for i = 1:N
    for l = 1:length(network{i}.connections)
        if network{i}.connections{l}(1) == n_
            if isempty(network{i}.optimal_policy)
                connections = [ connections; [i l]];
            else
                % check to see if the current connection is one of many
                % contained in the 
                if network{n_}.connections{...
                        network{n_}.optimal_policy}(1)==n
                    continue;
                end
                connections = [ connections; [i l]];
            end
        end
    end
end
end