%% SCRIPT TO CALCULATE OPTIMAL COST AND POLICY
% begin with the final state

% script to initialize value iteration and set the workspace environment
% clear all
% global NODES 
% load lib/cost_network_v0.1.mat 
% m = 51; n = 101; % the goal
% NODES{m,n}.optimal_value = 0;
% i = 1;
% [m,n,connections] = network_search(m,n);

for j = 4:10
    for i = i:length(m)
        evaluateConnection(m(i),n(i),connections{i});
        [mm,nn,cconn] = network_search(m(i),n(i));
        m = [m,mm];
        n = [n,nn];
        connections = [connections cconn];
    end
end
save('lib/current_6_12_2018_22_21.mat','connections','m','n','i')
save('lib/cost_network_v0.3.mat','NODES')