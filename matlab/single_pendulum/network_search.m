function [m,n,connections] = network_search(m_,n_)
%% NETWORK_SERCH searches the network to find state with connections to the given state
global NODES
n = [];
m = [];
connections = {};
for j = 1:101
    for k = 1:201
        for l = 1:length(NODES{j,k}.connections)
            if NODES{j,k}.connections{l}(1:2) == [m_,n_] 
                m(end+1) = j;
                n(end+1) = k;
                connections{end+1} = [NODES{j,k}.connections{l}];
%                 return;
            end
        end
    end
end

end