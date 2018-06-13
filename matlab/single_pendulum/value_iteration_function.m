function [m,n,connections,i] = value_iteration_function(m,n,connections,i)
    for i = i:length(m)
        evaluateConnection(m(i),n(i),connections{i});
        [mm,nn,cconn] = network_search(m(i),n(i));
        m = [m,mm];
        n = [n,nn];
        connections = [connections cconn];
    end
end

