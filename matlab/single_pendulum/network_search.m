function [m,n,connections] = network_search(m_,n_)
%% NETWORK_SERCH searches the network to find state with connections to the given state
global NODES
n = [];
m = [];
connections = [];
for j = 1:101
    for k = 1:201
        for l = 1:length(NODES{j,k}.connections)
            
            % if the node in question's optimal policy has a connection
            % equal to the state we are looking at it do not add that
            % connection to the list to be evaluated. this will produce a
            % loop and the number of connections to evaluate will grow to
            % an infinite value. in other words im looking to eliminate 1
            % deep cylclic loops.
%             if ~isempty(p)
%                 if NODES{m_,n_}.connections{p}(1:2) == [j,k]
%                     dont = true;
%                 end
%             end
            if sum(NODES{j,k}.connections{l}(1:2) == [m_,n_]) == 2
                p = NODES{m_,n_}.optimal_policy;
                dont = false;
                if ~isempty(p)
                    if NODES{m_,n_}.connections{p}(1:2) ~= [j,k]
                        m(end+1) = j;
                        n(end+1) = k;
                        connections = [connections ;[NODES{j,k}.connections{l}]];
                    end
                else
                    m(end+1) = j;
                    n(end+1) = k;
                    connections = [connections ;[NODES{j,k}.connections{l}]];
                end
            end
        end
    end
end

end