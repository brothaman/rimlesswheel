%% get cost range
addpath ../single_pendulum/lib/
load parallel_network_test.mat
max_cost = 0;
min_cost = 0;
max_connections = 0;
[n,m,p] = size(network);
for i = 1:n
    for j = 1:m
        for k = 1:p
            number_of_connections((i-1)*p*m + (j-1)*p + k) = length(network{i,j,k}.connections);
            number_of_connections_n(i,j,k) = length(network{i,j,k}.connections);
            for l = 1:number_of_connections((i-1)*p*m + (j-1)*p + k)
                cost((i-1)*p*m*100 + (j-1)*p*100 + (k-1)*100 + l) = network{i,j,k}.connections{l}(5);
%                 if network{i,j,k}.connections{l}(5) > max_cost
%                     max_cost = network{i,j,k}.connections{l}(5);
%                 elseif network{i,j,k}.connections{l}(5) < min_cost
%                     min_cost = network{i,j,k}.connections{l}(5);
%                 end
            end
        end
    end
end
max_cost = max(cost)
min_cost = min(cost)
max_connections = max(number_of_connections)
myhist = hist(conns(:,9),201);

xlabel('all possible torques from -10 to 10 N*m')
ylabel('Sum of Occurences')
xlim([-10 10])