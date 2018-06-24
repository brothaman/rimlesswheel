function [] = generate_new_state_n_cost()
global network
% take the given state and control signal input to produce a new state.
% return the new state and the cost associated with the transition. the top
% level should add the path to the model and integrator.

% ------------------------ discretizations ----------------------------- %
N = 100;
M = 100;
% ------------------------ discretizations ----------------------------- %


vmax =  10;
vmin = -10;
amax = 90*pi/180;
amin = 0;
velocities = vmin:(vmax-vmin)/N:vmax;
actions = amin:(amax-amin)/M:amax;
network = cell(size(velocities));
network(:) = {nNode};

% variable necessary for the use of the onestep function
steps = 1;
flag = 1;
parms = get_parms();

% 
for i = 1:N+1
    for j = 1:M+1
        % set the state information
        z0 = [ 0 velocities(i)];
        parms.control.alpha = actions(j);
        [z, t] = onestep(z0,parms,steps, flag);
        [z(2), n] = map(z(2),[vmin vmax],N);
        % now that the new state has been figured out map the out put to
        % the nearest increment and calculate the cost. since time is not
        % held static time will also be used to generate a cost. 
        J = cost(z,z0,actions(j),t);
        network{i}.state = v(i);
        network{i}.connections{end+1} = [n actions(j) J];
        
    end
end
% 
d = datestr(datetime('today'));
d = strrep(d,'-','_');
save(strcat('../lib/costnetwork_',d,'.mat'), network);
end

function [J] = cost(x,xminus1,xd,a,t)
% accept the time, state and action and treturn the cost for that motion
% set the gain parameters for the action cost and state error cost
deltaX = (xd-x).^2 - (xd - xminus1).^2;
Qabs = 1;
Qdelta = 1;
timescalingfactor = 1;
Absolute_positional_error = X*Qabs*X';
Change_in_positional_error = deltaX*Qdelta*abs(deltaX');
temporal_cost = timescalingfactor*t^2;
J = a^2 + Change_in_positional_error + Absolute_positional_error +...
    temporal_cost;
end

function [t,x] = generate_new_state(z0,parms)
steps = 1;

% Generate a new state with the given state and input signal
[z,t,thetadotmid,Avg_Velocity,error_flag] = onestep(z0,parms,steps);
end