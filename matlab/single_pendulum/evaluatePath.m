function [value, policy] = evaluatePath(mstate, nstate)
%% evaluate the policy and value of a node
% if they have already been calculated use those values otherwise evaluate
% the connected nodes paths
global NODES counter
% check in to see that the optimal value is empty
% this method of checking is necessary because it is possible for the
% optimal value to be set to zero which would cause issues
counter = counter + 1;
if counter > 100
    value = NAN;
    policy = [];
    return
end
if length(NODES{mstate, nstate}.optimal_value) == 0
    for i = 1:length(NODES{mstate, nstate}.connections)
        [value, policy] = evaluatePath(...
            NODES{mstate, nstate}.connections{i}(1),...
            NODES{mstate, nstate}.connections{i}(2)...
            );
        if isempty(NODES{mstate, nstate}.optimal_value)
            NODES{mstate, nstate}.optimal_value = value + NODES{mstate, nstate}.connections{i}(4);
            NODES{mstate, nstate}.optimal_policy = [NODES{mstate, nstate}.connections{i}(1:2) policy];
        elseif value + NODES{mstate, nstate}.connections{i}(2) < NODES{mstate, nstate}.optimal_value 
            NODES{mstate, nstate}.optimal_value = value + NODES{mstate, nstate}.connections{i}(4);
            NODES{mstate, nstate}.optimal_policy = [NODES{mstate, nstate}.connections{i}(1:2) policy];
        end
    end
end
value = NODES{mstate, nstate}.optimal_value;
policy = NODES{mstate, nstate}.optimal_policy;
end
