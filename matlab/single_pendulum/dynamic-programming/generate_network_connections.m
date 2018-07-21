%% Generate the network connections
load ../lib/cost_network_v1.0.mat
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
network = convert_network(network);
clearvars -except network p
steps = 30;
ids = [51 101];
connections = cell(steps,1);
for i = 1:steps
    tic
    if size(ids,1) > p.NumWorkers
        connections{i} = parnetwork_search3(network, ids);
    else
        connections{i} = network_search3(network, ids);
    end
    t = seconds(toc);
    t.Format = 'hh:mm:ss.SSS';
    t
    i
    save('cost_network.mat','i','network','connections', 't')
    ids = cell2mat(connections{i});
    ids = ids(:,1:2);
end

%% Functions
function [connections] = parnetwork_search3(network, ids)
    len = size(ids,1);
    connections = cell(len,1);
    parfor i = 1:len
        connections{i} = network(~any(ids(i,:) - network(:,[4,5]),2),:);
    end
end

function [connections] = network_search3(network, ids)
    len = size(ids,1);
    connections = cell(len,1);
    for i = 1:len
        connections{i} = network(~any(ids(i,:) - network(:,[4,5]),2),:);
    end
end

function new_network = convert_network(network)
    [n,m] = size(network);
    max_cons = 21;
    new_network = zeros(n*m*max_cons,2+1+4);
    for i = 1:n
        for j = 1:m
            len = length(network{i,j}.connections);
            for k = 1:max_cons
                if k > len
                    break;
                end
                new_network((i-1)*max_cons*m + (j-1)*max_cons + k,:) = ...
                    [ i j k network{i,j}.connections{k}];
            end
        end
    end
    new_network = new_network(any(new_network,2),:);
end