# CollisionShape

This abstract class represents the collision shape associated with a body that is used during the narrow-phase collision
detection.

You can create 6 types of shape:

1. [CapsuleShape](capsule_shape.md)
2. [SphereShape](sphere_shape.md)
3. [BoxShape](box_shape.md)
4. [ConvexMeshShape](convex_mesh_shape.md)
5. [ConcaveMeshShape](concave_mesh_shape.md)
6. [HeightFieldShape](heightfield_shape.md)


Subclasses:
1. [ConcaveShape](concave_shape.md)
2. [ConvexShape](convex_shape.md)

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/collision_shape_classes.png">

## Create

Abstract class.You can't create CollisionShape class.

## Methods

* CollisionShape:[getName](#collisionshapegetname)() [rp3d.CollisionShapeName](../rp3d.md#rp3dcollisionshapename)
* CollisionShape:[getType](#collisionshapegettype)() [rp3d.CollisionShapeType](../rp3d.md#rp3dcollisionshapetype)
* CollisionShape:[isConvex](#collisionshapeisconvex)() bool
* CollisionShape:[isPolyhedron](#collisionshapeispolyhedron)() bool
* CollisionShape:[getLocalBounds](#collisionshapegetlocalbounds)() vector3 vector3
* CollisionShape:[getId](#collisionshapegetid)() number
* CollisionShape:[getLocalInertiaTensor](#collisionshapegetlocalinertiatensormass)(mass) vector3
* CollisionShape:[getVolume](#collisionshapegetvolume)() number
* CollisionShape:[computeAABB](#collisionshapecomputeaabbtransform)(transform) [AABB](../aabb.md)

---

### CollisionShape:getName()

Return the name of the collision shape.

TRIANGLE, SPHERE, CAPSULE, BOX, CONVEX_MESH, TRIANGLE_MESH

**RETURN**

* ([rp3d.CollisionShapeName](../rp3d.md#rp3dcollisionshapename)) 

---

### CollisionShape:getType()

Return the type of the collision shape.

SPHERE, CAPSULE, CONVEX_POLYHEDRON, CONCAVE_SHAPE

**RETURN**

* ([rp3d.CollisionShapeType](../rp3d.md#rp3dcollisionshapetype)) 

---

### CollisionShape:isConvex()

Return true if the collision shape is convex, false if it is concave.

**RETURN**

* (bool)

---

### CollisionShape:isPolyhedron()

Return true if the collision shape is a polyhedron.

**RETURN**

* (bool)

---

### CollisionShape:getLocalBounds()

Return the local bounds of the shape in x, y and z directions.

**RETURN**

* (vector3) - min
* (vector3) - max

---

### CollisionShape:getId()

Return the id of the shape.

**RETURN**

* (number)

---

### CollisionShape:getLocalInertiaTensor(mass)

Return the local inertia tensor of the collision shapes.

**PARAMETERS**

* `mass` (number)

**RETURN**

* (vector3)

---

### CollisionShape:getVolume()

Compute and return the volume of the collision shape.

**RETURN**

* (number)

---

### CollisionShape:computeAABB(transform)

Compute the world-space AABB of the collision shape given a transform.

**PARAMETERS**

* `transform` ([Transform](../transform.md))

**RETURN**

* ([AABB](../aabb.md))