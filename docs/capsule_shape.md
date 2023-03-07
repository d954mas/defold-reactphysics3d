# CapsuleShape
CapsuleShape extends [ConvexShape](convex_shape.md)

This class represents a capsule collision shape that is defined around the Y axis.

A capsule shape can be seen as the convex hull of two spheres. The capsule shape is defined by its radius (radius of the two spheres of the capsule) and its height (distance between the centers of the two spheres). This collision shape does not have an explicit object margin distance. The margin is implicitly the radius and height of the shape. Therefore, no need to specify an object margin for a capsule shape.


## Create
rp3d.createCapsuleShape(radius, height)

## Methods

* CapsuleShape:[getRadius](#capsuleshapegetradius)() number
* CapsuleShape:[setRadius](#capsuleshapesetradius)(radius)
* CapsuleShape:[getHeight](#capsuleshapegetheight)() number
* CapsuleShape:[setHeight](#capsuleshapesetheight)(height)
