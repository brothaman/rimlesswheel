%% network details
% this script will gather information about the cost network
torque_range = [0 5];
velocity_range = [-2.76 0];
body_angle_range = [0 pi/2];
body_angle_rate_range = [-6 6];

steps = find(~cellfun('isempty',connections));
len = length(steps);
fills = zeros(size(steps));
net = {};
for i = steps'
    fills(i) = length(find(~cellfun('isempty',connections{i})));
    net = [net; connections{i}];
end
net = cell2mat(net);
disp('the total number of unique nodes visited is')
total_connections = sum(fills)

disp('the difference in unique connections found and unique connections store is')
number_of_unique_connections = size(unique(net,'rows'),1)
number_of_stored_connections = size(net,1)
size(unique(net,'rows'),1) - size(net,1)
plot (steps,fills)
xlabel('steps')
ylabel('nodes visited')

[n,m] = size(network);
for i = 1:n
    for j = 1:m
        number_of_connections(i,j) = length(network{i,j}.connections);
        if ~isempty(network{i,j}.optimal_value)
            cost_to_goal(i,j) = network{i,j}.optimal_value;
        else
            
        end
    end
end
fig1 = figure;
surf(number_of_connections);

fig2 = figure 
surf(cost_to_goal);