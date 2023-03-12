# ConvexMeshShape
ConvexMeshShape extends [ConvexPolyhedronShape](convex_polyhedron_shape.md)

This class represents a convex mesh shape.

In order to create a convex mesh shape, you need to indicate the local-space position of the mesh vertices. The center of mass of the shape will be at the origin of the local-space geometry that you use to create the mesh.


<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/collision_shape_classes.png">


## Create
```lua
TODO
```

## Methods

* ConvexMeshShape:[getScale](#convexmeshshapegetscale)() vector3
* ConvexMeshShape:[setScale](#convexmeshshapesetscalescale)(scale)

---
### ConvexMeshShape:getScale()
Return the scale. 

**RETURN**
* (vector3)

---
### ConvexMeshShape:setScale(scale)
Set the scale.

Note that you might want to recompute the inertia tensor and center of mass of the body after changing the scale of a collision shape.

**PARAMETERS**
* `halfExtents` (vector3)

