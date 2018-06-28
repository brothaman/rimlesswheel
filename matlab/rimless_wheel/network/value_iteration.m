function [conn, count] = value_iteration(conn, count)
global network

% -------------------------- performance data --------------------------- %
evaluateConnectionTime = [];
networksearchtime = [];
% ----------------------------------------------------------------------- %

% -------------------------- working data ------------------------------- %
temp = [];
% ----------------------------------------------------------------------- %

for i = 1:length(conn)
    % evaluate connection 
    evaluateConnectionTimer = tic;
    evaluateConnection(conn(i,:));
    evaluateConnectionTime(end+1) =  toc(evaluateConnectionTimer);
    
    % network search and return
    networksearchtimer  = tic;
    cc = networksearch(conn(i,:));
    networksearchtime(end+1) = toc(networksearchtimer);
    
    % store the new connections to evaluate in an array
    temp = [temp; cc];
end

d = datestr(datetime('today'));
d = strrep(d,'-','_');

% save the data generated
save(...
    strcat('../lib/valueiteration_', int2str(count),'_', d,'.mat'),...
    'temp','conn','evaluateConnectionTime','networksearchtime');
save(...
    strcat('../lib/cost_network_v0_iteration',int2str(count),'.mat'),...
    network);
% reassign the current array holding the connections 

count = count + 1;
end