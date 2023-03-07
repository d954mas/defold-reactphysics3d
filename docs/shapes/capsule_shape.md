# CapsuleShape
CapsuleShape extends [ConvexShape](convex_shape.md)

This class represents a capsule collision shape that is defined around the Y axis.

A capsule shape can be seen as the convex hull of two spheres. The capsule shape is defined by its radius (radius of the two spheres of the capsule) and its height (distance between the centers of the two spheres). This collision shape does not have an explicit object margin distance. The margin is implicitly the radius and height of the shape. Therefore, no need to specify an object margin for a capsule shape.

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/capsule_shape_classes.png">


## Create
```lua
rp3d.createCapsuleShape(radius, height)
```


## Methods

* CapsuleShape:[getRadius](#capsuleshapegetradius)() number
* CapsuleShape:[setRadius](#capsuleshapesetradiusradius)(radius)
* CapsuleShape:[getHeight](#capsuleshapegetheight)() number
* CapsuleShape:[setHeight](#capsuleshapesetheightheight)(height)

---
### CapsuleShape:getRadius()
Return the radius of the capsule.

**RETURN**
* (number)

---
### CapsuleShape:setRadius(radius)
Set the radius of the capsule.

Note that you might want to recompute the inertia tensor and center of mass of the body after changing the radius of the collision shape.

**PARAMETERS**
* `radius` (number)
### CapsuleShape:getHeight()
Return the height of the capsule.

**RETURN**
* (number)

---
### CapsuleShape:setHeight(height)
Return the height of the capsule.

Note that you might want to recompute the inertia tensor and center of mass of the body after changing the radius of the collision shape.

**PARAMETERS**
* `height` (number)