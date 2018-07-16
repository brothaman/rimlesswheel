function [] = network_search(network)
[n,m,p] = size(network);
id_n_state = state_id_correlation(network);
a = network{1,2,3}.state
loc = get_id_from_state(network, id_n_state, a)
network{1,2,3}.ID
goal = -1.84;
IDs = get_goal_nodes(id_n_state, goal, [n,m,p])
for i = 1:length(id_n_state)
    search_for_connected_nodes(network,i)
end
id = extract_location(183, m, p);
search_for_connected_nodes(network,id)
end

function nmp3returnmatrix = state_id_correlation(network)
[n,m,p] = size(network);
for i = 1:n
    for j = 1:m
        for k = 1:p
            nmp3returnmatrix((i-1)*m*p + (j-1)*p + k,:) = network{i,j,k}.state;
        end
    end
end
nmp3returnmatrix = reshape(nmp3returnmatrix,[i*j*k,3]);
end

function id = get_id_from_state(network, B, state)
if (size(state) ~= [1,3])
    % throw an error
end
[n,m,p] = size(network);
[val,nn] = min(abs(sum(state - B,2)));

id = extract_location(nn, m, p);
end

function return_array = get_goal_nodes(B, goal, dims)
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
for i = 1:length(single_number_states)
    return_array(i,:) = extract_location(single_number_states(i), m, p);
end
end

function result = extract_location(val, m, p)
i = floor(val/(m*p));
j = floor((val-i*p*m)/(p));
k = (val-i*p*m - j*p);

result = [i+1,j+1,k];
end

function [connections] = search_for_connected_nodes(network,ID)
% connections should contain [ connected_node_id number_correlating_to_connection]
[n,m,p] = size(network);
connections = [];
for i = 1:n
    for j = 1:m
        for k = 1:p
            if ID == [i,j,k]
                continue;
            end
            for l = 1:length(network{i,j,k}.connections)
                if network{i,j,k}.connections{l}(1:3) == ID
                    connections(end+1,:) = [ i j k l];
                end
            end
        end
    end
end
end
