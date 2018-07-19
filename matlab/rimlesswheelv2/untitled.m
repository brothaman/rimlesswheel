% [connections, id_n_state, conns] = network_search(A,3);

N = maxNumCompThreads;
p = gcp('nocreate'); % If no pool, do not create new one.
if isempty(p)
    poolsize = 0;
    parpool(N)
else
    poolsize = p.NumWorkers;
    if poolsize < N
        delete(gcp('nocreate'));
        parpool(N)
    end
end


[connections, id_n_state, conns] = network_search(A,12);
save('connections.mat','connections','id_n_state','conns')
connection_mat = cell2mat(connections(:));
touched = false(n,m,p);

parfor i = 1:n
    for j = 1:m
        for k = 1:p
            touched(i,j,k) = sum(connection_mat(~any([i j k] - connection_mat(:,1:3),2) | ~any([i j k] - connection_mat(:,5:7),2)));
%             if connection_mat(~any([i j k] - connection_mat(:,1:3),2) | ~any([i j k] - connection_mat(:,5:7),2))
%                 touched(i,j,k) = true;
%             end
        end
    end
end
