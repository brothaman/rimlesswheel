%% Visualize the cost network
close all
addpath ../lib
load ../lib/weak_cost_network.mat
pendulum_type = 'Weak Pendulum';
path = 'images/weak_pend/figures/';
if ~exist(path,'dir')
    mkdir(path)
end
statenvalues = get_state_n_value(network);
fig = figure;
fig1 = figure;
fig2 = figure;
fig3 = figure;
fig4 = figure;
rmean = 200;
k = 10;
kspeeds = k;
kcost = 1/7;
N = 200;%sum(any(~cellfun('isempty',connections),2));
flag = 1;
clear x y z

% animate the pendulum and generate the q_actual
if flag
    [qactual,txs,torques] = animate_pendulum(fig, network, N, all_angles, all_speeds,[ pendulum_type ' Pendulum [0,0] to [\pi,0]'],path,0);
end

% plot the torque and state
if flag
    plot_state_parameters(fig4,txs, torques,[pendulum_type ' System Response'])
    saveas(fig1, [path pendulum_type ' Response Plot.pdf'],'pdf'); %pause;
end

% plot network on a disk
[x,y] = get_CN_disk_data(rmean,k,all_angles,all_speeds);
plot_low_density_scatter(fig1,x,y,[4,20]);
saveas(fig1, [path pendulum_type ' cost network scatter on flat disk-isometric.pdf'],'pdf'); %pause;
clf(fig1)

plot_low_density_surf(fig1,x,y,[4,20]);
saveas(fig1, [path pendulum_type ' cost network surface on flat disk-isometric.pdf'],'pdf'); %pause;
clf(fig1)


z = get_disk_cost_height(kcost,all_angles, all_speeds, statenvalues);
if flag
    [xx,yy,zz] = get_actual_data_for_disk(rmean,qactual,statenvalues,k,kcost);
    fig1 = visualize_cost_network_on_disk(fig1,x,y,z,xx,yy,zz,['Discoidal Representation of ' pendulum_type ' Pendulum''s Cost Network']);
else
    fig1 = visualize_cost_network_on_disk(fig1,x,y,z,['Discoidal Representation of ' pendulum_type ' Pendulum''s Cost Network']);
end
view(0, 45)
saveas(fig1, [path pendulum_type ' cost network on disk-isometric.jpg'],'jpeg')

% plot the network on a cylinder
[x,y,z] = get_CN_cylinder_data(rmean,all_angles,all_speeds,statenvalues);
if flag
    [xx,yy,zz] = get_actual_data_for_cylinder(rmean,qactual,statenvalues);
    fig2 = visualize_cost_network_on_cylinder(fig2,x,y,z,xx,yy,zz,['Cylindrical Representation of the ' pendulum_type ' Pendulum''s Cost Network']);
else
    fig2 = visualize_cost_network_on_cylinder(fig2,x,y,z,['Cylindrical Representation of the ' pendulum_type ' Pendulum''s Cost Network']);
end
shading interp
saveas(fig1, [path pendulum_type ' cost network on cylinder-isometric.jpg'],'jpeg')
[az,el] = view;

% rotate the cyclinder's plot
az = 180-90; el = 15;
rotx = 180/pi*(qactual(1:end-1,1) - qactual(2:end,1))';
roty = 180/pi*(atan(qactual(2:end,2))/6)';
if flag
    rotating_the_cylindrical_cost_network(fig3,x,y,z,'Cylindrical Representation of Cost Network',1,[az,15-5],rotx,roty,path,xx,yy,zz)
end
%% functions
function [val, n] = nearest2(val,arr)                                                                                                                                                                       
vec = abs(arr - val);                                                                                                                                                                                       
[val,n] = min(vec);                                                                                                                                                                                         
val = arr(val == vec);                                                                                                                                                                                      
end

function [torque] = get_control_signal(network, n,m)
    torque = network{n,m}.connections{network{n,m}.optimal_policy}(3);
end

function state_value = get_state_n_value(network)
    [n,m] = size(network);
    for i = 1:n
        for j = 1:m
            if isempty(network{i,j}.optimal_value) || isnan(network{i,j}.optimal_value)
                state_value((i-1)*m + j,:) = [network{i,j}.state nan];
            else
                state_value((i-1)*m + j,:) = [network{i,j}.state network{i,j}.optimal_value];
            end
        end
    end
end

function J = get_value_at_state(state,network)
    J = network(sum(state - network(:,1:2),2) == 0,3);
    if isempty(J)
        disp('here')
    end
end

function plot_circle(fig, radius,center,linename)
    figure(fig);
    N = ceil(pi*2*radius/.1);
    theta = 0:2*pi/ceil(pi*2*radius/.1):2*pi;
    x = center(1) + radius*cos(theta');
    y = center(2) + radius*sin(theta');
    plot(x,y,'LineWidth',5, 'DisplayName',linename)
end

%% Functions for Plotting Cylinder
function [x,y,z] = get_CN_cylinder_data(rmean,all_angles,all_speeds,statenvalues)
    x = zeros(length(all_angles),length(all_speeds));
    y = zeros(length(all_angles),length(all_speeds));
    for i = 1:length(all_angles)
        for j = 1:length(all_speeds)
            x(i,j) = (rmean + get_value_at_state([all_angles(i) all_speeds(j)], statenvalues)) * cos(all_angles(i));
            y(i,j) = (rmean + get_value_at_state([all_angles(i) all_speeds(j)], statenvalues)) * sin(all_angles(i));
        end
    end
    z = ones(size(x)).*all_speeds;
end

function [x,y,z] = get_actual_data_for_cylinder(rmean,qactual,statenvalues)
    ractual = zeros(size(qactual(:,1)));
    for i = 1: length(qactual(:,1))
        ractual(i) = (rmean + get_value_at_state(qactual(i,:), statenvalues))+100;
    end
    x = ractual.*cos(qactual(:,1));
    y = ractual.*sin(qactual(:,1));
    z = qactual(:,2);
end

function fig = visualize_cost_network_on_cylinder(fig,x,y,z,varargin)
    figure(fig)
    plot_every_thing = false;
    if length(varargin) ~= 4
        disp('no data for actual plot given or wrong size')
        titl = varargin{1};
    else
        [xx,yy,zz,titl] = deal(varargin{:});
        plot_every_thing = true;
    end
    
    C = x.^2 +y.^2;
    surf(x,y,z,C,'DisplayName','Cost Network');
    if plot_every_thing
        hold on
        plot3(xx,yy,zz,'k','LineWidth',10,'DisplayName','Path Traveled');
        hold off
    end
    
    title(titl)
    zlabel('Cost to Navigate to the Goal')
    ylabel('y-position of Pendulum - Radius Indicates Cost')
    xlabel('x-position of Pendulum - Radius Indicates Cost')
end

function fig = rotating_the_cylindrical_cost_network(fig,x,y,z,titl,flag,desc,rotx,roty,path,varargin)
    figure(fig)
    C = x.^2 +y.^2;
    h = surf(x,y,z,C,'DisplayName','Cost Network');
    if ~isempty(varargin)
        [xx,yy,zz] = deal(varargin{:});
        hold on
        p = plot3(xx,yy,zz,'k','LineWidth',10,'DisplayName','Path Traveled');
        hold off
    end
    title(titl)
    view(desc(1), desc(2));
    shading interp
    j = 1;
    for i = [rotx;roty]
        rotate(h,[0 0 1],i(1))
        view(desc(1), i(2));
        if ~isempty(varargin)
            rotate(p,[0 0 1],i(1))
        end
        if flag
            saveas(fig,[path 'test_plot' int2str(j) '.jpg'],'jpeg')
        end
        pause(0.1)
        j = j + 1;
    end
end
%% Functions for Plotting Disk
function [x,y] = get_CN_disk_data(rmean,k,all_angles,all_speeds)
    r = rmean + k*all_speeds;
    x = cos(all_angles').*r;
    y = sin(all_angles').*r;
end

function z = get_disk_cost_height(k,all_angles, all_speeds, statenvalues)
    z = zeros(length(all_angles), length(all_speeds));
    for i = 1:length(all_angles)
        for j = 1:length(all_speeds)
            z(i,j) = k*get_value_at_state([all_angles(i) all_speeds(j)], statenvalues);
        end
    end
end

function [x,y,z] = get_actual_data_for_disk(rmean,qactual,statenvalues,k,kcost)
    ractual = rmean + k*qactual(:,2);
    x = ractual.*cos(qactual(:,1));
    y = ractual.*sin(qactual(:,1));
    z = zeros(size(x));
    for j = 1:length(qactual(:,1))
        z(j) = kcost*get_value_at_state(qactual(j,:),statenvalues)+.3;
    end
end

function fig = visualize_cost_network_on_disk(fig,x,y,z,varargin)
    figure(fig)
    plot_every_thing = false;
    if length(varargin) ~= 4
        disp('no data for actual plot given or wrong size')
        titl = varargin{1};
    else
        [xx,yy,zz,titl] = deal(varargin{:});
        plot_every_thing = true;
    end
    
    rmax = max(x(1,:));
    rmin = min(x(1,:));
    hold on
    surf(x,y,z, 'DisplayName', 'Cost Network')
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    hold off
    
    shading interp
    if plot_every_thing
        hold on
        plot3(xx,yy,zz,'k','LineWidth',10);
        hold off
    end
%     title('Discoidal Representation of Cost Network')
    title(titl)
    zlabel('Cost to Navigate to the Goal')
    ylabel('y-position of Pendulum')
    xlabel('x-position of Pendulum')
end

function plot_low_density_scatter(fig, x, y, res)
    x = x(1:res(1):end,1:res(2):end);
    y = y(1:res(1):end,1:res(2):end);
    rmax = max(x(1,:));
    rmin = min(x(1,:));
    figure(fig)
    hold on
    scatter(x(:),y(:),'b','DisplayName','States')  
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    legend('show')
    hold off
end

function plot_low_density_surf(fig, x, y, res)
    x = x(1:res(1):end,1:res(2):end);
    y = y(1:res(1):end,1:res(2):end);
    rmax = max(x(1,:));
    rmin = min(x(1,:));
    figure(fig)
    hold on
    surf(x,y,zeros(size(x)),'DisplayName','States')  
    plot_circle(fig, rmax, [0 0],'Max Velocity')
    plot_circle(fig, rmin, [0 0],'Min Velocity')
    legend('show')
    hold off
end

%% Animate the pendulum
function [qactual,txs, torque] = animate_pendulum(fig,network,N,all_angles,all_speeds,titl,path,flag)
    torque = zeros(1,N);
    txs = zeros(N,3);
    phi = -pi/2;
    t = 0.05;
    x = [0 0];
    [x(1),n] = nearest2(x(1),all_angles);
    [x(2),m] = nearest2(x(2),all_speeds);
    xd = [pi 0];
    P = {};
    for i =1:N
        torque(i) = get_control_signal(network,n,m);
        [~,x] = xnplusone(x,torque(i),t);
        [x(1),n] = nearest2(x(1),all_angles);
        [x(2),m] = nearest2(x(2),all_speeds);
        txs(i,:) = [i*t,x];
        P{end+1} = {1*[0 0 cos(x(1)+phi) sin(x(1)+phi)]};
        if round(x,4) == round(xd,4)
            break
        end
    end
    qactual = txs(1:i,2:3);
    figure(fig)
    axis([-2 2 -2 2]);
    phandle = [];
    xlabel('meters')
    ylabel('meters')
    title(titl)
    
    for i = 1:length(P)
        [fig,phandle] = show_pendulum(fig,phandle,P{i});
        if flag
            saveas(fig, [path 'pend' int2str(i) '.jpg'],'jpeg')
        end
        pause(0.03);
    end
end

function plot_state_parameters(fig, txs, torques, titl)
    figure(fig)
    txs = txs(~any(sum(txs,2)==0,2),:);
    torques = torques(~any(sum(txs,2)==0,2));
    
    hold on
    plot(txs(:,1),txs(:,2),'b','LineWidth',4,'DisplayName','Angular Position $\theta$ in rad')
    plot(txs(:,1),ones(size(txs(:,1)))*pi,'--b','DisplayName','Desired Angular Position')
    
    plot(txs(:,1),txs(:,3),'k','LineWidth',3,'DisplayName','Angular Speed $\dot\theta$ in $\frac{rad}{sec}$')
    plot(txs(:,1),zeros(size(txs(:,1))),'--k','DisplayName','Desired Angular Speed')
    
    plot(txs(:,1),torques,'r','LineWidth',3,'DisplayName', 'Torque Input $\tau$ in N*m');
    hold off
    title(titl)
    l = legend('show');
    l.Interpreter = 'latex';
    l.Location = 'southeast';
    
    xlabel('time (t) in seconds')
    ylabel('$Torque-Nm$, Angular Position - rad, Angular Speed - $\frac{rad}{sec}$','Interpreter','latex')
end