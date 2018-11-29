function data = generate_data(fixed, steps,network,speeds)
	parms = get_parameters(fixed);
	ts = [];

	alphas = [];

	if parms.fixed == 1
		z = zeros(1,4);
		zs = [];
		for i = 1:steps
			if i > ceil(.6*steps)
				parms.control.alpha = getControlSignal(z(end,2),network{2});
			else
				parms.control.alpha = getControlSignal(z(end,2),network{end-10});
			end
			[z,t,~,~,error_flag] = onestep_fixed(z(end,1:2),parms,1);
			alphas = [alphas; parms.control.alpha*ones(size(t))];
			if (error_flag) %%0 no failure, 1 = ground penetration, 2 = ground reaction force < 0 
				warning('simulation failed: change initial condition or torso angle');
			end
			if ~isempty(ts)
				ts = [ts; t+ts(end)];
				zs = [zs; [z(:,1) z(:,2) z(:,3)+zs(end,3) z(:,4)]];
			else
				ts = [ts; t];
				zs = [zs; z];
			end
 		end
	else
		parms.control.kp_q2 = 200;
		parms.control.kp_u2 = parms.control.kp_q2*0.4;
		z = zeros(1,6);
		zs = [];
		for i = 1:steps
			if i > ceil(.6*steps)
	% 			parms.control.alpha = getControlSignal(z(end,2),network{ceil(.1*length(network))});
	% 			parms.control.q2 = getControlSignal(z(end,2),network{10});
				parms.control.alpha = getControlSignal(z(end,2),network{2});
				parms.control.q2 = getControlSignal(z(end,2),network{2});
			else
	% 			parms.control.alpha = getControlSignal(z(end,2),network{ceil(.9*length(network))});
	% 			parms.control.q2 = getControlSignal(z(end,2),network{80});
				parms.control.alpha = getControlSignal(z(end,2),network{end-10});
				parms.control.q2 = getControlSignal(z(end,2),network{end-10});
			end
			[z,t,~,~,error_flag] = onestep_dynamics(z(end,[1 2 5 6]),parms,1);
			alphas = [alphas; parms.control.alpha*ones(size(t))];
			if (error_flag) %%0 no failure, 1 = ground penetration, 2 = ground reaction force < 0 
				warning('simulation failed: change initial condition or torso angle');
			end
			if ~isempty(ts)
				ts = [ts; t+ts(end)];
				zs = [zs; [z(:,1) z(:,2) z(:,3) z(:,4) z(:,5)+zs(end,5) z(:,6)]];
			else
				ts = [ts; t];
				zs = [zs; z];
			end
		end
	end
	data = {ts,zs,alphas,parms};