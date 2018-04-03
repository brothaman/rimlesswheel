%pkg load symbolic

% load the lagrangian
stiffLagrangian

%{
% ALI's Method for calculation of equations of motion
m = [m1;m2];
q = x_xdot (1:2:end,1);
qdot = x_xdot (1:2:end,2);
M = sym(zeros(length(q)))
for i = 1:length(q)
	for j = 1:length(q)
		M(i,j) = diff(diff(K,q(i)),q(j));
	end
end

V = sym(zeros(length(q),1))
for i = 1:length(q)
	for j = 1:length(q)
		for k = 1:length(q)
			V(i) = V(i) + (diff(M(i,j), q(k)) - 1/2*diff(M(j,k),q(i)))*qdot(j)*qdot(k);
		end
	end
end
G = sym(zeros(length(q),1))
for i = 1:length(q)
	for j = 1:length(q)
		G(i) = G(i) - (m(j)*g*diff(P,q(i)));
	end
end

qdoubledot = M\(-V - G)
%}
%% Calculate the equations of motion
% as a function of theta
dLdt = diff(L,theta);
dLdtd = diff(L, thetadot);
ddtdLdtd = ddt(dLdtd, x_xdot);
EOM1 = (dLdt - ddtdLdtd);

% as a function of phi
dLdphi = diff(L,phi);
dLdphidot = diff(L, phidot);
ddtdLdphidot = ddt(dLdphidot, x_xdot);
EOM2 = (dLdphi - ddtdLdphidot);


% solve and reduce the equations of motion
phidoubledot = solve(EOM2,phiddot);
thetadoubledot = solve(EOM1, thetaddot);

% replace phiddot in equation 1 with equation 2 and solve for thetaddot
thetadoubledot_ = (solve(subs(EOM1,phiddot,phidoubledot), thetaddot));
phidoubledot_   = (solve(subs(EOM2,thetaddot, thetadoubledot), phiddot));

if exist('l') == 1
	% as a function of l
	dLdl   = diff(L,l);
	dLdldot = diff(L, ldot);
	ddtdLdldot = ddt(dLdldot, x_xdot);
	EOM3 = simplify(dLdl - ddtdLdldot);
	ldoubledot_     = simplify(solve(EOM3, lddot));
	save('../data/RimlessSprungEOM.mat','*dot_',...
 		'phi','phidot','phiddot',...
		'l','ldot','lddot',...
		'theta','thetadot','thetaddot','L','P','K');
else
	save('../data/RimlessStiffEOM.mat','*dot_',...
 		'phi','phidot','phiddot',...
		'theta','thetadot','thetaddot','L','P','K');
end

