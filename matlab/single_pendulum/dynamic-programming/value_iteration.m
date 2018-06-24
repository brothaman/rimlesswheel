function [m,n,connections,i] = value_iteration(connections,n,m,i)
%% SCRIPT TO CALCULATE OPTIMAL COST AND POLICY
% begin with the final state
global NODES count
% script to initialize value iteration and set the workspace environment
evaluateConnectionTime = [];
networksearchtime = [];
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
count = count + 1;
save(strcat('../lib/current_6_12_2018_22_21_iteration', int2str(count),'.mat'),'connections','m','n','i')
save(strcat('../lib/cost_network_v0.4i',int2str(count),'.mat'),'NODES')
end