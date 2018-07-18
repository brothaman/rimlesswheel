function [connected_nodes, parallel_timer, reshape_timer] = search_network2(NODES,conns)
    len = size(conns,1);
    connected_nodes = zeros(len,22,3);
    parallel_timer = tic;
    parfor i = 1:len
        connections_found = network_search(NODES,conns(i,1),conns(i,2));
        len = size(connections_found,1);
        for j = 1:22
            if j > len
                continue;
            end
            connected_nodes(i,j,:) = connections_found(j,:);
%             connected_nodes(i,j,2) = connections_found(j,2);
%             connected_nodes(i,j,3) = connections_found(j,3);
        end
    end
    parallel_timer = seconds(toc(parallel_timer));
    % now reshape output variable
    len = size(conns,1);
    pretty_connected_nodes = zeros(len*22,3);
    reshape_timer = tic;
    for i = 1:len
        for j = 1:22
            pretty_connected_nodes((i-1)*22+j,:) = connected_nodes(i,j,:);
        end
    end
    % now get rid of zeros
    connected_nodes = pretty_connected_nodes(any(pretty_connected_nodes,2),:);
    reshape_timer = seconds(toc(reshape_timer));
    reshape_timer.Format = 'hh:mm:ss.SSS';
    parallel_timer.Format = 'hh:mm:ss.SSS';
end
