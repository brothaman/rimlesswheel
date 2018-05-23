function animated_pendulum(points, varagin)
defaults.lims = [2,-2,2,-2];
defaults.pause = 0;
defaults.fig = figure;
defaults.timestep = 1e-3

%% input verification functions
isValidPointArray = @(x) isnumeric(x) && ~mod(size(x,2),2);
isGraphLimit = @(x) isnumeric(x) && length(x) == 4 && any(size(x) == 1); % ensure that the input array has 4 numeric values 
isBool = @(x) x == 1 || x == 0;

p = inputParser;
addRequired(p,'points',isValidPointArray);
addOptional(p, 'GraphDimensions',defaults.lims,isGraphLimit)
addOptional(p, 'Pause', defaults.pause, isBool)
addOptional(p, 'TimeStep', defaults.timestep, isnumeric)
parse(p,points,varagin{:});

%% gather the figure
sz = size(points);
n = sz(2)/2;
len = sz(1);

% get axis and plot window
axis(gca,'equal');
axis(defaults.lims);

% throw for matrices that do not contain pairs of coordinates
%if n ~= int16(n)
%	exception1 = MException('MyComponent:UnevenInput',...
%	'The input matrix of size [%i x %i]''s last dimesion is not even', sz(1),sz(2));
%	throw(exception1)
%end

for i = 1:len
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
	end
	pause(defaults.timestep)
	% delete the last points
	if(i<len)
		for j = 1:n
			delete(PP(j));
		end
	end
end
end
