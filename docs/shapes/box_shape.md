# BoxShape

BoxShape extends [ConvexPolyhedronShape](convex_polyhedron_shape.md)

This class represents a 3D box shape.

Those axis are unit length. The three extents are half-widths of the box along the three axis x, y, z local axis. The "
transform" of the corresponding body will give an orientation and a position to the box.

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/box_shape_classes.png">

## Create

```lua
local halfExtents = vmath.vector3(1, 1, 1)
rp3d.createBoxShape(halfExtents)
```

## Methods

* BoxShape:[getHalfExtents](#boxshapegethalfextents)() vector3
* BoxShape:[setHalfExtents](#boxshapesethalfextentshalfextents)(halfExtents)

---

### BoxShape:getHalfExtents()

Return the half-extents of the box.

**RETURN**

* (vector3)

---

### BoxShape:setHalfExtents(halfExtents)

Set the half-extents of the box.

Note that you might want to recompute the inertia tensor and center of mass of the body after changing the size of the
collision shape.

**PARAMETERS**

* `halfExtents` (vector3)

