%===================================================================
function [z,t,thetadotmid,Avg_Velocity,error_flag]=onestep(z0,parms,steps)
%===================================================================

flag = 1;
if nargin<2
    error('need more inputs to onestep');
elseif nargin<3
    flag = 0; %send only last state
    steps = 1;
end

% -------------------------- made a change here ------------------------- %
% flag = 1;
% ----------------------------------------------------------------------- %

%thetadotmid=zeros(1,steps);
Avg_Velocity = zeros(1,steps);

t0 = 0; 
x_trans = -parms.l*sin(pi/parms.n); %distace moved by center of wheel.
t_ode = [];
z_ode = [];

thetadotmid = z0(1,2);
for i=1:steps

    [z_temp1,t_temp1] = fn_mid2bhs(z0,parms);
    %thetadotmid(i) = z_temp1(1,2);
    
    
    %h = parms.l*cos(z_temp1(:,1)) - parms.l*cos(z_temp1(:,1)+(2*pi/parms.n))+parms.disturb.height;
    %h = parms.l*cos(z_temp1(:,1)) - parms.l*cos(pi/parms.n)+parms.disturb.height;
    %h = z_temp1(:,1) + pi/parms.n;
    
%     if (parms.control.on==4)
%         [h z_temp1]
%     end
        
    t1 = t0+t_temp1(end);
    z0 = z_temp1(end,:);
    xtemp1 = -parms.l*sin(z_temp1(end,1));
    xhtemp1 = -parms.l*sin(z_temp1(:,1)); %x of wheel
    
    zplus = fn_bhs2ahs(z0,parms);
    %disp(['z_ahs  = ',num2str(zplus)]);
    
    [z_temp2,t_temp2] = fn_ahs2mid(zplus,parms);
    
    thetadotmid = [thetadotmid z_temp2(end,2)];

    xtemp2 = -parms.l*sin(z_temp2(end,1)) - (-parms.l*sin(z_temp2(1,1)));
    xhtemp2 =  -parms.l*sin(z_temp2(2:end,1))+2*xhtemp1(end,1); %2*xhtemp1 is the distance moved by support foot
    
    xtemp = xtemp1+xtemp2;
    
    t_temp = [t0+t_temp1(1:end); t1+t_temp2(2:end)];
    z_temp = [z_temp1(1:end,:); z_temp2(2:end,:)];
   
    %%% check penetration
    error_flag = check_failure(z_temp,parms);
    
    Time = t_temp(end)-t0; %step time.
    
    z0 = z_temp(end,:);
    t0 = t_temp(end);
    
   
    %post-processd data for storing
    Distance = xtemp; %xhtemp(end)-xhtemp(1);
    
    %xhtemp = xhtemp + Distance + x_trans;
    x_trans = x_trans + Distance;
    
     Velocity = Distance/Time;
     Avg_Velocity(i) = Velocity;
    % disp(['Velocity = ',num2str(Velocity)]);

    xhtemp = x_trans+[xhtemp1; xhtemp2];
    yhtemp = parms.l*cos(z_temp(:,1));    %y of wheel

    
    if (parms.ignore_VelocityCondition==0)
%         disp(['Steps = ', num2str(i), '; Velocity = ',num2str(Velocity)]);
        if (Velocity<0)
            warning('Velocity is less than zero. Modify T2 or launch condition');
        end
    end
    
    t_ode = [t_ode; t_temp(1:end)];
    z_ode = [z_ode;  ... 
             z_temp(1:end,:),xhtemp(1:end,1),yhtemp(1:end,1)];
    
end

z = z_temp(end,1:2);

if flag==1
   z=z_ode;
   t=t_ode;
elseif flag == 0
    z = z_temp(end,:);
    t = t_temp(end);
end




%===================================================================
function [zout,tout] = fn_ahs2mid(z0,parms)
%===================================================================
t0 = 0;
dt = 3;
tspan = linspace(t0,t0+dt,500);
if (parms.ode_MATLAB)
    options=odeset('abstol',1e-9,'reltol',1e-9,'events',@midstance);
    [tout, zout] = ode113(@single_stance,tspan,z0,options,parms);
else
    parms2 = [parms.m1 parms.m2 parms.c parms.w parms.l parms.g parms.I1 parms.I2 parms.n ...
              parms.gam parms.disturb.height parms.control.T2];
    options_dop = dopset('AbsTol',1e-9,'RelTol',1e-9,'Events',1,'EventTol',1e-9);
% --------- if you havent run it yet this should be uncommented ----------%
%     [tout,zout,te,ye,ie,stats] = dop853('single_stance_ahs2mid',tspan,z0,options_dop,parms2'); 
% -------- after the initial run this line should be uncommented ---------%
    [tout,zout,te,ye,ie,stats] = dop853_single_stance_ahs2mid(tspan,z0,options_dop,parms2');
end

if (nargout==1)
    zout = zout(end,:);
end

%===================================================================
function [zout,tout] = fn_mid2bhs(z0,parms)
%===================================================================
t0 = 0;
dt = 3;

tspan = linspace(t0,t0+dt,500);
if (parms.ode_MATLAB)
    options=odeset('abstol',1e-9,'reltol',1e-9,'events',@collision);
    [tout, zout] = ode113(@single_stance,tspan,z0,options,parms);
else
    parms2 = [parms.m1 parms.m2 parms.c parms.w parms.l parms.g parms.I1 parms.I2 parms.n ...
              parms.gam parms.disturb.height parms.control.T2];
    options_dop = dopset('AbsTol',1e-9,'RelTol',1e-9,'Events',1,'EventTol',1e-9);
% --------- if you havent run it yet this should be uncommented ----------%
%     [tout,zout,te,ye,ie,stats] = dop853('single_stance_mid2bhs',tspan,z0,options_dop,parms2'); 
% -------- after the initial run this line should be uncommented ---------%
    [tout,zout,te,ye,ie,stats] = dop853_single_stance_mid2bhs(tspan,z0,options_dop,parms2');   
end

if (nargout==1)
    zout = zout(end,:);
end

%===================================================================
function zout =fn_bhs2ahs(z,parms)  
%===================================================================
zout=heelstrike(z,parms);


%===================================================================
function zdot=single_stance(t,z,parms)  
%===================================================================

q1 = z(1); u1 = z(2);
q2 = z(3); u2 = z(4);


%T2_openloopcontrol = parms.control.V - u1; %open loop, motor model is V = T + w
%T2_torsopositioncontrol = -parms.control.kp_q2*(q2-parms.control.q2)-parms.control.kp_u2*(u2-parms.control.u2); %position control
%T2_wheelspeedcontrol = -parms.control.kp_u1*(u1-parms.control.u1);   %speed control
T2 = parms.control.T2; %T2_openloopcontrol + T2_torsopositioncontrol + T2_wheelspeedcontrol;

m1 = parms.m1; m2 = parms.m2; I1 = parms.I1; I2 = parms.I2;
l = parms.l; c = parms.c; w = parms.w; g = parms.g; gam = parms.gam;

M11 = I1 + l^2*m1 + l^2*m2 - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
M21 = -l*m2*(c*cos(q1 - q2) + w*sin(q1 - q2));
M12 = I2 + c^2*m2 + m2*w^2 - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
M22 = I2 + c^2*m2 + m2*w^2;
RHS1 = c*g*m2*sin(gam - q2) - g*m2*w*cos(gam - q2) - g*l*m1*sin(gam - q1) - g*l*m2*sin(gam - q1) - c*l*m2*u1^2*sin(q1 - q2) + c*l*m2*u2^2*sin(q1 - q2) + l*m2*u1^2*w*cos(q1 - q2) - l*m2*u2^2*w*cos(q1 - q2);
RHS2 = T2 + c*g*m2*sin(gam - q2) - g*m2*w*cos(gam - q2) - c*l*m2*u1^2*sin(q1 - q2) + l*m2*u1^2*w*cos(q1 - q2);
 
M = [M11 M12; M21 M22];
RHS = [RHS1; RHS2];
X = M\RHS;
zdot = [u1 X(1,1) u2 X(2,1)]';

%===================================================================
function zplus=heelstrike(zminus,parms)      
%===================================================================


r1 = zminus(1);   v1 = zminus(2);
r2 = zminus(3);   v2 = zminus(4);

m1 = parms.m1; m2 = parms.m2; I1 = parms.I1; I2 = parms.I2; n = parms.n;
l = parms.l; c = parms.c; w = parms.w; g = parms.g; gam = parms.gam;

q1 = -r1;
q2 = r2;

M11 = I1 + l^2*m1 + l^2*m2 - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
M21 = - c*l*cos(q1 - q2) - l*w*sin(q1 - q2);
M12 = I2 + c^2*m2 + m2*w^2 - c*l*m2*cos(q1 - q2) - l*m2*w*sin(q1 - q2);
M22 = I2 + c^2 + w^2;

RHS1 = I1*v1 + I2*v2 - m2*((v2*(c*cos(r2) - w*sin(r2)) - l*v1*cos(r1))*(l*cos(r1 + pi/n) - c*cos(r2) + w*sin(r2)) - (v2*(c*sin(r2) + w*cos(r2)) - l*v1*sin(r1))*(c*sin(r2) - l*sin(r1 + pi/n) + w*cos(r2))) + l^2*m1*v1*cos(pi/n);
RHS2 = I2*v2 + c^2*v2 + v2*w^2 - c*l*v1*cos(r1 - r2) - l*v1*w*sin(r1 - r2);

M = [M11 M12; M21 M22];
RHS = [RHS1; RHS2];
X = M\RHS;
zplus = [q1 X(1,1) q2 X(2,1)];


%===================================================================
function [h, isterminal,direction]=midstance(t,x,parms)
%===================================================================

%n = parms.n;
q = x(1);

h = q;
isterminal=1; %= 1 if the integration is to terminate at a zero of this event function, otherwise, 0.
direction = -1; %= 0 if all zeros are to be located (the default), +1 if only zeros where the event function is increasing, and -1 if only zeros where the event function is decreasing.



%===================================================================
function [h, isterminal,direction]=collision(t,x,parms)
%===================================================================

n = parms.n;
q = x(1);


h = parms.l*cos(q) - parms.l*cos(q+(2*pi/n))+parms.disturb.height;
%h = parms.l*cos(q) - parms.l*cos(pi/n)+parms.disturb.height; 
%h = q+pi/n;
isterminal=1; %= 1 if the integration is to terminate at a zero of this event function, otherwise, 0.
direction = -1; %= 0 if all zeros are to be located (the default), +1 if only zeros where the event function is increasing, and -1 if only zeros where the event function is decreasing.



%===================================================================
function flag=check_failure(z,parms)
%===================================================================
%q = z(:,1); %store angle
m1 = parms.m1; m2 = parms.m2; %I1 = parms.I1; I2 = parms.I2; n = parms.n;
l = parms.l; c = parms.c; w = parms.w; g = parms.g; gam = parms.gam;

flag = 0;

%%%%%%%% check ground penetration %%%%%%%
qmin = min(z(:,1));
qmax = max(z(:,1));
if (qmin < (-pi/parms.n)-0.1 || qmax > (pi/parms.n)+0.1)
    warning('robot walk failure: ground penetration');
    flag = 1;
    return
end

%%%%%%%% check reaction forces %%%%%%%
Fy = zeros(length(z),1);
for i=1:length(Fy)
    t = 0;    
    q1 = z(i,1);
    u1 = z(i,2);
    q2 = z(i,3);
    u2 = z(i,4);
    zdot=single_stance(t,[q1 u1 q2 u2],parms);
    ud1 = zdot(2);
    ud2 = zdot(4);
    Fy(i,1) = cos(gam)*(m2*(ud2*(c*sin(q2) + w*cos(q2)) + u2^2*(c*cos(q2) - w*sin(q2)) - l*ud1*sin(q1) - l*u1^2*cos(q1)) - m1*(l*ud1*sin(q1) + l*u1^2*cos(q1))) - sin(gam)*(m2*(ud2*(c*cos(q2) - w*sin(q2)) - u2^2*(c*sin(q2) + w*cos(q2)) - l*ud1*cos(q1) + l*u1^2*sin(q1)) - m1*(l*ud1*cos(q1) - l*u1^2*sin(q1))) + g*(m1 + m2);
    %Fy(i,1) = (parms.M + parms.m)*(parms.g - u^2*cos(parms.gam - q) + ud*sin(parms.gam - q));
end

Fymin = min(Fy);
if (Fymin<0)
     warning('robot walk failure: vertical reaction force is zero');
     flag = 2;
     return
end

q2_all = z(:,3);
index1 = isempty(find(q2_all > pi/2,1));
index2 = isempty(find(q2_all < -pi/2,1));
if (~index1 || ~index2)
    warning('robot walk failure imminent: torso beyond horizontal');
     flag = 3;
     return
end