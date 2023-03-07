# Transform
This table represents a position and an orientation in 3D.

It can also be seen as representing a translation and a rotation.

---

* `position` (vector3) Origin of the transform.
* `quat` (quaternion) 	The orientation quaternion.

```lua
local transform = {
    position = vmath.vector3(),
    quat = vmath.quat(),
}
```