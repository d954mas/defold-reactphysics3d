local CLASS = require "libs.middleclass"

local PerlinNoise = CLASS.class("Perlin")

function PerlinNoise:initialize(persistence, frequency, amplitude, octaves, randomseed)
	self.persistence = persistence or 0;
	self.frequency = frequency or 0;
	self.amplitude = amplitude or 0;
	self.octaves = octaves or 0;
	self.randomseed = 0;
	if (randomseed) then
		self.randomseed = 2 + randomseed * randomseed
	end
end

function PerlinNoise:GetHeight(x, y)
	return self.amplitude * self:Total(x, y);
end

function PerlinNoise:Total(i, j)
	--properties of one octave (changing each loop)
	local t = 0.0
	local _amplitude = 1;
	local freq = self.frequency;

	for k = 0, self.octaves - 1 do
		t = t + self:GetValue(j * freq + self.randomseed, i * freq + self.randomseed) * _amplitude;
		_amplitude = _amplitude * self.persistence;
		freq = freq * 2;
	end

	return t;
end
function PerlinNoise:GetValue(x, y)
	local Xint = math.floor(x);
	local Yint = math.floor(y);
	local Xfrac = x - Xint;
	local Yfrac = y - Yint;

	--noise values
	local n01 = self:Noise(Xint - 1, Yint - 1);
	local n02 = self:Noise(Xint + 1, Yint - 1);
	local n03 = self:Noise(Xint - 1, Yint + 1);
	local n04 = self:Noise(Xint + 1, Yint + 1);
	local n05 = self:Noise(Xint - 1, Yint);
	local n06 = self:Noise(Xint + 1, Yint);
	local n07 = self:Noise(Xint, Yint - 1);
	local n08 = self:Noise(Xint, Yint + 1);
	local n09 = self:Noise(Xint, Yint);

	local n12 = self:Noise(Xint + 2, Yint - 1);
	local n14 = self:Noise(Xint + 2, Yint + 1);
	local n16 = self:Noise(Xint + 2, Yint);

	local n23 = self:Noise(Xint - 1, Yint + 2);
	local n24 = self:Noise(Xint + 1, Yint + 2);
	local n28 = self:Noise(Xint, Yint + 2);

	local n34 = self:Noise(Xint + 2, Yint + 2);

	--find the noise values of the four corners
	local x0y0 = 0.0625 * (n01 + n02 + n03 + n04) + 0.125 * (n05 + n06 + n07 + n08) + 0.25 * (n09);
	local x1y0 = 0.0625 * (n07 + n12 + n08 + n14) + 0.125 * (n09 + n16 + n02 + n04) + 0.25 * (n06);
	local x0y1 = 0.0625 * (n05 + n06 + n23 + n24) + 0.125 * (n03 + n04 + n09 + n28) + 0.25 * (n08);
	local x1y1 = 0.0625 * (n09 + n16 + n28 + n34) + 0.125 * (n08 + n14 + n06 + n24) + 0.25 * (n04);

	--interpolate between those values according to the x and y fractions
	local v1 = self:Interpolate(x0y0, x1y0, Xfrac); --interpolate in x direction (y)
	local v2 = self:Interpolate(x0y1, x1y1, Xfrac); --interpolate in x direction (y+1)
	local fin = self:Interpolate(v1, v2, Yfrac);  --interpolate in y direction
	return fin
end

function PerlinNoise:Interpolate(x, y, a)
	local negA = 1.0 - a;
	local negASqr = negA * negA;
	local fac1 = 3.0 * (negASqr) - 2.0 * (negASqr * negA);
	local aSqr = a * a;
	local fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);

	return x * fac1 + y * fac2; --add the weighted factors
end

function PerlinNoise:Noise(x, y)
	local n = x + y * 57;
	local nshift = bit.lshift(n, 13)
	n = bit.bxor(n, nshift)
	local t = (n * (n * n * 15731 + 789221) + 1376312589)
	t = bit.band(t, 0x7fffffff)
	return 1.0 - t * 0.931322574615478515625e-9;-- 1073741824.0) ;
end

return PerlinNoise
