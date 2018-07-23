%% network details
% this script will gather information about the cost network
steps = find(~cellfun('isempty',connections));
len = length(steps);
fills = zeros(size(steps));
net = {};
for i = steps'
    fills(i) = length(find(~cellfun('isempty',connections{i})));
    net = [net; connections{i}];
end
net = cell2mat(net);
disp('the total number of unique connections is')
total_connections = sum(fills)

disp('the difference in unique connections found and unique connections store is')
number_of_unique_connections = size(unique(net,'rows'),1)
number_of_stored_connections = size(net,1)
size(unique(net,'rows'),1) - size(net,1)
xlabel('steps')
ylabel('new connections')
plot (steps,fills)