%% SCRIPT TO CALCULATE OPTIMAL COST AND POLICY
% begin with the final state

% script to initialize value iteration and set the workspace environment
clear all
global NODES 
load lib/cost_network_v0.1.mat 
m = 51; n = 101; % the goal
NODES{m,n}.optimal_value = 0;
i = 1;
[m,n,connections] = network_search(m,n);
evaluateConnectionTime = [];
networksearchtime = [];
for j = 1:10
    tempm = [];
    tempn = [];
    tempconnections = [];
    for i = i:length(m)
        evaluateConnectionTimer = tic;
        evaluateConnection(m(i),n(i),connections(i,:));
        evaluateConnectionTime(end+1) =  toc(evaluateConnectionTimer);
        networksearchtimer  = tic;
        [mm,nn,cconn] = network_search(m(i),n(i));
        networksearchtime(end+1) = toc(networksearchtimer);
        tempm = [tempm,mm];
        tempn = [tempn,nn];
        tempconnections = [tempconnections ;cconn];
    end
    % search for unique states to evaluate if the state is repeated there
    % is no need to calculate an optimal path multiple times
    temp = [tempm',tempn',tempconnections];
    temp = unique(temp,'rows');
    m = [m temp(:,1)'];
    n = [n temp(:,2)'];
    connections = [connections; temp(:,3:end)];    
end
save('lib/current_6_12_2018_22_21.mat','connections','m','n','i')
save('lib/cost_network_v0.4.mat','NODES')