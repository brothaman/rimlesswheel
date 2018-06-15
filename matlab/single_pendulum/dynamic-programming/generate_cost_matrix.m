function generate_cost_matrix()
	Ntheta = 10; thetamax = 0; thetamin =2*pi;
	Nthetadot = 10; thetadotmin = -6; thetadotmax = 6;
	Ntau = 10; taumin = -10; taumax = 10;

	thetas = linspace(thetamin,thetamax,Ntheta);
	thetadots = linspace(thetadotmin,thetadotmax,Nthetadot);
	thetadots = [thetadots(1:Nthetadot/2) 0 thetadots(Nthetadot/2:end)];
	taus = linspace(taumin,taumax,Ntau);
	taus = [taus(1:Ntau/2) 0 taus(Ntau/2:end)];
	J = zeros(Ntheta, length(thetadots), length(taus));

	disp('begin dynamic programming *')
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
	save('lib/dp_cost.mat', J);
end
