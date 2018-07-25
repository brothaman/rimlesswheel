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
            number_of_connections((i-1)*p*m + (j-1)*p + k) = length(A{i,j,k}.connections);
            for l = 1:number_of_connections((i-1)*p*m + (j-1)*p + k)
                cost((i-1)*p*m*100 + (j-1)*p*100 + (k-1)*100 + l) = A{i,j,k}.connections{l}(5);
%                 if A{i,j,k}.connections{l}(5) > max_cost
%                     max_cost = A{i,j,k}.connections{l}(5);
%                 elseif A{i,j,k}.connections{l}(5) < min_cost
%                     min_cost = A{i,j,k}.connections{l}(5);
%                 end
            end
        end
    end
end
max_cost = max(cost)
min_cost = min(cost)
max_connections = max(number_of_connections)