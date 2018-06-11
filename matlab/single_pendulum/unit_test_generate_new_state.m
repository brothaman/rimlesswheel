Xin = [0 0];
Xd  = [pi 0];
torque = 1;
time = 0.05;

anglerange = [0,2*pi];
speedrange = [-6,6];
torquerange = [-10,10];

global NODES
NODES = cell(101,101);
NODES(:,:) = {nNode};
generate_new_state( Xin, Xd, torque, time, anglerange, speedrange, torquerange)