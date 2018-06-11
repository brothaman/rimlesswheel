function [value, policy] = evaluatePath(nodeID)
% evaluate the policy and value of a node
% if they have already been calculated use those values otherwise evaluate
% the connected nodes paths
global NODES
value = []; policy = [];
if length(NODES{nodeID}.optimal_value) == 0
    for i = 1:length(NODES{nodeID}.connections)
        [value, policy] = evaluatePath(NODES{nodeID}.connections{i}(1));
        if length(NODES{nodeID}.optimal_value) == 0
            NODES{nodeID}.optimal_value = value + NODES{nodeID}.connections{i}(2);
            NODES{nodeID}.optimal_policy = [NODES{nodeID}.connections{i}(1) policy];
        elseif value + NODES{nodeID}.connections{i}(2) < NODES{nodeID}.optimal_value 
            NODES{nodeID}.optimal_value = value + NODES{nodeID}.connections{i}(2);
            NODES{nodeID}.optimal_policy = [NODES{nodeID}.connections{i}(1) policy];
        end
    end
end
value = NODES{nodeID}.optimal_value;
policy = NODES{nodeID}.optimal_policy;

end
