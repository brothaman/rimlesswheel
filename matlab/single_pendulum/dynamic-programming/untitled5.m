%% build connection network
clear
data = load('cost_network.mat');
NODES = data.NODES;
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
% i need to evaluate each connection. if there is not a connections set
% then 
for i = 1:N
    conns = connections{i};
    len = length(conns);
    nodes = cell(len,1);
    parfor j = 1:len
        n = conns(j,1);
        m = conns(j,2);
        % evaluate connection
        node = evaluateConnection(NODES, n, m, conns(j,3));
        nodes{j} = { [n,m] node};
    end
    
    for j = 1:len
        NODES{nodes{j}{1}(1),nodes{j}{1}(2)} = nodes{j}{2};
    end
end