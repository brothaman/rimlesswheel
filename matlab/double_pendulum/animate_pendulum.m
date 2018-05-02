function fig = animated_pendulum(points,pz,dims)
fig = figure;
sz = size(points);
n = sz(2)/2;
len = sz(1);

% get axis and plot window
axis(gca,'equal')
axis(dims)

% throw for matrices that do not contain pairs of coordinates
if n ~= int16(n)
	exception1 = MException('MyComponent:UnevenInput',...
	'The input matrix of size [%i x %i]''s last dimesion is not even', sz(1),sz(2));
	throw(exception1)
end

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
	pause(pz)
	% delete the last points
	if(i<len)
		for j = 1:n
			delete(PP(j));
		end
	end
end
end
