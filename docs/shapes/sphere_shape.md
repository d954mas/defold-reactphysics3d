# SphereShape
SphereShape extends [ConvexShape](convex_shape.md)

This class represents a sphere collision shape that is centered at the origin and defined by its radius.

This collision shape does not have an explicit object margin distance. The margin is implicitly the radius of the sphere. Therefore, no need to specify an object margin for a sphere shape.

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/sphere_shape_classes.png">


## Create
```lua
rp3d.createSphereShape(radius)
```
## Methods

* SphereShape:[getRadius](#sphereshapegetradius)() number
* SphereShape:[setRadius](#sphereshapesetradiusradius)(radius)

---
### SphereShape:getRadius()
Return the radius of the sphere.

**RETURN**
* (number)

---
### SphereShape:setRadius(radius)
Set the radius of the sphere.

Note that you might want to recompute the inertia tensor and center of mass of the body after changing the radius of the collision shape.

**PARAMETERS**
* `radius` (number)
