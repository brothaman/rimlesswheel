function X = generate_new_state( Xin, Xd, torque, time, anglerange, speedrange, torquerange)
global NODES
% use xnplus 1 to generate a new state and store it in to the global
% variable NODES
% if X is the same then dont save the state/input signal combo
%% ------------------ discretizations --------------------------- %%
angleresolution = 0.01;
speedresolution = 0.01;
torqueresolution = 1;
nangles = 100;
nspeeds = 200;
ntorques =20;
[Xin(1), mstate] = map(Xin(1),anglerange, nangles);
[Xin(2), nstate] = map(Xin(2),speedrange, nspeeds);
torque = map(torque,torquerange, ntorques);
%% ------------------ discretizations --------------------------- %%

Xin = round(Xin, 2);
torque = round(torque, 1);
[t,X] = xnplusone(0,Xin,torque,'StepSize',time,...
        'AngleResolution', angleresolution,...
        'SpeedResolution', speedresolution,...
        'TorqueResolution', torqueresolution);
[X(1), mnextstate] = map(X(1), anglerange, nangles);
[X(2), nnextstate] = map(X(2), speedrange, nspeeds);
X = round(X,2);
if max( Xin ~= X)
J = cost(Xd,Xin,X,torque);
    if isempty(NODES{mstate,nstate}.state), NODES{mstate,nstate}.state = Xin; end
    NODES{mstate,nstate}.connections{end+1} = [ mnextstate, nnextstate, torque, J];
end
end