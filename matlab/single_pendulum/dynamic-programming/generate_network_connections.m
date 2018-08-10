%% Generate the network connections
addpath ../lib/
filename = standard_init();
load(filename)
N = maxNumCompThreads;
p = gcp('nocreate'); % If no pool, do not create new one.
if isempty(p)
    poolsize = 0;
    m = parcluster;
    m.NumWorkers = N;
    p = parpool(N);
else 
    poolsize = p.NumWorkers;
    if poolsize < N
        delete(gcp('nocreate'));
        m = parcluster;
        m.NumWorkers = N;
        parpool(N)
    end
end
connection_network = convert_network(network);
clearvars -except connection_network network p filename
steps = 1000;
ids = connection_network(~any([51 101] - connection_network(:,[1 2]),2),[1 2 4 5]);
res = size(ids,1);
connections = cell(steps,1);
maxconns = 0;
for i = 1:steps
    tic
    if i > 1
        [connections{i},maxcon] = parnetwork_search3(connection_network, ids, previous_ids);
        if maxcon > maxconns
            maxconns = maxcon;
        end
        ids = cell2mat(connections{i});
        previous_ids = [previous_ids; ids(:,[1 2 4 5])];
        previous_ids = unique(previous_ids,'rows');
    else
        connections{i} = network_search3(connection_network, ids(1,1:2));
        previous_ids = ids;
    end
    
    t(i) = seconds(toc);
    t(i)
    i
    save(filename,'i','connection_network','connections', 't', 'ids','previous_ids','-append','maxconns')
gener    ids = cell2mat(connections{i});
    ids = ids(:,[1 2]);
    ids = unique(ids,'rows');
    if isempty(ids)
        break;
    end
end

%% Functions
function [connections,maxconns] = parnetwork_search3(network, ids, previous_ids)
    len = size(ids,1);
    connections = cell(len,1);
    maxconns = 0;
    parfor i = 1:len
        % if previous id's [4,5] is equal to current id's [1,2] and current
        % id's [4,5] is equal to previous id's [1,2] then eliminate current
        % id's connection that correlate with [4,5]. delete current id's
        % [4,5]
        connections{i} = network(~any(ids(i,[1,2]) - network(:,[4,5]),2),:);
        % this will eliminate any connections back to the previous
        for j = 1:size(previous_ids,1)
            connections(i) = {connections{i}(any(previous_ids(j,:) - connections{i}(:,[1 2 4 5]),2),:)};
        end
    end
    for i = 1:length(connections)
        if ~isempty(connections{i})
            if size(connections{i},1) > maxconns
                maxconns = size(connections{i},1);
            end
        end
    end
end

function [connections] = network_search3(network, ids)
    len = size(ids,1);
    connections = cell(len,1);
    for i = 1:len
        connections{i} = network(~any(ids(i,[1,2]) - network(:,[4,5]),2),:);
    end
end

function new_network = convert_network(network)
    [n,m] = size(network);
    max_cons = 21;
    new_network = zeros(n*m*max_cons,2+1+2);
    for i = 1:n
        for j = 1:m
            len = length(network{i,j}.connections);
            for k = 1:max_cons
                if k > len
                    break;
                end
                new_network((i-1)*max_cons*m + (j-1)*max_cons + k,:) = ...
                    [ i j k network{i,j}.connections{k}(1:2)];
            end
        end
    end
    new_network = new_network(any(new_network,2),:);
end

function [filename] = underactuated_init()
    filename = '../lib/underactuated_cost_network.mat';
end

function [filename] = standard_init()
    filename = '../lib/cost_network.mat';
end

function [filename] = very_weak_actuation_init()
    filename = '../lib/very_weak_cost_network.mat';
end

function [filename] = weak_actuation_init()
    filename = '../lib/weak_cost_network.mat';
end
