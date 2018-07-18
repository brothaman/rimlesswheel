function parms = get_parms
% 
parms.m1 = 1;
parms.m2 = 1;
parms.I1 = 0.0;
parms.I2 = 0.0;
parms.l = 1;
parms.c = 0.5;
parms.w = 0;
parms.g = 10;
parms.n = 10; %spokes 
parms.gam = 0.0; %slope
parms.ignore_VelocityCondition = 0; %detect backward motion
parms.ode_MATLAB = 0;


%parms.control.alpha = 45*(pi/180);%0.5401; %0.54006 %1.33;  %0.57 (%1.3961);
parms.disturb.height = 0.0*parms.l; 
%parms.disturb.gam = 0;

% parms.control.V = 0;
% parms.control.kp_q2 = 200;
% parms.control.kp_u2 = parms.control.kp_q2*0.1;
% parms.control.q2 = 1.0;
% parms.control.u2 = 0;
% parms.control.kp_u1 = 0; 
% parms.control.u1 = 0;
parms.control.T2 = 3;
