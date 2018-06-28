function evaluateConnection(c)
global network
transition_cost = network{c(1)}.connections{c(2)}(3);
n = network{c(1)}.connections{c(2)}(1);
state_cost = network{n}.optimal_value;

if isempty(network{c(1)}.optimal_value)
    network{c(1)}.optimal_value = transition_cost + state_cost;
    network{c(1)}.optimal_policy  = c(2);
% otherwise check to see if there is a value in 
elseif network{c(1)}.optimal_value > transition_cost + state_cost
    network{c(1)}.optimal_value = transition_cost + state_cost;
    network{c(1)}.optimal_policy  = c(2);
end
end