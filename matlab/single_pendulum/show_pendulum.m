function [fig, phandle] = show_pendulum(fig, phandle, points)
	figure(fig)
	for i = 1:length(points)
		p = points{i}
		clearfig = true;
		if (clearfig)
			for i = 1:length(phandle)
				delete(phandle(i));
			end
		end

		phandle(i) = line(p([1 3]),p([2 4]),'Marker', 'o','MarkerSize',50);
	end
end
