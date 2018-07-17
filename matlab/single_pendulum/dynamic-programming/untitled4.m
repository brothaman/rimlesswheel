%% build connection network
N = 30;
connections = cell(1,N);
connections(1) = {network_search(NODES,51,101)};
[n,m] = size(network);
for i = 1:N-1
    for j = 1:size(connections{i},1)
        connections{i+1} = [
            connections{i+1}
            network_search(NODES,connections{i}(j,1),connections{i}(j,2))
            ];
    end
end

%% evaluate the connections parallelize this!!
