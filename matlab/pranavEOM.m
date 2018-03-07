m,M,l,L,g,gamma = deal(0);

A = @(alpha, theta) m*l^2 + M*l*(l-L*cos(theta-alpha));
bss = @(alpha, theta) M*l*L*thetadot^2*sin(alpha-theta) + m*g*l*sin(theta-gamma) + M*g*(l*sin(theta-gamma) - L*sin(alpha-gamma));

x = @(x1,x2) [x2, ]
