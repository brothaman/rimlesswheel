function [] = generate_new_state_n_cost(xd)
global network
% take the given state and control signal input to produce a new state.
% return the new state and the cost associated with the transition. the top
% level should add the path to the model and integrator.
% ------------------------ discretizations ----------------------------- %
N = 100;
M = 20;
% ------------------------ discretizations ----------------------------- %

vmax =  0;
vmin = -3;
amax = 90*pi/180;
amin = 0;
velocities = vmin:(vmax-vmin)/N:vmax;
actions = amin:(amax-amin)/M:amax;
network = cell(size(velocities));
network(:) = {nNode};

% variable necessary for the use of the onestep function
steps = 1;
flag = 0;
parms = get_parms();
% 
for i = 1:N+1
    for j = 1:M+1
        % set the state information
        z0 = [ 0 velocities(i)];
        parms.control.alpha = actions(j);
        [z,t,thetadotmid,Avg_Velocity,error_flag] =...
            onestep(z0,parms,steps, flag);
        [z(2), n,] = map(z(2),[vmin vmax],N);
        
        % now that the new state has been figured out map the out put to
        % the nearest increment and calculate the cost. since time is not
        % held static time will also be used to generate a cost. 
        if (z(2) == z0(2) || error_flag)
            continue;
        end
        J = cost(z(2),z0(2),xd,actions(j),t(end));
        % if state isnt set set it
        if isempty(network{i}.state)
            network{i}.state = velocities(i);
        end
        connection = [n actions(j) J];
        % if the connection doesnt exist make it
        if isempty(network{i}.connections)
            % this is inplace to reduce unneccessary iterations if this
            % werent here there would be upto N unnecessary for loops
            network{i}.connections{end+1} = connection;
        else
            conn = getconnection(network{i}.connections, connection);
            if conn
                network{i}.connections{conn} = connection;
            end
        end
    end
end

d = datestr(datetime('today'));
d = strrep(d,'-','_');
save(strcat('../lib/DEBUGcostnetwork_xd_equal_',num2str(xd),'_',d,'.mat'),...
    'network');
end

function [J] = cost(x,xminus1,xd,a,t)
% accept the time, state and action and treturn the cost for that motion
% set the gain parameters for the action cost and state error cost
deltaX = (xd-x).^2 - (xd - xminus1).^2;

% gain parameters for each type of cost
Qabs = 5;
Qdelta = 0.05;
timescalingfactor = 8;

% calculate the cost
midstance_velocity_cost = (xd-x)*Qabs*(xd-x)';
midstance_velocity_approach_cost = deltaX*Qdelta*abs(deltaX');
temporal_cost = timescalingfactor*t^2;
J = a^2 + midstance_velocity_approach_cost + midstance_velocity_cost +...
    temporal_cost;
if J <0
    return;
end
end

function [t,x] = generate_new_state(z0,parms)
steps = 1;

% Generate a new state with the given state and input signal
[z,t,thetadotmid,Avg_Velocity,error_flag] = onestep(z0,parms,steps);
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