function network = generate_cost_network(...
    network, torque_arr,...
    body_angle_arr, velocity_arr,...
    body_angle_rate_arr, parms, N, M, P,xd)
% for each of the possible torques body_angles and velocities calculate and
% store a cost
for i = 1:N
    for j = 1:M
        for k = 1:P
            for T = torque_arr
                parms.control.T2 = T;
                q1 = 0;%angle should always be zero
                u1 = velocity_arr(j);%mid-stance velocity 
                q2 = body_angle_arr(i); %parms.control.q2;
                u2 = body_angle_rate_arr(k);
                z0 = [q1 u1 q2 u2];% [angle rate];
                [z,t,thetadotmid,Avg_Velocity,error_flag] = ...
                    onestep(z0, parms, 1);
                if (z(2:end) == z0(2:end) | error_flag)
                    continue;
                end
                if (    z(2) > max(velocity_arr) || z(2) < min(velocity_arr) ||...
                        z(3) > max(body_angle_arr) || z(3) < min(body_angle_arr) ||...
                        z(4) > max(body_angle_rate_arr) || z(4) < min(body_angle_rate_arr))
                    continue;
                end
                [z(2), n] = nearest2(z(2), velocity_arr);
                [z(3), m] = nearest2(z(3), body_angle_arr); 
                [z(4), p] = nearest2(z(4), body_angle_rate_arr);
                
                network = memoize(...
                    network,z,t,...
                    thetadotmid,Avg_Velocity,error_flag,...
                    i,j,k,T,...
                    body_angle_arr(i), velocity_arr(j),body_angle_rate_arr(k),...
                    n,m,p,xd);
            end
            if ~mod(k,10)
                disp(strcat(int2str(k),' of ',int2str(P),' possible body angle rates'))
            end
        end
        if ~mod(j,10)
            disp(strcat(int2str(j),' of ',int2str(M),' possible body angle rates'))
        end
    end
    if ~mod(i,10)
        disp(strcat(int2str(i),'s of ',int2str(N),' possible velocities'))
    end
end

% now save the memoized network
save('lib/DEBUG_costnetworkv00.mat','network')
end

function network = memoize(...
    network,z,t,...
    thetadotmid,Avg_Velocity,error_flag,...
    i,j,k,T,...
    body_angle, velocity,body_angle_rate,...
    n,m,p,xd)
% now that the new state has been figured out map the out put to
% the nearest increment and calculate the cost. since time is not
% held static time will also be used to generate a cost. 
J = cost(z,xd, T,t);
% if state isnt set set it
if isempty(network{i,j,k}.state)
    network{i,j,k}.state = [body_angle, velocity, body_angle_rate];
end
connection = [n m p T J];
% if the connection doesnt exist make it
if isempty(network{i,j,k}.connections)
    % this is inplace to reduce unneccessary iterations if this
    % werent here there would be upto N unnecessary for loops
    network{i,j,k}.connections{end+1} = connection;
else
    conn = getconnection(network{i,j,k}.connections, connection);
    if conn
        network{i,j,k}.connections{conn} = connection;
    end
end

end

function J = cost(z,zd,a,t)
% the desired state should be one in which the body angle can be anything,
% the speed is stated and the body angle rate should be zero
% calculate the cost of the state transition
% i.e. the body angle and leg angles dont matter. the leg angle should
% always be 0 first off and the body angle i dont care about
err = zd - z;
err = err([2,4]);

% scaling constants for cost 20% from time 80% from state
qerr = ones(2);
qt = 1;
qa = 1;

% use the square of the costs
state_cost = err*qerr*err';
time_cost = t*qt*t;
input_cost = a*qa*a;

global costs count
costs(count,:) = [state_cost, time_cost, input_cost];
count = count + 1;
% sum the cost
J = state_cost + time_cost + input_cost;
end

function [val, n] = nearest2(val,arr)
vec = abs(arr - val);
[val,n] = min(vec);
val = arr(val == vec);
end

function [i] = getconnection(existingconnections, newconnection)
state = [1,2,3];
cost = 5;
for i = 1:length(existingconnections)
    if newconnection(state) == existingconnections{i}(state)
        if newconnection(cost) < existingconnections{i}(cost)
            return;
        end
        i = 0;
        return;
    end
end
i = i+1;    
end
