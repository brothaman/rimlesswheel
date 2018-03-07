%% Robert Brothers BSME
% this program will generate the limit cycle for a single over simplified rimless wheel
% using ODE45
t0 = 0;
tf = 10;
g = -9.81;
L = 1;
x_dot = @(t,x) [x(2); g*L*sin(x(1))];
x0 = [15*pi/180 0];

tspan = [t0 tf];
[T,Y] = ode45(x_dot, tspan, x0);

fig1 = figure;
plot(T, Y, "b-o")

fig2 = figure;
plot(Y(:,1), Y(:,2))
title("Limit Cycle")
xlabel("theta")
ylabel("theta_dot")
