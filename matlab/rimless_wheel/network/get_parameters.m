function parms = get_parameters(fixed)

parms.fixed = fixed; %1 for torso fixed
                 %anything else uses torso with dynamics
parms.g = 9.81;
parms.n = 10; %spokes
parms.gam = 0.0; %slope
parms.ignore_VelocityCondition = 0; %detect backward motion
parms.control.alpha = 50*(pi/180); %torso angle

m_wheel = 2.32;
m_torso = 4.194;
leg_length = 0.26;
torso_com = 0.048;


if (parms.fixed == 1)
    parms.m = m_wheel; %1;
    parms.M = m_torso;% 1;
    parms.l = leg_length;% 1;
    parms.L = torso_com; %0.5; %distance of torso from pin joint

    
    %parms.ignore_VelocityCondition = 0; %detect backward motion
    %parms.control.alpha = 45*(pi/180);%0.5401; %0.54006 %1.33;  %0.57 (%1.3961);
    parms.disturb.height = 0.0*parms.l; 
    parms.disturb.gam = 0;
else
    parms.m1 = m_wheel;% 1;
    parms.m2 = m_torso; %1;
    parms.I1 = 0.0;
    parms.I2 = 0.0;
    parms.l = leg_length; %1;
    parms.c = torso_com; %0.5;
    parms.w = 0;
%     parms.g = 10;
%     parms.n = 10; %spokes 
%    parms.gam = 0.0; %slope



    %parms.control.alpha = 45*(pi/180);%0.5401; %0.54006 %1.33;  %0.57 (%1.3961);
    parms.disturb.height = 0.0*parms.l; 
    %parms.disturb.gam = 0;

    parms.control.V = 0;
    parms.control.kp_q2 = 200;
    parms.control.kp_u2 = parms.control.kp_q2*0.1;
    parms.control.q2 = parms.control.alpha; %torso angle %0.25;
    parms.control.u2 = 0;
    parms.control.kp_u1 = 0; 
    parms.control.u1 = 0;
    %parms.control.T2 = 0;

end

