# RigidBody

RigidBody extends [CollisionBody](collision_body.md)

This class represents a rigid body of the physics engine.

A rigid body is a non-deformable body that has a constant mass. This class inherits from the CollisionBody class.

## Create

```lua
local body = world:createRigidBody(transform);
```

## Methods

* RigidBody:[getMass](#rigidbodygetmass)() number
* RigidBody:[setMass](#rigidbodysetmassmass)(mass)
* RigidBody:[getLinearVelocity](#rigidbodygetlinearvelocity)() vector3
* RigidBody:[setLinearVelocity](#rigidbodysetlinearvelocitylinearvelocity)(linearVelocity)
* RigidBody:[getAngularVelocity](#rigidbodygetangularvelocity)() vector3
* RigidBody:[setAngularVelocity](#rigidbodysetangularvelocityangularvelocity)(angularVelocity)
* RigidBody:[getLocalInertiaTensor](#rigidbodygetlocalinertiatensor)() vector3
* RigidBody:[setLocalInertiaTensor](#rigidbodysetlocalinertiatensorinertiatensorlocal)(inertiaTensorLocal)
* RigidBody:[getLocalCenterOfMass](#rigidbodygetlocalcenterofmass)() vector3
* RigidBody:[setLocalCenterOfMass](#rigidbodysetlocalcenterofmasscenterofmass)(centerOfMass)
* RigidBody:[updateLocalCenterOfMassFromColliders](#rigidbodyupdatelocalcenterofmassfromcolliders)()
* RigidBody:[updateLocalInertiaTensorFromColliders](#rigidbodyupdatelocalinertiatensorfromcolliders)()
* RigidBody:[updateMassFromColliders](#rigidbodyupdatemassfromcolliders)()
* RigidBody:[updateMassPropertiesFromColliders](#rigidbodyupdatemasspropertiesfromcolliders)()
* RigidBody:[getType](#rigidbodygettype)() [BodyType](rp3d.md#rp3dbodytype)
* RigidBody:[setType](#rigidbodysettypetype)(type)
* RigidBody:[isGravityEnabled](#rigidbodyisgravityenabled)() bool
* RigidBody:[enableGravity](#rigidbodyenablegravityisenabled)(isEnabled)
* RigidBody:[isSleeping](#rigidbodyissleeping)() bool
* RigidBody:[setIsSleeping](#rigidbodysetissleepingissleeping)(isSleeping)
* RigidBody:[getLinearDamping](#rigidbodygetlineardamping)() number
* RigidBody:[setLinearDamping](#rigidbodysetlineardampinglineardamping)(linearDamping)
* RigidBody:[getAngularDamping](#rigidbodygetangulardamping)() number
* RigidBody:[setAngularDamping](#rigidbodysetangulardampingangulardamping)(angularDamping)
* RigidBody:[getLinearLockAxisFactor](#rigidbodygetlinearlockaxisfactor)() vector3
* RigidBody:[setLinearLockAxisFactor](#rigidbodysetlinearlockaxisfactorlinearlockaxisfactor)(linearLockAxisFactor)
* RigidBody:[getAngularLockAxisFactor](#rigidbodygetangularlockaxisfactor)() vector3
* RigidBody:[setAngularLockAxisFactor](#rigidbodysetangularlockaxisfactorangularlockaxisfactor)(angularLockAxisFactor)
* RigidBody:[applyLocalForceAtCenterOfMass](#rigidbodyapplylocalforceatcenterofmassforce)(force) 
* RigidBody:[applyWorldForceAtCenterOfMass](#rigidbodyapplyworldforceatcenterofmassforce)(force) 
* RigidBody:[applyLocalForceAtLocalPosition](#rigidbodyapplylocalforceatlocalpositionforce-point)(force, point) 
* RigidBody:[applyWorldForceAtLocalPosition](#rigidbodyapplyworldforceatlocalpositionforce-point)(force, point) 
* RigidBody:[applyLocalForceAtWorldPosition ](#rigidbodyapplylocalforceatworldpositionforc-epoint)(force, point)
* RigidBody:[applyWorldForceAtWorldPosition](#rigidbodyapplyworldforceatworldpositionforce-point)(force, point) 
* RigidBody:[applyWorldTorque](#rigidbodyapplyworldtorquetorque)(torque) 
* RigidBody:[applyLocalTorque](#rigidbodyapplylocaltorquetorque)(torque) 
* RigidBody:[resetForce](#rigidbodyresetforce)() 
* RigidBody:[resetTorque](#rigidbodyresettorque)() 
* RigidBody:[getForce](#rigidbodygetforce)() vector3
* RigidBody:[getTorque](#rigidbodygettorque)() vector3
* RigidBody:[isAllowedToSleep](#rigidbodyisallowedtosleep)() bool
* RigidBody:[setIsAllowedToSleep](#rigidbodysetisallowedtosleepisallowedtosleep)(isAllowedToSleep)

---
### RigidBody:getMass()
Return the mass of the body.

**RETURN**
* (number)

---
### RigidBody:setMass(mass)
Set the mass of the rigid body.

**PARAMETERS**
* `mass` (vector3)

---
### RigidBody:getLinearVelocity()
Return the linear velocity.

**RETURN**
* (vector3)

---
### RigidBody:setLinearVelocity(linearVelocity)
Set the linear velocity of the body.

**PARAMETERS**
* `linearVelocity` (vector3)

---
### RigidBody:getAngularVelocity()
Return the angular velocity.

**RETURN**
* (vector3)

---
### RigidBody:setAngularVelocity(angularVelocity)
Set the angular velocity of the body.

**PARAMETERS**
* `angularVelocity` (vector3)

---
### RigidBody:getLocalInertiaTensor()
Return the local inertia tensor of the body (in body coordinates)
A vector with the three values of the diagonal 3x3 matrix of the local-space inertia tensor

**RETURN**
* (vector3)

---
### RigidBody:setLocalInertiaTensor(inertiaTensorLocal)
Set the local inertia tensor of the body (in body coordinates)
Note that an inertia tensor with a zero value on its diagonal is interpreted as infinite inertia.

**PARAMETERS**
* `inertiaTensorLocal` (vector3)

---
### RigidBody:getLocalCenterOfMass()
Return the center of mass of the body (in local-space coordinates)

**RETURN**
* (vector3)

---
### RigidBody:setLocalCenterOfMass(centerOfMass)
Set the center of mass of the body (in local-space coordinates)

**PARAMETERS**
* `centerOfMass` (vector3)

---
### RigidBody:updateLocalCenterOfMassFromColliders()
Сompute and set the local-space center of mass of the body using its colliders.

This method uses the shape, mass density and transforms of the colliders to set the center of mass of the body.

Note that calling this method will overwrite the mass that has been previously set with the RigidBody:setCenterOfMass() method. Moreover, this method does not use the mass set by the user with the RigidBody:setMass() method to compute the center of mass but only the mass density and volume of the colliders.

---
### RigidBody:updateLocalInertiaTensorFromColliders()
Compute and set the local-space inertia tensor of the body using its colliders.

This method uses the shape, mass density and transforms of the colliders to set the local-space inertia tensor of the body.

Note that calling this method will overwrite the mass that has been set with the RigidBody:setInertiaTensorLocal() method.


---
### RigidBody:updateMassFromColliders()
Compute and set the mass of the body using its colliders.

This method uses the shape, mass density and transforms of the colliders to set the total mass of the body.

Note that calling this method will overwrite the mass that has been set with the RigidBody:setMass() method

---
### RigidBody:updateMassPropertiesFromColliders()
Compute and set the center of mass, the mass and the local-space inertia tensor of the body using its colliders.

This method uses the shape, mass density and transform of the colliders of the body to set the total mass, the center of mass and the local inertia tensor of the body.

Note that calling this method will overwrite the mass that has been set with the RigidBody:setMass(), the center of mass that has been set with RigidBody:setCenterOfMass() and the local inertia tensor that has been set with RigidBody:setInertiaTensorLocal().

---
### RigidBody:getType()
Return the type of the body.

**RETURN**
* ([BodyType](rp3d.md#rp3dbodytype))

---
### RigidBody:setType(type)
Set the type of the body.

**PARAMETERS**
* `type` ([BodyType](rp3d.md#rp3dbodytype))

---
### RigidBody::isGravityEnabled()
Return true if the gravity needs to be applied to this rigid body.

**RETURN**
* (bool)

---
### RigidBody::enableGravity(isEnabled)
Set the variable to know if the gravity is applied to this rigid body. 

**PARAMETERS**
* `isEnabled` (bool)

---
### RigidBody::isSleeping()
Return whether or not the body is sleeping.

**RETURN**
* (bool)

---
### RigidBody::setIsSleeping(isSleeping)
Set the variable to know whether or not the body is sleeping. 

**PARAMETERS**
* `isSleeping` (bool)

---
### RigidBody:getLinearDamping()
Return the linear velocity damping factor.

**RETURN**
* (number)

---
### RigidBody:setLinearDamping(linearDamping)
Set the linear damping factor.

**PARAMETERS**
* `linearDamping` (number)

---
### RigidBody:getAngularDamping()
Return the angular velocity damping factor.

**RETURN**
* (number)

---
### RigidBody:setAngularDamping(angularDamping)
Set the angular damping factor.

**PARAMETERS**
* `angularDamping` (number)

---
### RigidBody:getLinearLockAxisFactor()
Return the lock translation factor.

**RETURN**
* (vector3)

---
### RigidBody:setLinearLockAxisFactor(linearLockAxisFactor)
Set the linear lock factor.

**PARAMETERS**
* `linearLockAxisFactor` (vector3)

---
### RigidBody:getAngularLockAxisFactor()
Return the lock rotation factor.

**RETURN**
* (vector3)

---
### RigidBody:setAngularLockAxisFactor(angularLockAxisFactor)
Set the lock rotation factor.

**PARAMETERS**
* `angularLockAxisFactor` (vector3)

---
### RigidBody:applyLocalForceAtCenterOfMass(force)
Manually apply an external force (in local-space) to the body at its center of mass.

**PARAMETERS**
* `force` (vector3)

---
### RigidBody:applyWorldForceAtCenterOfMass(force)
Manually apply an external force (in world-space) to the body at its center of mass.

**PARAMETERS**
* `force` (vector3)

---
### RigidBody:applyLocalForceAtLocalPosition(force, point)
Manually apply an external force (in local-space) to the body at a given point (in local-space).

**PARAMETERS**
* `force` (vector3)
* `point` (vector3)

---
### RigidBody:applyWorldForceAtLocalPosition(force, point)
Manually apply an external force (in world-space) to the body at a given point (in local-space).

**PARAMETERS**
* `force` (vector3)
* `point` (vector3)

---
### RigidBody:applyLocalForceAtWorldPosition(force, point)
Manually apply an external force (in local-space) to the body at a given point (in world-space).

**PARAMETERS**
* `force` (vector3)
* `point` (vector3)

---
### RigidBody:applyWorldForceAtWorldPosition(force, point)
Manually apply an external force (in world-space) to the body at a given point (in world-space).

**PARAMETERS**
* `force` (vector3)
* `point` (vector3)

---
### RigidBody:applyWorldTorque(torque)
Manually apply an external torque to the body (in world-space).

**PARAMETERS**
* `torque` (vector3)

---
### RigidBody:applyLocalTorque(torque)
Manually apply an external torque to the body (in local-space).

**PARAMETERS**
* `torque` (vector3)

---
### RigidBody:resetForce()
Reset the manually applied force to zero. 

---
### RigidBody:resetTorque()
Reset the manually applied torque to zero. 

---
### RigidBody:getForce()
Return the total manually applied force on the body (in world-space)

**RETURN**
* (vector3)

---
### RigidBody:getTorque()
Return the total manually applied torque on the body (in world-space)

**RETURN**
* (vector3)

---
### RigidBody:isAllowedToSleep()
Return whether or not the body is allowed to sleep.

**RETURN**
* (bool)

---
### RigidBody::setIsAllowedToSleep(isAllowedToSleep)
Set whether or not the body is allowed to go to sleep.

**PARAMETERS**
* `isAllowedToSleep` (bool)