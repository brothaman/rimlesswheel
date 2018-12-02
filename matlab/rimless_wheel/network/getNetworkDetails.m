%% Network Details
filename = 'junk/network.mat';

testNetworkConnectivity(filename)

[connectivity, reachable_states, unreachable_states, conns] = testNetworkConnectivity(filename);

reds = 5*(conns ==0);
fig1 = figure('Position',[0 0 800 400]);
hold on
bar(parameters.velocities,conns,'DisplayName','Number of States with Connections to State')
bar(parameters.velocities,reds,'DisplayName','Unreachable States')
title('Network Connectivity','FontSize',18)
ylabel('Number of Connections to the State','FontSize',16)
xlabel('States (Midstatnce Velocities)','FontSize',16)
legend('show')
% saveas(fig1,'../plots/networkDetails.jpeg')