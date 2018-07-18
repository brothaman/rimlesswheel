function node = evaluateConnection(NODES,n,m,connection)
% if isnumeric(connection) && length(connection) == 1
%     transition_cost = NODES{m,n}.connections{connection}(4);
%     mm = NODES{m,n}.connections{connection}(1);
%     nn = NODES{m,n}.connections{connection}(2);
%     pol = connection;
% else
%     transition_cost = connection(4);
%     mm = connection(1);
%     nn = connection(2);
%     for pol = 1:length(NODES{m,n}.connections)
%         if NODES{m,n}.connections{pol}(1:2) == [mm,nn]
%             break;
%         end
%     end
% end
% ----------------------------------------------------------------------- %
transition_cost = NODES{n,m}.connections{connection}(4);
mm = NODES{n,m}.connections{connection}(1);
nn = NODES{n,m}.connections{connection}(2);
pol = connection;

state_cost = NODES{mm,nn}.optimal_value;

% if there is no optimal value already inplace fill the optimal value
if isempty(NODES{n,m}.optimal_value)
    NODES{n,m}.optimal_value = transition_cost + state_cost;
    NODES{n,m}.optimal_policy  = pol;
% otherwise check to see if there is a value in 
elseif NODES{n,m}.optimal_value > transition_cost + state_cost
    NODES{n,m}.optimal_value = transition_cost + state_cost;
    NODES{n,m}.optimal_policy  = pol;
end
node = NODES{n,m};
end