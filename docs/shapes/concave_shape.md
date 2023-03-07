# ConcaveShape
ConcaveShape extends [CollisionShape](collision_shape.md)

This abstract class represents a concave collision shape associated with a body that is used during the narrow-phase collision detection.


Subclasses:
1. [ConcaveMeshShape](concave_mesh_shape.md)
2. [HeightFieldShape](heightfield_shape.md)


<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/concave_shape_classes.png">


## Create
Abstract class.You can't create ConcaveShape class.

## Methods

* ConcaveShape:[getRaycastTestType](#concaveshapegetraycasttesttype)()  [rp3d.TriangleRaycastSide](../rp3d.md#rp3dtriangleraycastside)
* ConcaveShape:[setRaycastTestType](#concaveshapesetraycasttesttypetesttype)(testType)
* ConcaveShape:[getScale](#concaveshapegetscale)() vector3
* ConcaveShape:[setScale](#concaveshapesetscalescale)(scale)

---
### ConcaveShape:getRaycastTestType()
Return the raycast test type (FRONT, BACK, FRONT_AND_BACK)

**RETURN**
* ([rp3d.TriangleRaycastSide](../rp3d.md#rp3dtriangleraycastside)) FRONT, BACK, FRONT_AND_BACK

---
### ConcaveShape:setRaycastTestType(testType)
Set the raycast test type (FRONT, BACK, FRONT_AND_BACK)

**PARAMETERS**
* `testType` ([rp3d.TriangleRaycastSide](../rp3d.md#rp3dtriangleraycastside)) FRONT, BACK, FRONT_AND_BACK

---
### ConcaveShape:getScale()
Return the scale.

**RETURN**
* (vector3)

---
### ConcaveShape:setScale(scale)
Set the scale.

Note that you might want to recompute the inertia tensor and center of mass of the body after changing the scale of a collision shape.

**PARAMETERS**
* `scale` (vector3)
