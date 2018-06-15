function prune_network()
%% PRUNE_NETWORK
% this will prune undesired connections from the network 

% THis function will look for closed paths in the network and notify the
% user. Because i am currently not sure how to handle a 
% FIRST of all we will be looking for connections that 1 connection deep
% loops. this means that two states have connections to one another and a
% single state transition is required to navigate between them. In these
% cases those connections will need to be destroyed so that recursion black
% wholes are avoided. 

% SECOND we 