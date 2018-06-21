format long
close all
clc
clear all

parms = get_parms;
parms.control.alpha = 45*(pi/180); %torso angle

q = 0;%angle should always be zero
u = -1;%mid-stance velocity 
z0 = [q u];% [angle rate];

steps = 1;
[z,t,thetadotmid,Avg_Velocity,error_flag] = onestep(z0,parms,steps);
if (error_flag ~= 0) %%0 no failure, 1 = ground penetration, 2 = ground reaction force < 0 
    warning('simulation failed: change initial condition or torso angle');
end

fps = 30;
farview = 0; %=1 to have a farview of the animation
disp('Animating...');
%disp('NOTE: Animation speed can be changed using fps defined in the code');
figure(1)
animate(t,z,parms,steps,fps,farview);

figure(2)
subplot(2,1,1)
plot(t,z(:,1),'r');
subplot(2,1,2)
plot(t,z(:,2),'b');