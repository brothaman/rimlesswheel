function [val,n] = map(val, range, split)
vec = range(1):diff(range)/split:range(2);
[s,n] = min(abs(val - vec));
val = vec(s ==  abs(val - vec));
end