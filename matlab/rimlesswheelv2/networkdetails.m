%% get cost range
load parallel_network_test.mat
max_cost = 0;
min_cost = 0;
[n,m,p] = size(A);
for i = 1:n
    for j = 1:m
        for k = 1:p
            for l = 1:length(A{i,j,k}.connections)
                if A{i,j,k}.connections{l}(5) > max_cost
                    max_cost = A{i,j,k}.connections{l}(5);
                elseif A{i,j,k}.connections{l}(5) < min_cost
                    min_cost = A{i,j,k}.connections{l}(5);
                end
            end
        end
    end
end