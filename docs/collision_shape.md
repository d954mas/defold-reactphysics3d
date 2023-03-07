# CollisionShape
This abstract class represents the collision shape associated with a body that is used during the narrow-phase collision detection.

You can create 6 types of shape:
1. CapsuleShape
2. SphereShape
3. BoxShape
4. ConvexMeshShape
5. ConcaveMeshShape
6. HeightFieldShape

Inheritance diagram for Collision Shape.

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/collision_shape_classes.png">

## Create
You can't create CollisionShape class.

## Methods

* CollisionShape:[getName](#collisionshapegetname)() CollisionShapeName
* CollisionShape:[getType](#collisionshapegettype)() CollisionShapeType
* CollisionShape:[isConvex](#collisionshapeisconvex)() bool
* CollisionShape:[isPolyhedron](#collisionshapeispolyhedron)() bool
* CollisionShape:[getLocalBounds](#collisionshapegetlocalbounds)() vector3 vector3
* CollisionShape:[getId](#collisionshapegetid)() number
* CollisionShape:[getLocalInertiaTensor](#collisionshapegetlocalinertiatensormass)(mass) vector3
* CollisionShape:[getVolume](#collisionshapegetvolume)() number
* CollisionShape:[computeAABB](#collisionshapecomputeaabbtransform)(transform) AABB

---
### CollisionShape:getName()
Return the name of the collision shape.

Enum constants in rp3d.CollisionShapeName.

TRIANGLE, SPHERE, CAPSULE, BOX, CONVEX_MESH, TRIANGLE_MESH

**RETURN**
* (string)

---
### CollisionShape:getType()
Return the type of the collision shape.

Enum constants in rp3d.CollisionShapeType.

SPHERE, CAPSULE, CONVEX_POLYHEDRON, CONCAVE_SHAPE

**RETURN**
* (string)

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
* `transform` [(Transform)](transform.md)

**RETURN**
* [(AABB)](aabb.md)