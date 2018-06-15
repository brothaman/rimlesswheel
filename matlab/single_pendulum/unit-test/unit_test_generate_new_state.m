Xin = [0 6];
Xd  = [pi 0];
torque = 10;
time = 0.05;

anglerange = [0,2*pi];
speedrange = [-6,6];
torquerange = [-10,10];

global NODES
initialize_NODES(101,201);
generate_new_state( Xin, Xd, torque, time, anglerange, speedrange, torquerange)
Xin = [pi 0];
Xd  = [pi 0];
torque = 0;
time = 0.05;
generate_new_state( Xin, Xd, torque, time, anglerange, speedrange, torquerange)