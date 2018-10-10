%%%% modified from GarciaModelDerivation.m %%%%
%%% q1 absolute angle of stance leg wrt to vertical
%%% alpha absolute angle of torso wrt to vertical

clc;
clear all;

syms q alpha real %Angles as defined in figures (theta and phi resp in garcia's figure)
syms u real %Angular velocity (thetadot and phidot resp in garcia's figure)
syms ud real%Angular Acceleration
syms gam g real %slope of ramp, gravity
syms L l n real % com of torso, leg length, number of spokes
syms M m I_M I_m real  %masses and inertia, 1 wheel, 2 torso
syms v real %angles before heelstrike
syms r real %velocities before heelstrike

I_M = 0;
I_m = 0;
%gam = 0;
%l = 1;
%m = 1;

i=[1 0 0];
j=[0 1 0];
k=[0 0 1];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                 Reference Frames                  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
X1 = sin(q)*i - cos(q)*j; 
X3 = sin(q+(2*pi/n))*i - cos(q+(2*pi/n))*j; 

X2 = sin(alpha)*i - cos(alpha)*j; 

J  = -sin(gam)*i+cos(gam)*j; 
I  = cos(gam)*i + sin(gam)*j;

R_XYZ_xyz = [I(1,1), I(1,2); ...
             J(1,1), J(1,2)]; %XYZ = R_XYZ_xyz xyz (any vector in xyz)
         
%R_xyz_XYZ = inv(R_XYZ_xyz);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               Position Vectors                    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Original position vectors
r_G1_G2 = L*X2; 
r_G1_P = l*X1;
r_G1_Q = l*X3;

r_P_G1 = -r_G1_P;
r_P_G2 = r_P_G1+r_G1_G2;
r_Q_G1 = -r_G1_Q;
r_Q_G2 = r_Q_G1+r_G1_G2; 


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%        Angular Velocities and Accelerations       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

om1 = u*k;
om2 = 0*k;

al1 = ud*k;
al2 = 0*k;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Constraints, Linear Velocities and Accelerations %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
xh = -l*sin(q);
yh =  l*cos(q);
   
    xhdot  = jacobian(xh,q)*u;
    yhdot  = jacobian(yh,q)*u;
    xhddot = jacobian(xhdot,q)*u + jacobian(xhdot,u)*ud;
    yhddot = jacobian(yhdot,q)*u + jacobian(yhdot,u)*ud;
    
v_G1 = xhdot*i+yhdot*j; 
a_G1 = xhddot*i+yhddot*j;
v_G2 = v_G1 +cross(om2,r_G1_G2);
a_G2 = a_G1 +cross(om2,cross(om2,r_G1_G2))+cross(al2,r_G1_G2);


% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % Center of Mass from support point and world frame %
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% r_com = (m*r_G1_P + M*r_G1_G2)/(m+M);
% x_com = r_com(1);
% y_com = r_com(2);
% disp(' ');
% disp(['x_com = ',char(x_com),';']); 
% disp(['y_com = ',char(y_com),';']); 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%        Collision Condition (Events)               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%h = q+sym(pi)/n; %yhdash-yh; %approaches zero from the top
h = l*cos(q) - l*cos(q+(2*pi/n));

disp(' ');
disp(['h = ',char(h),';']); 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Change of Angular Momentum & External Moments    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

M_P = dot(...
           m*g*cross(r_P_G1,-J)+ ...
           M*g*cross(r_P_G2,-J), ...
           k);
Hdot_P = dot(...
           m*cross(r_P_G1,a_G1)+I_m*al1 + ...
           M*cross(r_P_G2,a_G2)+I_M*al2,...
           k);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    Angular Momentum, (Before and After Heelstrike  % 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

H_Pp = dot(...
            m*cross(r_P_G1,v_G1) + I_m*om1 + ...
            M*cross(r_P_G2,v_G2) + I_M*om2, ...
            k);
H_Qn = subs(...
                dot(...
                   m*cross(r_Q_G1,v_G1) + I_m*om1 + ...
                   M*cross(r_Q_G2,v_G2) + I_M*om2   ...
                   ,k)...
            ,{u,q},{v,r});
        


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   EOM:[M-Hdot=0](Single Stance)  % 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
AMB_P = Hdot_P-M_P; %take negative of this to make equations symmetric

%%% Single stance equations %%%
    RHSs = -subs(AMB_P,ud,0); 
    Ms  =  subs(AMB_P,ud,1) + RHSs;
  
     

%%%%%%%%%%%%%%% Jacobian of single_stance %%%%%%%%%%%%%%%
disp(' ');
disp(['M1 = ', char(simplify(Ms)),';']);
disp(['RHS1 = ', char(simplify(RHSs)),';']);

% pretty(simplify(Ms))
% pretty(simplify(RHSs))
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Heelstrike:[H+ = H-](Single Stance) %  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

AM_P = H_Pp;

%%%%%% Heelstrike: H-, Transition to Single stance 
     RHShs = H_Qn;
     Mhs  =  subs(AM_P,u,1);
   
disp(' ');
disp(['M1 = ', char(simplify(Mhs)),';']);
disp(['RHS1 = ', char(simplify(RHShs)),';']);

% pretty(simplify(Mhs))
% pretty(simplify(RHShs))

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Reaction force on the stance leg in ground frame XYZ 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
F_xyz = m*a_G1 + M*a_G2;
F_XYZ = R_XYZ_xyz*[F_xyz(1,1); F_xyz(1,2)];
FX = F_XYZ(1,1);
FY = F_XYZ(2,1)+(m+M)*g;
disp(' ');
disp(['FX = ',char(simplify(FX)),';']);
disp(['FY = ',char(simplify(FY)),';']);