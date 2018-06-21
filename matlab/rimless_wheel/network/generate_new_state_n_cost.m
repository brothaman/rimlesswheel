function [] = generate_new_state_n_cost()
global network
% take the given state and control signal input to produce a new state.
% return the new state and the cost associated with the transition. the top
% level should add the path to the model and integrator.
end

function [J] = cost(x,xminus1,xd,a)
% accept the time, state and action and treturn the cost for that motion
% set the gain parameters for the action cost and state error cost
deltaX = (xd-x).^2 - (xd - xminus1).^2;
Qabs = 1;
Qdelta = 1;
Absolute_positional_error = X*Qabs*X';
Change_in_positional_error = deltaX*Qdelta*abs(deltaX');
J = a^2 + Change_in_positional_error + Absolute_positional_error;
end

function [t,x] = generate_new_state(z0,parms)
steps = 1;

% Generate a new state with the given state and input signal
[z,t,thetadotmid,Avg_Velocity,error_flag] = onestep(z0,parms,steps);
end