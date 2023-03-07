# Collider
A collider has a collision shape (box, sphere, capsule, ...) and is attached to a [CollisionBody](collision_body.md) or [RigidBody](rigid_body.md).

A body can have multiple colliders. The collider also have a mass value and a [Material](material.md) with many physics parameters like friction or bounciness. When you create a body, you need to attach at least one collider to it if you want that body to be able to collide in the physics world.

## Create

```lua
local collider = body:addCollider(shape, transform)
```

## Methods

* Collider:[getEntityId](#collidergetentityid)() number
* Collider:[getCollisionShape](#collidergetcollisionshape)() [CollisionShape](shapes/collision_shape.md)
* Collider:[getBody](#collidergetbody)() [CollisionBody](collision_body.md)
* Collider:[getUserData](#collidergetuserdata)() table|nil
* Collider:[setUserData](#collidersetuserdatauserdata)(userData)
* Collider:[getLocalToBodyTransform](#collidergetlocaltobodytransform)() [Transform](transform.md)
* Collider:[setLocalToBodyTransform](#collidersetlocaltobodytransformtransform)(transform)
* Collider:[getLocalToWorldTransform](#collidergetlocaltoworldtransform)() [Transform](transform.md)
* Collider:[getWorldAABB](#collidergetworldaabb)() [AABB](aabb.md)
* Collider:[testAABBOverlap](#collidertestaabboverlapworldaabb)(worldAABB) bool
* Collider:[testPointInside](#collidertestpointinsideworldpoint)(worldPoint) bool
* Collider:[raycast](#colliderraycastray)(ray) [RaycastInfo](raycast_info.md)|nil
* Collider:[getCollideWithMaskBits](#collidergetcollidewithmaskbits)() number
* Collider:[setCollideWithMaskBits](#collidersetcollidewithmaskbitscollidewithmaskbits)(collideWithMaskBits) 
* Collider:[getCollisionCategoryBits](#collidergetcollisioncategorybits)() number
* Collider:[setCollisionCategoryBits](#collidersetcollisioncategorybitscollisioncategorybits)(collisionCategoryBits) 
* Collider:[getBroadPhaseId](#collidergetbroadphaseid)() number
* Collider:[getMaterial](#collidergetmaterial)() [Material](material.md)
* Collider:[setMaterial](#collidersetmaterialmaterial)(material)
* Collider:[getMaterialBounciness](#collidergetmaterialbounciness)() number
* Collider:[setMaterialBounciness](#collidersetmaterialbouncinessbounciness)(bounciness) 
* Collider:[getMaterialFrictionCoefficient](#collidergetmaterialfrictioncoefficient)() number
* Collider:[setMaterialFrictionCoefficient](#collidersetmaterialfrictioncoefficientfrictioncoefficient)(frictionCoefficient)
* Collider:[getMaterialMassDensity](#collidergetmaterialmassdensity)() number
* Collider:[setMaterialMassDensity](#collidersetmaterialmassdensitymassdensity)(massDensity)
* Collider:[getIsTrigger](#collidergetistrigger)() bool
* Collider:[setIsTrigger](#collidersetistriggeristrigger)(isTrigger)

---
### Collider:getEntityId()
Return the corresponding entity id of the collider.

**RETURN**
* (number)

---
### Collider:getCollisionShape()
Return the collision shape.

**RETURN**
* ([CollisionShape](shapes/collision_shape.md))

---
### Collider:getBody()
Return the parent body.

**RETURN**
* ([CollisionBody](collision_body.md))

---
### Collider:getUserData()
Return a table attached to this body or nil.

**RETURN**
* (table|nil)

---
### Collider:setUserData(userData)
Attach user data to this body.

**PARAMETERS**
* `userData` (table|nil)

---
### Collider:getLocalToBodyTransform()
Return the local to parent body transform. 

**RETURN**
* ([Transform](transform.md))

---
### Collider:setLocalToBodyTransform(transform)
Set the local to parent body transform.

**PARAMETERS**
* `transform` ([Transform](transform.md))

---
### Collider:getLocalToWorldTransform()
Return the local to world transform.

**RETURN**
* ([Transform](transform.md))

---
### Collider:getWorldAABB()
Return the AABB of the collider in world-space.

**RETURN**
* ([AABB](aabb.md))

---
### Collider:testAABBOverlap(worldAABB)
Test if the collider overlaps with a given AABB

**PARAMETERS**
* `worldAABB` ([AABB](aabb.md))

**RETURN**
* (bool)

---
### Collider:testPointInside(worldPoint)
Return true if a point is inside the collision shape.

**PARAMETERS**
* `worldPoint` (vector3)

**RETURN**
* (bool)

---
### Collider:raycast(ray)
Raycast method with feedback information.
Retun (nil) if the ray not hits the collision shape

**PARAMETERS**
* `ray` ([Ray](ray.md))

**RETURN**
* ([RaycastInfo](raycast_info.md)|nil)

---
### Collider:getCollideWithMaskBits()
Return the collision bits mask.

**RETURN**
* (number)

---
### Collider:setCollideWithMaskBits(collideWithMaskBits)
Return the collision bits mask.

**PARAMETERS**
* `collideWithMaskBits` (number)

---
### Collider:getCollisionCategoryBits()
Return the collision category bits. 

**RETURN**
* (number)

---
### Collider:setCollisionCategoryBits(collisionCategoryBits)
Set the collision category bits.

**PARAMETERS**
* `collisionCategoryBits` (number)

---
### Collider:getBroadPhaseId()
Return the broad-phase id.

**RETURN**
* (number)

---
### Collider:getMaterial()
Return a material properties of the collider.

**RETURN**
* ([Material](material.md))

---
### Collider:setMaterial(material)
Set a new material for this collider.

**PARAMETERS**
* `material` ([Material](material.md))

---
### Collider:getMaterialBounciness()
Return a bounciness properties of material.

**RETURN**
* (number)

---
### Collider:setMaterialBounciness(bounciness)
Set a bounciness properties of material.

**PARAMETERS**
* `bounciness` (number)

---
### Collider:getMaterialFrictionCoefficient()
Return a frictionCoefficient properties of material.

**RETURN**
* (number)

---
### Collider:setMaterialFrictionCoefficient(frictionCoefficient)
Set a frictionCoefficient properties of material.

**PARAMETERS**
* `frictionCoefficient` (number)

---
### Collider:getMaterialMassDensity()
Return a massDensity properties of material.

**RETURN**
* (number)

---
### Collider:setMaterialMassDensity(massDensity)
Set a massDensity properties of material.

**PARAMETERS**
* `massDensity` (number)

---
### Collider:getIsTrigger()
Return true if the collider is a trigger.

**RETURN**
* (bool)

---
### Collider:setIsTrigger(isTrigger)
Set whether the collider is a trigger.

**PARAMETERS**
* `isTrigger` (bool)