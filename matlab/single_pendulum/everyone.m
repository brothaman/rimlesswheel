%% calculate every cost for every possible state transition
% this will require a high number of calculations but should provide the most optimal 
% * calculate the number of operations
% * calculate initial computation time
% * calculate runtime after computation
% * calculate lookup time
clear 
close all

round2 = @(val, basis, decimal_places) ...
	round(...
		round(val/basis*1*10^decimal_places)...
			/(1*10^decimal_places)*round(basis,decimal_places),decimal_places);

%Ntheta = 1e4; thetamax = 0; thetamin =2*pi;
%Nthetadot = 1e3; thetadotmin = -6; thetadotmax = 6;
%Ntau = 1e2; taumin = -10; taumax = 10;
Ntheta = 10; thetamax = 0; thetamin =2*pi;
Nthetadot = 10; thetadotmin = -6; thetadotmax = 6;
Ntau = 10; taumin = -10; taumax = 10;

%fun = @(val_range, N) (val_range(1):range(val_range)/N:val_range(2));
thetas = linspace(thetamin,thetamax,Ntheta);
thetadots = linspace(thetadotmin,thetadotmax,Nthetadot);
taus = linspace(taumin,taumax,Ntau);
J = zeros(Ntheta,Nthetadot,Ntau);

for i = 1:Ntheta
	for j = 1:Nthetadot
		for k = 1:Ntau
			X = [
				thetas(i)
				thetadots(j)
			];
			J(i,j,k) = cost(X,taus(k));
		end
	end
end
