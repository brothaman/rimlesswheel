%% ===================================================================
function animater_dynamics(t_all,z_all,parms,steps,fps,farview,myPathVid)
%===================================================================
% stuff i added %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
h = gcf;
% myPathVid = '../plots/dynamics_accurate.mp4';
vidObj = VideoWriter(myPathVid);
vidObj.Quality = 100;
open(vidObj);
movegui(h, 'onscreen');
% rect = get(h,'Position'); 
% rect(1:2) = [0 0];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (nargin<6)
    farview = 0;
end

l = parms.l; c = parms.c;

% %%%% First, get the unique values of states %%%%
% [t_unique,index] = unique(t_all,'first');
% 
% z_unique = [];
% for i = 1:length(index)
%    z_unique = [z_unique; z_all(index(i),1), z_all(index(i),3),  z_all(index(i),5),  z_all(index(i),6)];
% end
% t_unique = t_all;
% z_unique = z_all;

%%%% Second, interpolate linearly using fps %%%%%
% [m,n] = size(z_all);
% t = linspace(0,t_all(end),fps*steps);
% for i=1:n
%     z(:,i) = interp1(t_all,z_all(:,i),t);
% end

%%%% Lastly, animate the results
clf
   
z_unique = [z_all(:,1) z_all(:,3) z_all(:,5) z_all(:,6)];

z = z_unique;
dth = 2*pi/parms.n; %spokes spacing in radians. n = number of spokes.
[m,n]=size(z);

min_xh = min(z(:,3));
max_xh = max(z(:,3));
dist_travelled = max_xh - min_xh;

camera_rate = dist_travelled/m;

window_ymin = -0.1; window_ymax = 2*max([parms.l,parms.c])+0.1;
if (farview == 1)
    window_xmin = min_xh-l; window_xmax = max_xh+l; 
else
%     window_xmin = -1.0; window_xmax = 2.0;
      window_xmin = -4*l; window_xmax = 4*l;
end
% axis('equal')
axis([window_xmin window_xmax window_ymin window_ymax])
% axis off
set(gcf,'Color',[1,1,1])

%%% creat object for center of rimles wheel %%%%%
hingepic=line('xdata',0,'ydata',0, 'marker','.','markersize',20, ...
           'visible','on','color','black');
torsopic=line('xdata',0,'ydata',0, 'marker','.','markersize',40, ...
          'visible','on','color','red');

%%%% create object for spokes %%%%
barref = [0 0; 0 1]; %%% bar along positive y-axis
      
for p = 1:parms.n
    barpic(p)=line('xdata',barref(1,:),'ydata',barref(2,:),'linewidth', 2, 'visible','on','color','blue');
end

barpic(parms.n+1)=line('xdata',barref(1,:),'ydata',barref(2,:),'linewidth', 4, 'visible','on','color','red');

    
%%%% create ramp %%%%
rampref=[min_xh-10*l max_xh+10*l; 0 0];

ramppic=line('xdata',rampref(1,:),'ydata',rampref(2,:), ...
            'linewidth', 1,'color','black');
     

moviescaling = 1;                      % slow down factor
delay =floor(moviescaling); %delay per frame in .001 secs


for i=1:m
   
   for j=1:100, log(1:delay*17); end %delay for graphics. 
	                                 %the number in this expression
									 %is machine dependent.
									 %The LOG is just something
									 %to keep the machine busy.

   q1 = z(i,1);
   q2 = z(i,2);
   xh = z(i,3); yh = z(i,4);  
  
   if (farview ~= 1)
       window_xmin = window_xmin + camera_rate;
       window_xmax = window_xmax + camera_rate;
       axis('equal')
       axis([window_xmin window_xmax window_ymin window_ymax])
   end

   hinge=[xh; yh];    

        for p = 1:parms.n
            A = q1-(p-1)*dth;
            bar(:,:,p) = [hinge, hinge] + l*R(A)*barref;
        end
        A = q2 - pi; %angle made by vertical and torso
        bar(:,:,parms.n+1) = [hinge,hinge] + c*R(A)*barref;
        

    set(hingepic,'xdata',hinge(1),'ydata',hinge(2));
    
    for p=1:parms.n+1
        set(barpic(p),'xdata',bar(1,:,p),'ydata',bar(2,:,p));
    end
    set(torsopic,'xdata',bar(1,2,parms.n+1),'ydata',bar(2,2,parms.n+1));
	
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	%%%%%%%%%%%%%%%%%%% attempting annotation%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 	annotation('textbox',...
%     [0.60 0.55 0.285 0.125],...
%     'String',{['Distance = ', num2str(z_unique(i,3),3)],['Velocity =' num2str(z_unique(i,4),3)]},...
%     'FontSize',18,...
%     'FontName','Arial',...
%     'LineStyle','-',...
%     'EdgeColor',[0 0 0],...
%     'LineWidth',3,...
%     'BackgroundColor',[0.4  0.4 0.4],...
%     'Color',[0 0 0]);
	
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    drawnow  
	
	%%%%%%%%%%%%%%%%%%%%%% more stuff i added %%%%%%%%%%%%%%%%%%%%%%%%%%%%
	writeVideo(vidObj,getframe(gcf));
	%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
end
close(vidObj);
%===================================================================
function rotation = R(A)
%===================================================================
rotation = [cos(A) -sin(A); sin(A) cos(A)];

