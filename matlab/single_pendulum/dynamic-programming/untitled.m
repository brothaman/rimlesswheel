%% build connection network
clear
load ../lib/cost_network_v0.1.mat
N = 3;
connections = cell(1,N);
connections(1) = {network_search(NODES,51,101)};
[n,m] = size(network);
parallel_timer = duration(nan(N,3));
reshape_timer = duration(nan(N,3));
tic
for i = 1:N-1
    [connections{i+1}, parallel_timer(i), reshape_timer(i)]  = search_network2(NODES,connections{i});
%     save('cost_network.mat','i','NODES','connections', 'parallel_timer', 'reshape_timer')
end
t = seconds(toc);
t.Format = 'hh:mm:ss.SSS';
t
%% evaluate the connections parallelize this!!
