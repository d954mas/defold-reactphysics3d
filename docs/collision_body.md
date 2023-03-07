# CollisionBody

This class represents a body that is able to collide with others bodies.

Subclasses:

1. [RigidBody](rigid_body.md)

## Create

```lua
local body = world:createCollisionBody(transform);
```

## Methods

* CollisionBody:[getEntityId](#collisionbodygetentityid)() number
* CollisionBody:[isRigidBody](#collisionbodyisrigidbody)() bool
* CollisionBody:[isActive](#collisionbodyisactive)() bool
* CollisionBody:[setIsActive](#collisionbodysetisactiveisactive)(isActive)
* CollisionBody:[getUserData](#collisionbodygetuserdata)() table|nil
* CollisionBody:[setUserData](#collisionbodysetuserdatauserdata)(userData)
* CollisionBody:[getTransform](#collisionbodygettransform)() [Transform](transform.md)
* CollisionBody:[setTransform](#collisionbodysettransformtransform)(transform)
* CollisionBody:[getTransformPosition](#collisionbodygettransformposition)() vector3
* CollisionBody:[setTransformPosition](#collisionbodysettransformpositionposition)(position)
* CollisionBody:[getTransformQuat](#collisionbodygettransformquat)() quaternion
* CollisionBody:[setTransformQuat](#collisionbodysettransformquatquat)(quat)
* CollisionBody:[addCollider](#collisionbodyaddcollidercollisionshape-transform)(collisionShape,
  transform) [Collider](collider.md)
* CollisionBody:[removeCollider](#collisionbodyremovecollidercollider)(collider)
* CollisionBody:[testPointInside](#collisionbodytestpointinsideworldpoint)(worldPoint) bool
* CollisionBody:[raycast](#collisionbodyraycastray)(ray) [RaycastInfo](raycast_info.md)|nil
* CollisionBody:[testAABBOverlap](#collisionbodytestaabboverlapworldaabb)(worldAABB) bool
* CollisionBody:[getAABB](#collisionbodygetaabb)() [AABB](aabb.md)
* CollisionBody:[getCollider](#collisionbodygetcollidercolliderindex)(colliderIndex) [Collider](collider.md)
* CollisionBody:[getNbColliders](#collisionbodygetnbcolliders)() number
* CollisionBody:[getWorldPoint](#collisionbodygetworldpointlocalpoint)(localPoint) vector3
* CollisionBody:[getWorldVector](#collisionbodygetworldvectorlocalvector)(localVector) vector3
* CollisionBody:[getLocalPoint](#collisionbodygetlocalpointworldpoint)(worldPoint) vector3
* CollisionBody:[getLocalVector](#collisionbodygetlocalvectorworldvector)(worldVector) vector3

---

### CollisionBody:getEntityId()

Return the corresponding entity id of the body.

**RETURN**

* (number)

---

### CollisionBody:isRigidBody()

Return true if body is rigid.

**RETURN**

* (bool)

---

### CollisionBody::isActive()

Return true if the body is active.

**RETURN**

* (bool)

---

### CollisionBody::setIsActive(isActive)

Set whether or not the body is active.

**PARAMETERS**

* `isActive` (bool)

---

### CollisionBody:getUserData()

Return a table attached to this body or nil.

**RETURN**

* (table|nil)

---

### CollisionBody:setUserData(userData)

Attach user data to this body.

**PARAMETERS**

* `userData` (table|nil)

---

### CollisionBody:getTransform()

Return the current position and orientation. The current transformation of the body that transforms the local-space of
the body into world-space

**RETURN**

* ([Transform](transform.md))

---

### CollisionBody:setTransform(transform)

Set the current position and orientation.

**PARAMETERS**

* `transform` ([Transform](transform.md))

### CollisionBody:getTransformPosition()

Return the current position.

**RETURN**

* (vector3)

---

### CollisionBody:setTransformPosition(position)

Set the current position.

**PARAMETERS**

* `position` (vector3)

---

### CollisionBody:getTransformQuat()

Return the current orientation.

**RETURN**

* (quaternion)

---

### CollisionBody:setTransformQuat(quat)

Set the current orientation.

**PARAMETERS**

* `quat` (quaternion)

---

### CollisionBody:addCollider(collisionShape, transform)

Create a new collider and add it to the body.

This method will return a new collider.

A collider is an object with a collision shape that is attached to a body. It is possible to attach multiple colliders
to a given body. You can use the returned collider to get and set information about the corresponding collision shape
for that body.

**PARAMETERS**

* `collisionShape` ([CollisionShape](shapes/collision_shape.md))
* `transform` ([Transform](transform.md))

**RETURN**

* ([Collider](collider.md))

---

### CollisionBody:removeCollider(collider)

Remove a collider from the body.

**PARAMETERS**

* `collider` ([Collider](collider.md))

---

### CollisionBody:testPointInside(worldPoint)

Return true if a point is inside the collision body.

**PARAMETERS**

* `worldPoint` (vector3)

**RETURN**

* (bool)

---

### CollisionBody:raycast(ray)

Raycast method with feedback information. Retun (nil) if the ray not hits the body

**PARAMETERS**

* `ray` ([Ray](ray.md))

**RETURN**

* ([RaycastInfo](raycast_info.md)|nil)

---

### CollisionBody:testAABBOverlap(worldAABB)

Test if the collision body overlaps with a given AABB.

**PARAMETERS**

* `worldAABB` ([AABB](aabb.md))

**RETURN**

* (bool)

---

### CollisionBody:getAABB()

Compute and return the AABB of the body by merging all colliders AABBs.

**RETURN**

* ([AABB](aabb.md))

---

### CollisionBody:getCollider(colliderIndex)

Return a given collider of the body.

**PARAMETERS**

* `colliderIndex` (number)

**RETURN**

* ([Collider](collider.md))

---

### CollisionBody:getNbColliders()

Return the number of colliders associated with this body.

**RETURN**

* (number)

---

### CollisionBody:getWorldPoint(localPoint)

Return the world-space coordinates of a point given the local-space coordinates of the body.

**PARAMETERS**

* `localPoint` (vector3)

**RETURN**

* (vector3)

---

### CollisionBody:getWorldVector(localVector)

Return the world-space vector of a vector given in local-space coordinates of the body.

**PARAMETERS**

* `localVector` (vector3)

**RETURN**

* (vector3)

---

### CollisionBody:getLocalPoint(worldPoint)

Return the body local-space coordinates of a point given in the world-space coordinates.

**PARAMETERS**

* `worldPoint` (vector3)

**RETURN**

* (vector3)

---

### CollisionBody:getLocalVector(worldVector)

Return the body local-space coordinates of a vector given in the world-space coordinates.

**PARAMETERS**

* `worldVector` (vector3)

**RETURN**

* (vector3)




