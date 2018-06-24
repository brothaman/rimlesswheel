function parms = get_parms

parms.m = 1;
parms.M = 1;
parms.l = 1;
parms.L = 0.5; %distance of torso from pin joint
parms.g = 10;
parms.n = 8; %spokes 
parms.gam = 0.0; %slope
parms.ignore_VelocityCondition = 0; %detect backward motion
parms.control.alpha = 45*(pi/180);%0.5401; %0.54006 %1.33;  %0.57 (%1.3961);
parms.disturb.height = 0.0*parms.l; 
parms.disturb.gam = 0;

