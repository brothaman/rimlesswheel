%% Generate the network connections
clear
filename = 'parallel_network_test.mat';
load(filename);
network = A;
clear A
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

STEPS = 3;
[n,m,p] = size(network);
id_n_state = state_id_correlation(network);
conns = get_state_connections(network);
goal = -2.76;
IDs = get_goal_nodes(id_n_state, goal, [n,m,p], network);
connections = cell(STEPS,1);
for i = 1:STEPS
    tic
    if i>1
        connections{i} = parnetwork_search2(conns, IDs, previous_ids);
        previous_ids = [previous_ids; IDs(:,[1 2 3 5 6 7])];
        previous_ids = unique(previous_ids,'rows');
    else
        connections{i} = network_search2(conns, IDs);
        previous_ids = IDs([1 2 3 5 6 7]);
    end
    t(i) = seconds(toc);
    IDs = unique(cell2mat(connections{i}), 'rows');
end
save(filename,'network','connections','t','IDs','previous_ids','conns');
%% Functions
function connections = parnetwork_search2(network, ids, previous_ids)
    ids = unique(ids(:,1:3),'rows');
    len = size(ids,1);
    connections = cell(len,1);
    parfor i = 1:len
        connections{i} = network(~any(ids(i,[1 2 3]) - network(:,[5 6 7]),2),:);
        % this will eliminate any connections back to the previous
        for j = 1:size(previous_ids,1)
            connections(i) = {connections{i}(any(previous_ids(j,:) - connections{i}(:,[1 2 3 5 6 7]),2),:)};
        end
    end
end

function connections = network_search2(network, ids)
    ids = unique(ids(:,1:3),'rows');
    len = size(ids,1);
    connections = cell(len,1);
    for i = 1:len
        connections{i} = network(~any(ids(i,[1 2 3]) - network(:,[5 6 7]),2),:);
    end
end

%% convert the network to a N x 3 matrix of states to correlate state and ID
function nmp3returnmatrix = state_id_correlation(network)
[n,m,p] = size(network);
nmp3returnmatrix = zeros(n*m*p,3);
for i = 1:n
    for j = 1:m
        for k = 1:p
            nmp3returnmatrix((i-1)*m*p + (j-1)*p + k,:) = network{i,j,k}.state(:);
        end
    end
end
nmp3returnmatrix = reshape(nmp3returnmatrix,[i*j*k,3]);
end

%% convert the network to a N x 3 matrix of states to correlate state and ID
function conns = get_state_connections(network)
[n,m,p] = size(network);
max_cons = 21;
max_con = 0;
conns = zeros(n*m*p*max_cons,9);
for i = 1:n
    for j = 1:m
        for k = 1:p
            len = length(network{i,j,k}.connections);
            if len > max_con
                max_con  = len;
            end
            for l = 1:max_cons
                if l <= len
                    conns((i-1)*m*p*max_cons + (j-1)*p*max_cons + (k-1)*max_cons + l,:) = [i j k l network{i,j,k}.connections{l}];
                end
            end
        end
    end
end
conns = conns(any(conns,2),:);
end

%% extract state id from a location
function id = get_id_from_state(B, state, dims)
if (size(state) ~= [1,3])
    % throw an error
end
[~,nn] = min(abs(sum(state - B,2)));

id = extract_location(nn, dims(2), dims(3));
end

function return_array = get_goal_nodes(B, goal, dims, network)
    % the arguments accepted are the parsed network and the goal
    if length(dims) ~= 3
        % throw error
        return
    end
    n = dims(1);
    m = dims(2);
    p = dims(3);

    % also set the cost of the desired node
    single_number_states = find(min(round(abs(sum([goal 0] - B(:,[1,3]),2)),2)) == round(abs(sum([goal 0] - B(:,[1,3]),2)),2));
    return_array = [];
    for i = 1:length(single_number_states)
        id = extract_location(single_number_states(i), m, p);
        connections = network{id(1),id(2),id(3)}.connections;
        for j = 1:length(connections)
            return_array(end+1,:) = [id j connections{j}]; 
        end
    end
end
%% this method returns the <i,j,k> ID that correlates to the given value
function result = extract_location(val, m, p)
    i = floor(val/(m*p));
    j = floor((val-i*p*m)/(p));
    k = (val-i*p*m - j*p);

    result = [i+1,j+1,k];
end

%% search the network for nodes connected to the given ID
function [conns] = search_for_connected_nodes(network,ID)
% connections should contain [ connected_node_id number_correlating_to_connection]
max_cons = 20;
[n,m,p] = size(network);
connections = zeros(n,m,p,max_cons,4);
for i = 1:n
    for j = 1:m
        for k = 1:p
            if ID == [i,j,k]
                continue;
            end
            for l = 1:length(network{i,j,k}.connections)
                if network{i,j,k}.connections{l}(1:3) == ID
                    connections(i,j,k,l,:) = [ i j k l];
                end
            end
        end
    end
end

conns = zeros(n*m*p*max_cons,4);
for i = 1:n
    for j = 1:m
        for k = 1:p
            for l = 1:max_cons
                conns((i-1)*m*p*max_cons + (j-1)*max_cons*p + (k-1)*max_cons + l, :) = connections(i,j,k,l,:);
            end
        end
    end
end
conns = conns(any(conns,2),:);
end
