%===================================================================
function [z,t,thetadotmid,Avg_Velocity,error_flag]=onestep(z0,parms,steps,varargin)
%===================================================================

if nargin > 3
    flag = varargin{4};
else
    flag = 1;
end
if nargin<2
    error('need more inputs to onestep');
elseif nargin<3
    flag = 0; %send only last state
    steps = 1;
end
thetadotmid=zeros(1,steps);
Avg_Velocity = zeros(1,steps);

alpha = parms.control.alpha;
t0 = 0; 
x_trans = -parms.l*sin(pi/parms.n); %distace moved by center of wheel.
t_ode = [];
z_ode = [];

thetadotmid = z0(1,2);
for i=1:steps

    % integrate until collision
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
    
    % determine the state after heel strike from the state given at the
    % time of collision
    zplus = fn_bhs2ahs(z0,parms);
    
    % integrate from just after heel strike to the next midstance
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
        %disp(['Steps = ', num2str(i), '; Velocity = ',num2str(Velocity)]);
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
end




%===================================================================
function [zout,tout] = fn_ahs2mid(z0,parms)
%===================================================================
t0 = 0;
dt = 3;
options=odeset('abstol',1e-9,'reltol',1e-9,'events',@midstance);
tspan = linspace(t0,t0+dt,500);
[tout, zout] = ode113(@single_stance,tspan,z0,options,parms);

if (nargout==1)
    zout = zout(end,:);
end

%===================================================================
function [zout,tout] = fn_mid2bhs(z0,parms)
%===================================================================
t0 = 0;
dt = 3;
options=odeset('abstol',1e-9,'reltol',1e-9,'events',@collision);
tspan = linspace(t0,t0+dt,500);
[tout, zout] = ode113(@single_stance,tspan,z0,options,parms);

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
q = z(1); u = z(2);
M = parms.M; L = parms.L; g = parms.g; %n = parms.n;
gam = parms.gam+parms.disturb.gam;
m = parms.m;

%control variable
alpha = parms.control.alpha;

% M1 = M - L*M*cos(alpha - q) + 1;
% RHS1 = g*sin(q) + M*g*sin(q) - L*M*g*sin(alpha) + L*M*u^2*sin(alpha - q);
% M1 = M - L*M*cos(alpha - q) + 1;
% RHS1 = L*M*u^2*sin(alpha - q) - M*g*sin(gam - q) - L*M*g*sin(alpha - gam) - g*sin(gam - q);
M1 = M + m - L*M*cos(alpha - q);
RHS1 = L*M*u^2*sin(alpha - q) - g*m*sin(gam - q) - L*M*g*sin(alpha - gam) - M*g*sin(gam - q);
X = M1\RHS1;

zdot = [u X(1,1)]';

%===================================================================
function zplus=heelstrike(zminus,parms)      
%===================================================================

r = zminus(1);   v = zminus(2);

alpha = parms.control.alpha;
M = parms.M; L = parms.L; n = parms.n; %g = parms.g; %gam = parms.gam;
m = parms.m;

%q = -r;
%q = acos(cos(r));
q = acos( cos(r) + parms.disturb.height/L);

% M1 = M - L*M*cos(alpha - q) + 1;
% RHS1 = v*(cos((2*pi)/n) + M*cos((2*pi)/n) - L*M*cos(alpha - r));
M1 = M + m - L*M*cos(alpha - q);
RHS1 = M*v*cos((2*pi)/n) + m*v*cos((2*pi)/n) - L*M*v*cos(alpha - r);
X = M1\RHS1;

zplus = [q X(1,1)]; 


%===================================================================
function [h, isterminal,direction]=midstance(t,x,parms)
%===================================================================

%n = parms.n;
q = x(1);

h = q;
isterminal=1; %= 1 if the integration is to terminate at a zero of this event function, otherwise, 0.
 % = 0 if all zeros are to be located (the default), +1 if only zeros where 
 % the event function is increasing, and -1 if only zeros where the event function is decreasing.
 direction = -1;



%===================================================================
function [h, isterminal,direction]=collision(t,x,parms)
%===================================================================

n = parms.n;
q = x(1);


h = parms.l*cos(q) - parms.l*cos(q+(2*pi/n))+parms.disturb.height;
%h = parms.l*cos(q) - parms.l*cos(pi/n)+parms.disturb.height; 
%h = q+pi/n;
isterminal=1; %= 1 if the integration is to terminate at a zero of this event function, otherwise, 0.
% = 0 if all zeros are to be located (the default), +1 if only zeros where 
% the event function is increasing, and -1 if only zeros where the event function is decreasing.
direction = -1; 



%===================================================================
function flag=check_failure(z,parms)
%===================================================================
%q = z(:,1); %store angle
flag = 0;
qmin = min(z(:,1));
qmax = max(z(:,1));
if (qmin < (-pi/parms.n)-0.1 || qmax > (pi/parms.n)+0.1)
    warning('robot walk failure: ground penetration');
    flag = 1;
end

Fy = zeros(length(z),1);
for i=1:length(Fy)
    t = 0;    
    q = z(i,1);
    u = z(i,2);
    zdot=single_stance(t,[q u],parms);
    ud = zdot(2);
    Fy(i,1) = (parms.M + parms.m)*(parms.g - u^2*cos(parms.gam - q) + ud*sin(parms.gam - q));
end

Fymin = min(Fy);
if (Fymin<0)
     warning('robot walk failure: vertical reaction force is zero');
     flag = 2;
end

