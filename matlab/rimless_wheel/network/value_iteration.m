function [conn, count] = value_iteration(conn, count)
global network

% -------------------------- performance data --------------------------- %
evaluateConnectionTime = [];
networksearchtime = [];
% ----------------------------------------------------------------------- %

% -------------------------- working data ------------------------------- %
temp = [];
% ----------------------------------------------------------------------- %

% conn should be an Nx2 vector storing the state and the connection
for i = 1:size(conn,1)
    % evaluate connection 
    evaluateConnectionTimer = tic;
    evaluateConnection(conn(i,:));
    evaluateConnectionTime(end+1) =  toc(evaluateConnectionTimer);
    
    % network search and return
    networksearchtimer  = tic;
    cc = network_search(conn(i,1), length(network));
    networksearchtime(end+1) = toc(networksearchtimer);
    
    % store the new connections to evaluate in an array
    temp = [temp; cc];
end

d = datestr(datetime('today'));
d = strrep(d,'-','_');

% save the data generated
save(...
    strcat('../lib/DEBUGvalueiteration_', int2str(count),'_', d,'.mat'),...
    'temp','conn','evaluateConnectionTime','networksearchtime','count');
save(...
    strcat('../lib/DEBUGcost_network_v0_iteration',int2str(count),'.mat'),...
    'network');

% reassign the current array holding the connections 
conn = temp;

% increment the count
count = count + 1;
end