%% load the model and the network
global NODES
global model
global counter
load('lib/cost_network.mat')
load('lib/model.mat')

% set the value of the desired state
NODES{51,101}.optimal_value = 0;
% get the variables stored
nangles = 100;
nspeeds = 200;

% choose a location to begin navigation
% lets start close to the desired value with zero velocity
[x1,m] = map(170*pi/180,[0 2*pi],100);
[x2,n] = map(0,[-6 6], 200);
X = [170*pi/180 0];


% begin recursive iteration 
% use the counter to keep track of the necessary 
[value, policy] = evaluatePath(m,n);