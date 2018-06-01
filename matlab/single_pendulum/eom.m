%% Equations of Motion for Single Tone Pendulum
% this file generate the equatsion of motion and exports them in to a file

syms m g l I theta thetadot thetaddot real

% defined physical variables
M = 1;
G = 9.81;
L = 1;

% calculate lagrangian
h = -l*cos(theta);
v = thetadot*l*[cos(theta);sin(theta); 0];
K = m*dot(v,v)/2;
P = m*g*h;
lagrangian = K - P;

% derive the equations of motion
dldtheta = diff(lagrangian, theta);
dldthetadot = diff(lagrangian, thetadot);
ddtdldthetadot = diff(dldthetadot, theta)*thetadot + diff(dldthetadot, thetadot)*thetaddot;
EOM = dldtheta - ddtdldthetadot;

% resolve the model into
symbolic_variables = [m,g,l];
physical_variables = [M,G,L];

model.M = subs(EOM,g,0);
model.D = EOM - model.M;

model.M = simplify(subs(model.M,symbolic_variables,physical_variables));
model.D = simplify(subs(model.D,symbolic_variables,physical_variables));
model.M = simplify(subs(model.M,thetaddot,1));
model.D = str2func(strcat('@(theta, thetadot)',char(model.D)));
model.M = str2func(strcat('@(theta, thetadot)',char(model.M)));
save('lib/model.mat')
