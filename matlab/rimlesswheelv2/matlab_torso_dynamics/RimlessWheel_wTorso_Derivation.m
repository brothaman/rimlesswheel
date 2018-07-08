%%%% modified from GarciaModelDerivation.m %%%%
%%% q1 absolute angle of stance leg wrt to vertical
%%% q2 absolute angle of torso wrt to vertical

clc;
clear all;

syms q1 q2 real %Angles as defined in figures (theta and phi resp in garcia's figure)
syms u1 u2 real %Angular velocity (thetadot and phidot resp in garcia's figure)
syms ud1 ud2 real%Angular Acceleration
syms gam g real %slope of ramp, gravity
syms c w l n real % com of torso, leg length, number of spokes
syms m1 m2 I1 I2 real  %masses and inertia, 1 wheel, 2 torso
syms v1 v2 real %angles before heelstrike
syms r1 r2 real %velocities before heelstrike
syms T2 real %torque due to torse

i=[1 0 0];
j=[0 1 0];
k=[0 0 1];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                 Reference Frames                  %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
X1 = sin(q1)*i - cos(q1)*j; 
X3 = sin(q1+pi/n)*i - cos(q1+pi/n)*j; 

X2 = sin(q2)*i - cos(q2)*j; 
Y2 = cos(q2)*i + sin(q2)*j;

J  = -sin(gam)*i+cos(gam)*j; 
I  = cos(gam)*i + sin(gam)*j;

R_XYZ_xyz = [I(1,1), I(1,2); ...
             J(1,1), J(1,2)]; %XYZ = R_XYZ_xyz xyz (any vector in xyz)
         
%R_xyz_XYZ = inv(R_XYZ_xyz);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%               Position Vectors                    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Original position vectors
r_G1_G2 = c*X2+w*Y2; 
r_G1_P = l*X1;
r_G1_Q = l*X3;

r_P_G1 = -r_G1_P;
r_P_G2 = r_P_G1+r_G1_G2;
r_Q_G1 = -r_G1_Q;
r_Q_G2 = r_Q_G1+r_G1_G2; 


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%        Angular Velocities and Accelerations       %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

om1 = u1*k;
om2 = u2*k;
 
al1 = ud1*k;
al2 = ud2*k;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Constraints, Linear Velocities and Accelerations %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
q = [q1; q2];
u = [u1; u2];
ud = [ud1; ud2];

xh = -l*sin(q1);
yh =  l*cos(q1);
   
    xhdot  = jacobian(xh,q)*u;
    yhdot  = jacobian(yh,q)*u;
    xhddot = jacobian(xhdot,q)*u + jacobian(xhdot,u)*ud;
    yhddot = jacobian(yhdot,q)*u + jacobian(yhdot,u)*ud;
    
v_G1 = xhdot*i+yhdot*j; 
a_G1 = xhddot*i+yhddot*j;

v_G2 = v_G1 +cross(om2,r_G1_G2);
a_G2 = a_G1 +cross(om2,cross(om2,r_G1_G2))+cross(al2,r_G1_G2);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%        Collision Condition (Events)               %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
h = q1-sym(pi)/n; %yhdash-yh; %approaches zero from the top


disp(' ');
disp(['h = ',char(h),';']); 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Change of Angular Momentum & External Moments    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

M_P = dot(...
           m1*g*cross(r_P_G1,-J)+ ...
           m2*g*cross(r_P_G2,-J), ...
           k);
Hdot_P = dot(...
           m1*cross(r_P_G1,a_G1)+I1*al1 + ...
           m2*cross(r_P_G2,a_G2)+I2*al2,...
           k);

M_G1 = dot(...
          m2*g*cross(r_G1_G2,-J)+T2*k,...
          k);
Hdot_G1 = dot(...
          m2*cross(r_G1_G2,a_G2)+I2*al2,...
          k);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%    Angular Momentum, (Before and After Heelstrike  % 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% H_G1p = dot(beta*cross(r_G1_G2,v_G2)+cross(r_G1_H,v_H),k);
% H_G2n = subs(dot(beta*cross(r_G2_G1,v_G1)+cross(r_G2_H,v_H),k),...
%             {u1,u2,q1,q2},{v1,v2,r1,r2});


H_Pp = dot(...
            m1*cross(r_P_G1,v_G1) + I1*om1 + ...
            m2*cross(r_P_G2,v_G2) + I2*om2, ...
            k);
H_Qn = subs(...
                dot(...
                   m1*cross(r_Q_G1,v_G1) + I1*om1 + ...
                   m2*cross(r_Q_G2,v_G2) + I2*om2   ...
                   ,k)...
            ,{u1,u2,q1,q2},{v1,v2,r1,r2});
        
%%%%% The beta in this equation gets divided out.
% H_Hp = dot(cross(r_H_G2,v_G2),k);
% H_Hn = subs(dot(cross(r_H_G1,v_G1),k),...
%      {u1,u2,q1,q2},{v1,v2,r1,r2}); 

H_G1p = dot(...
           cross(r_G1_G2,v_G2) + I2*om2 ...
           ,k);
H_G1n = subs(...
             dot(...
                cross(r_G1_G2,v_G2) + I2*om2 ...
                ,k),...
             {u1,u2,q1,q2},{v1,v2,r1,r2});  %v_G2 is questionable.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%   EOM:[M-Hdot=0](Single Stance)  % 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
AMB_P = Hdot_P-M_P; %take negative of this to make equations symmetric
AMB_G1  = Hdot_G1-M_G1; 


%%% Single stance equations %%%
    RHSs1 = -subs(AMB_P,[ud1 ud2],[0 0]); 
    Ms11  =  subs(AMB_P,[ud1 ud2],[1 0]) + RHSs1;
    Ms12  =  subs(AMB_P,[ud1 ud2],[0 1]) + RHSs1;

     RHSs2 = -subs(AMB_G1,[ud1 ud2],[0 0]); 
     Ms21  =  subs(AMB_G1,[ud1 ud2],[1 0]) + RHSs2;
     Ms22  =  subs(AMB_G1,[ud1 ud2],[0 1]) + RHSs2;

     

%%%%%%%%%%%%%%% Jacobian of single_stance %%%%%%%%%%%%%%%
disp(' ');

disp(['M11 = ', char(simplify(Ms11)),';']);
disp(['M21 = ', char(simplify(Ms21)),';']);
disp(['M12 = ', char(simplify(Ms12)),';']);
disp(['M22 = ', char(simplify(Ms22)),';']);
disp(['RHS1 = ', char(simplify(RHSs1)),';']);
disp(['RHS2 = ', char(simplify(RHSs2)),';']);

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% % Heelstrike:[H+ = H-](Single Stance) %  
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% %%%  Heelstrike: H+
% AM_G1 = H_G1p;
% AM_H  = H_Hp;

AM_P = H_Pp;
AM_G1  = H_G1p;

% 
% 
% % %%%% Heelstrike: H-, Transition to Single stance 
     RHShs1 = H_Qn;
     RHShs2 = H_G1n; %sym added later when found that this gives double value

     Mhs11  =  subs(AM_P,[u1 u2],[1 0]);
     Mhs12  =  subs(AM_P,[u1 u2],[0 1]);

     Mhs21  =  subs(AM_G1,[u1 u2],[1 0]);
     Mhs22  =  subs(AM_G1,[u1 u2],[0 1]);

% 
%      
%      M = [Mhs11 Mhs13; Mhs31 Mhs33];
%      RHS = [RHShs1; RHShs3];
%     
%      xx = M\RHS;
%      
% %%%%%%%%%%%%%% Jacobian of heelstrike %%%%%%%%%%%%%%%
% disp(' ');
% 
% disp(['q1 = ',char(-r1),';']);
% disp(['q2 = ',char(-r2),';']);
% disp(['u1 = ',char(simple(xx(1,1))),';']);
% disp(['u2 = ',char(simple(xx(2,1))),';']);
% 
disp(' ');
disp(['M11 = ', char(simplify(Mhs11)),';']);
disp(['M21 = ', char(simplify(Mhs21)),';']);
disp(['M12 = ', char(simplify(Mhs12)),';']);
disp(['M22 = ', char(simplify(Mhs22)),';']);
disp(['RHS1 = ', char(simplify(RHShs1)),';']);
disp(['RHS2 = ', char(simplify(RHShs2)),';']);
% 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Reaction force on the stance leg in ground frame XYZ 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
F_xyz = m1*a_G1 + m2*a_G2;
F_XYZ = R_XYZ_xyz*[F_xyz(1,1); F_xyz(1,2)];
FX = F_XYZ(1,1);
FY = F_XYZ(2,1)+(m1+m2)*g;
disp(' ');
disp(['FX = ',char(simplify(FX)),';']);
disp(['FY = ',char(simplify(FY)),';']);
