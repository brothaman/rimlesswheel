
% -------------------------------------
% differentiation with respect to theta
% -------------------------------------
dldtheta1 = diff(L, theta_1);
dldthetadot1 = diff(L, thetadot_1);
ddtdldthetadot1 = ddt(dldthetadot1, theta);
EOM1 = simplify(dldtheta1 - ddtdldthetadot1)
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
EOM2 = simplify(dldtheta2 - ddtdldthetadot2)
EOM2 = collect(EOM2, [thetaddot_1, thetaddot_2, sin(theta_1), sin(theta_2)]);

% seperation of variables from the second equation
MM = subs(EOM2,[thetadot_1,g],[0,0])
M21 = subs(MM, [thetaddot_1,thetaddot_2],[1,0]);
M22 = subs(MM, [thetaddot_1,thetaddot_2],[0,1]);
D2 = EOM2 - MM

