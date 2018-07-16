function [] = network_search(network)
[n,m,p] = size(network);
B = state_id_correlation(network);
a = network{1,2,3}.state
loc = get_id_from_state(network, B, a)
network{1,2,3}.ID
desired_speed = -1.84;

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
i = floor(nn/(m*p));
j = floor((nn-i*p*m)/(p));
k = (nn-i*p*m - j*p);

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

end

function result = extract_location(val, m, p)
i = floor(val/(m*p));
j = floor((val-i*p*m)/(p));
k = (val-i*p*m - j*p);

result = [i+1,j+1,k];
end
function [connections] = search_for_connected_nodes(network)
% connections should contain [ connected_node_id number_correlating_to_connection]
end
