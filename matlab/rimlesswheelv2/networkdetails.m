%% get cost range
% load parallel_network_test.mat
addpath ../single_pendulum/lib/
max_cost = 0;
min_cost = 0;
max_connections = 0;
[n,m,p] = size(A);
for i = 1:n
    for j = 1:m
        for k = 1:p
            number_of_connections = length(A{i,j,k}.connections);
            max_connections(max_connections < number_of_connections) = number_of_connections;
            for l = 1:number_of_connections
                if A{i,j,k}.connections{l}(5) > max_cost
                    max_cost = A{i,j,k}.connections{l}(5);
                elseif A{i,j,k}.connections{l}(5) < min_cost
                    min_cost = A{i,j,k}.connections{l}(5);
                end
            end
        end
    end
end
max_cost
min_cost
max_connections