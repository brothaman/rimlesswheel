function network = generate_cost_network(...
    network, torque_range,...
    body_angle_range, velocity_range,...
    body_angle_rate_range, parms, N, M, P)
% for each of the possible torques body_angles and velocities calculate and
% store a cost
for i = 1:N
    for j = 1:M
        for k = 1:P
            for T = torque_range
                parms.control.T2 = T;
                q1 = 0;%angle should always be zero
                u1 = velocity_range(j);%mid-stance velocity 
                q2 = body_angle_range(i); %parms.control.q2;
                u2 = body_angle_rate_range(k);
                z0 = [q1 u1 q2 u2];% [angle rate];
                [z,t,thetadotmid,Avg_Velocity,error_flag] = ...
                    onestep(z0, parms, 1);
                network = memoize(network,z,t,thetadotmid,Avg_Velocity,error_flag);
            end
        end
    end
end

end

function network = memoize(...
    network,z,t,thetadotmid,Avg_Velocity,error_flag)

end

function J = cost(z,zd,t)
% calculate the cost of the state transition
err = zd - z;

% scaling constants for cost 20% from time 80% from state
qerr = 1;
qt = 1;

% use the square of the costs
state_cost = err*qerr*err';
qt = t*qt*t;
J = state_cost + qt;
end