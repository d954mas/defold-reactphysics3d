# Ray
This table represents a 3D ray represented by two points.

The ray goes from point1 to point1 + maxFraction * (point2 - point1).

The points are specified in world-space coordinates.

---

* `point1` (vector3) First point of the ray (origin) in world-space.
* `point2` (vector3) 	Second point of the ray in world-space.
* `maxFraction` (number|nil) Maximum fraction value.

```lua
local ray = {
    point1 = vmath.vector3(0,0,0),
    point2 = vmath.vector3(1,0,0),
    maxFraction = 1 --[0-1] if nil use 1.
}
```