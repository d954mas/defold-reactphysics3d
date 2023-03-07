# ConvexShape

ConvexShape extends [CollisionShape](collision_shape.md)

This abstract class represents a convex collision shape associated with a body that is used during the narrow-phase
collision detection.

Subclasses:
1. [CapsuleShape](capsule_shape.md)
2. [ConvexPolyhedronShape](convex_polyhedron_shape.md)
3. [SphereShape](sphere_shape.md)


<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/convex_shape_classes.png">

## Create

Abstract class.You can't create ConvexShape class.

## Methods

* ConvexShape:[getMargin](#convexshapegetmargin)() number

---

### ConvexShape:getMargin()

Return the current object margin.

**RETURN**

* (number) - The margin (in meters) around the collision shape
