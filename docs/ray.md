# Ray
This table represents a 3D ray represented by two points.

The ray goes from point1 to point1 + maxFraction * (point2 - point1).

The points are specified in world-space coordinates.

```lua
local ray = {
	point1 = vmath.vector3(0,0,0),
	point2 = vmath.vector3(1,0,0),
	maxFraction = 0 --[0-1] if nil use 1.
}
```