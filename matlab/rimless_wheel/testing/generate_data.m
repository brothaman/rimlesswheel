function data = generate_data(fixed,network,desired_states)
steps = sum(desired_states(:,2));
	for i = 1:length(desired_states(:,2))
		desired_states(i,2) = sum(desired_states(1:i,2));
	end
	parms = get_parameters(fixed);
	ts = [];

	alphas = [];

% 	desired_states = [100 50 100 50 10 100];
	j=1;
	val = steps/length(desired_states);
	iterp = 1;
	if parms.fixed == 1
		poincare_map_data = zeros(steps,2);
		z = zeros(1,4);
		zs = [];
		desired_state = desired_states(1,1)
		for i = 1:steps
			if desired_states(j,2) < i
				j = j+1;
				desired_state = desired_states(j,1)
			end
			parms.control.alpha = getControlSignal(z(end,2),network{desired_state});
			parms.control.alpha
% 			if i > ceil(weight*steps)
% 				parms.control.alpha = getControlSignal(z(desire,2),network{2});
% 			else
% 				parms.control.alpha = getControlSignal(z(end,2),network{end-10});
% 			end
			[z,t,~,~,error_flag] = onestep_fixed(z(end,1:2),parms,1);
			poincare_map_data(iterp,:) = z(end,[1 2]);
			iterp = iterp+1;
			alphas = [alphas; parms.control.alpha*ones(size(t))];
			if (error_flag) %%0 no failure, 1 = ground penetration, 2 = ground reaction force < 0 
				warning('simulation failed: change initial condition or torso angle');
			end
			if ~isempty(ts)
				ts = [ts; t+ts(end)];
				zs = [zs; [z(:,1) z(:,2) z(:,3)+zs(end,3)-z(1,3) z(:,4)]];
			else
				ts = [ts; t];
				zs = [zs; z];
			end
 		end
	else
		poincare_map_data = zeros(steps,4);
		parms.control.kp_q2 = 200;
		parms.control.kp_u2 = parms.control.kp_q2*0.4;
		z = zeros(1,6);
		zs = [];
		desired_state = desired_states(1,1);
		for i = 1:steps
			if desired_states(j,2) < i
				desired_state = desired_states(j,1);
				j = j+1;
			end
			parms.control.alpha = getControlSignal(z(end,2),network{desired_state});
			parms.control.q2 = getControlSignal(z(end,2),network{desired_state});
% 			if i > ceil(weight*steps)
% 				parms.control.alpha = getControlSignal(z(73,2),network{2});
% 				parms.control.q2 = getControlSignal(z(73,2),network{2});
% 			else
% 				parms.control.alpha = getControlSignal(z(end,2),network{end-10});
% 				parms.control.q2 = getControlSignal(z(end,2),network{end-10});
% 			end
			[z,t,~,~,error_flag] = onestep_dynamics(z(end,[1 2 5 6]),parms,1);
			poincare_map_data(iterp,:) = z(end,[1 2 5 6]);
			iterp = iterp+1;
			alphas = [alphas; parms.control.alpha*ones(size(t))];
			if (error_flag) %%0 no failure, 1 = ground penetration, 2 = ground reaction force < 0 
				warning('simulation failed: change initial condition or torso angle');
			end
			
			%[t_unique,index] = unique(t,'first');
			t_all = t;
			z_all = z;
			
			z = []; t = [];
			[m,n] = size(z_all);
			t = linspace(t_all(1),t_all(end),30);
			for ii=1:n
				z(:,ii) = interp1(t_all,z_all(:,ii),t);
			end

			
			
			if ~isempty(ts)
				ts = [ts; t+ts(end)];
				zs = [zs; [z(:,1) z(:,2) z(:,3) z(:,4) z(:,5)+zs(end,5)-z(1,5) z(:,6)]];
			else
				ts = [ts; t];
				zs = [zs; z];
			end
		end
	end
	data = {ts,zs,alphas,parms,poincare_map_data};