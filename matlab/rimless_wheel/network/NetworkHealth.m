%% Network Health
close all

[~, ~, ~, conns,cconns,states] = testNetworkConnectivity('../data/beta_1/network.mat');
h = figure
bar(states,cconns)
hold on; bar(states,conns)
plot(states,cconns,'k-','LineWidth',2)
legend('Number of Connections TO','Number of Connections FROM','Location','NorthWest')
title('Network Health','FontSize',18)
xlabel('States','FontSize',14)
ylabel('Connections','FontSize',14)
saveas(h,'../plots/NetworkHealth.pdf','pdf')