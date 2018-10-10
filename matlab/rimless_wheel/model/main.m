format long
close all
clc
clear all

parms = get_parms;

q = 0;%angle should always be zero
u = -0.5;%mid-stance velocity 
fps = 30;
farview = 0; %=1 to have a farview of the animation
steps = 20;

if (parms.fixed==1)
    z0 = [q u];% [angle rate];

    [z,t,thetadotmid,Avg_Velocity,error_flag] = onestep_fixed(z0,parms,steps);
    if (error_flag ~= 0) %%0 no failure, 1 = ground penetration, 2 = ground reaction force < 0 
        warning('simulation failed: change initial condition or torso angle');
    end

    disp('Animating...');
    %disp('NOTE: Animation speed can be changed using fps defined in the code');
    figure(1)
    animate_fixed(t,z,parms,steps,fps,farview);

    figure(2)
    subplot(2,1,1)
    plot(t,z(:,1),'r');
    subplot(2,1,2)
    plot(t,z(:,2),'b');
else
    %q1 = 0;%angle should always be zero
    %u1 = -0.1;%mid-stance velocity 
    q2 = parms.control.alpha; %0.25; %parms.control.q2;
    u2 = 0;
    z0 = [q u q2 u2];% [angle rate];

    [z,t,thetadotmid,Avg_Velocity,error_flag] = onestep_dynamics(z0,parms,steps);
    if (error_flag ~= 0) %%0 no failure, 1 = ground penetration, 2 = ground reaction force < 0 
        warning('simulation failed: change initial condition or torso angle');
    end

    %fps = 30;
    %farview = 0; %=1 to have a farview of the animation
    disp('Animating...');
    %disp('NOTE: Animation speed can be changed using fps defined in the code');
    figure(1)
    animate_dynamics(t,z,parms,steps,fps,farview);

    figure(2)
    subplot(2,1,1)
    plot(t,z(:,1),t,z(:,3));
    ylabel('absolute angles (rad)');
    legend('body','torso');
    subplot(2,1,2)
    plot(t,z(:,2),t,z(:,4));
    ylabel('absolute angular rates (rad/s)');
    xlabel('time (s)');
    legend('body','torso');
end