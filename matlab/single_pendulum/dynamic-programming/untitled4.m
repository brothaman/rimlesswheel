%% build connection network
clear
load cost_network.mat
N = 30;
connections = cell(1,N);
connections(1) = {network_search(NODES,51,101)};
[n,m] = size(network);
for i = i :N-1
    for j = j:size(connections{i},1)
        connections{i+1} = [
            connections{i+1}
            network_search(NODES,connections{i}(j,1),connections{i}(j,2))
            ];
    end
    save('cost_network.mat','i','NODES','connections')
    j = 1;
end

%% evaluate the connections parallelize this!!
