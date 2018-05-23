
% -------------------------------------
% differentiation with respect to theta
% -------------------------------------
dldtheta1 = diff(L, theta_1);
dldthetadot1 = diff(L, thetadot_1);
ddtdldthetadot1 = ddt(dldthetadot1, theta);
EOM1 = simplify(dldtheta1 - ddtdldthetadot1);
EOM1 = collect(EOM1, [thetaddot_1, thetaddot_2, sin(theta_1), sin(theta_2)]);

% seperation of variables to produce the form M*xddot + D = 0
MM = subs(EOM1,[thetadot_2, g],[0,0]);
M11 = subs(MM, [thetaddot_1,thetaddot_2],[1,0]);
M12 = subs(MM, [thetaddot_1,thetaddot_2],[0,1]);
D1 = EOM1 - MM;

% ---------------------------------------
% differentiation with respect to theta 2
% ---------------------------------------
dldtheta2 = diff(L, theta_2);
dldthetadot2 = diff(L, thetadot_2);
ddtdldthetadot2 = ddt(dldthetadot2, theta);
EOM2 = simplify(dldtheta2 - ddtdldthetadot2);
EOM2 = collect(EOM2, [thetaddot_1, thetaddot_2, sin(theta_1), sin(theta_2)]);

% seperation of variables from the second equation
MM = subs(EOM2,[thetadot_1,g],[0,0]);
M21 = subs(MM, [thetaddot_1,thetaddot_2],[1,0]);
M22 = subs(MM, [thetaddot_1,thetaddot_2],[0,1]);
D2 = EOM2 - MM;

%% set up the state space equation
syms x1 x2 x3 x4 
M1 = 1;
M2 = 1;
G = -9.81; % in the +x direction
L1 = 1;
L2 = 1;
symbolic_variables = [m1,m2,l1,l2,g,theta_1,thetadot_1,theta_2,thetadot_2];
physical_variables = [M1,M2,L1,L2,G,     x1,        x2,     x3,        x4];
% convert the equation of motion over to function handles for faster computation
M11 = subs(M11,symbolic_variables, physical_variables);
M12 = subs(M12,symbolic_variables, physical_variables);
M21 = subs(M21,symbolic_variables, physical_variables);
M22 = subs(M22,symbolic_variables, physical_variables);
D1 = subs(D1,symbolic_variables, physical_variables);
D2 = subs(D2,symbolic_variables, physical_variables);
M11 = str2func(strcat('@(x1,x2,x3,x4)', char(M11)));
M21 = str2func(strcat('@(x1,x2,x3,x4)', char(M21)));
M12 = str2func(strcat('@(x1,x2,x3,x4)', char(M12)));
M22 = str2func(strcat('@(x1,x2,x3,x4)', char(M22)));
D1 = str2func(strcat('@(x1,x2,x3,x4)', char(D1)));
D2 = str2func(strcat('@(x1,x2,x3,x4)', char(D2)));
M = @(x) [M11(x(1),x(2),x(3),x(4)), M12(x(1),x(2),x(3),x(4)); M21(x(1),x(2),x(3),x(4)), M22(x(1),x(2),x(3),x(4))];
D = @(x) [D1(x(1),x(2),x(3),x(4));D2(x(1),x(2),x(3),x(4))];
model.M = M;
model.D = D;
model.symbolic_variables = symbolic_variables;
model.physical_variables = physical_variables;
model.L1 = L1;
model.L2 = L2;
save('../rimless_wheel/model.mat', 'model')
