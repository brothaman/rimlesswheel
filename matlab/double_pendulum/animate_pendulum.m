function animated_pendulum(points, varargin)
defaults.lims = [2,-2,2,-2];
defaults.pause = 0;
defaults.fig = figure;
defaults.timestep = 1e-3;

%% input verification functions
isValidPointArray = @(x) isnumeric(x) && ~mod(size(x,2),2);
% ensure that the input array has 4 numeric values 
isGraphLimit = @(x) isnumeric(x) && length(x) == 4 && any(size(x) == 1); 
isValidTimeStep = @(x) isnumeric(x);

%% parse the input
parser = inputParser;
addRequired(parser,'points',isValidPointArray);
addParameter(parser, 'GraphDimensions',defaults.lims,isGraphLimit)
addParameter(parser, 'Pause', defaults.pause, @(x) (x==1||x==0))
addParameter(parser, 'TimeStep', defaults.timestep, isValidTimeStep)
addParameter(parser, 'Figure', defaults.fig)
parse(parser,points,varargin{:});

%% gather the figure
sz = size(points)
n = sz(2)/2;
len = sz(1);

% get axis and plot window
axis(gca,'equal');
axis(parser.Results.GraphDimensions);

% check if user has paused to start
if parser.Results.Pause
	pause;
end

% animate a line between all points given
for i = 1:len
	i
	p = points(i,:);
	% opportunity for optimization here
	p_ = [];
	
	% generate points for line 
	for j = 1:n
		if(j>1)
			origin = [p((2*(j-1)-1)),p(2*(j-1))];
		else
			origin = [0,0];
		end
		p_ = [ p(2*j-1),p(2*j)];
		P = [origin(:), p_(:)];
		PP(j) = line(P(1,:),P(2,:));
		PPo(j) = line(p_(1), p_(2), 'Marker', 'o','MarkerSize',50);
	end
	pause(parser.Results.TimeStep);
	% delete the last points
	if(i<len)
		for j = 1:n
			delete(PP(j));
			delete(PPo(j));
		end
	end
end
hold off
end
