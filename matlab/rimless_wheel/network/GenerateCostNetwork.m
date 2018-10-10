%% Generate New Cost Network and Store it in a Data File
% take the given state and control signal input to produce a new state.
% return the new state and the cost associated with the transition. the top
% level should add the path to the model and integrator.

function GenerateCostNetwork(output_filename,parameters)

	network = blank_network(parameters.velocities);
	network = BuildNetwork(network, parameters);

	net = network_state_n_id(network);
	[~,indx] = min(abs(parameters.desired_speed - net(:,2)));
	network{indx}.optimal_value = 0;
	save(output_filename, 'network', 'parameters')
	
end
%% Functions
function network = BuildNetwork(network, parameters)
	N = size(network,2);
	flag = 0;
	steps = 1;
	warning('off','all')
	for i = 1:N
		network{i}.ID = i;
		for action = parameters.actions
			z0 = [ 0 parameters.velocities(i)];
			parameters.control.alpha = action;
			[z,t,~,~,error_flag] =...
				onestep_fixed(z0,parameters,steps);
			z = z(end,1:2);
			t = t(end);
			[z(2), n] = map(z(2),[parameters.vmin parameters.vmax],N);
			
			% if the state hasnt changed or system has exited the 
			% feasibility space then i dont want to record this data
			if (z(2) == z0(2) || error_flag)
				continue;
			end
			
			% otherwise evaluate the new state, action, and time required
			% to determine the transitional cost
			J = cost(z(2),parameters.desired_speed,action,t(end));
			
			% quick check to see if the state ID and value are set
			if isempty(network{i}.state)
				network{i}.state = parameters.velocities(i);
			end
			
			% set 
			connection = [n action J];
			% if the connection doesnt exist make it
			if isempty(network{i}.connections)
				network{i}.connections{end+1} = connection;
			else
				% use the funciton get connection to generate determine if
				% the connection exist. if the connection does exist the
				% function will compare the existing cost if the incoming
				% is lower getconnection will return the index of the state
				% if it is greater it will return 0. if connection doesnt
				% exist it will return an index equal to 1 greater than the
				% length of the connections cell array stored in the
				% network.
				conn = getconnection(network{i}.connections, connection);
				if conn
					network{i}.connections{conn} = connection;
				end
			end
		end
	end
end

function [i] = getconnection(existingconnections, newconnection)
	for i = 1:length(existingconnections)
		if newconnection(1) == existingconnections{i}(1)
			if newconnection(3) < existingconnections{i}(3)
				return;
			end
			i = 0;
			return;
		end
	end
	i = i+1;    
end

function network = blank_network( states)
	network = cell(size(states));
	network(:) = {nNode};
end

function [val, n] = nearest2(val,arr)
	vec = abs(arr - val);
	[val,n] = min(vec);
	val = arr(val == vec);
end

function [J] = cost(x,xd,a,t)
	% accept the time, state and action and treturn the cost for that motion
	% set the gain parameters for the action cost and state error cost
	% deltaX = (xd-x).^2 - (xd - xminus1).^2;

	amax = pi/2;
	xmax = 7.6;
	tmax = 2.81;
	% gain parameters for each type of cost
	velocity_cost_scaling_factor = 8.9/xmax;
	timescalingfactor = 1/tmax;
	input_cost_scaling_factor = 0.1/amax;

	% calculate the cost
	midstance_velocity_cost = (xd-x)*velocity_cost_scaling_factor*(xd-x)';
	temporal_cost = t*timescalingfactor*t;
	input_cost = a*input_cost_scaling_factor*a;

	% add the cost for each type and scale it
	J = 5/12.88*(input_cost + midstance_velocity_cost + temporal_cost);
	if J > 5
		return;
	end
end

function new_network = network_state_n_id(network)
    n = size(network,2);
    new_network = zeros(n,2);
    for i = 1:n
		new_network(i,:) = [i,network{i}.state];
    end
end