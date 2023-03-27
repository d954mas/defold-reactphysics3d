# PhysicsWorld
This class represents a physics world.

## WorldSettings
```lua
---@class WorldSettings
local WorldSettings = {
	--Name of the world
	worldName = "",
	--Gravity force vector of the world (in Newtons)
	gravity = vmath.vector3(0, -9.81, 0),
	--Distance threshold for two contact points for a valid persistent contact (in meters)
	persistentContactDistanceThreshold = 0.03,
	--Default friction coefficient for a rigid body
	defaultFrictionCoefficient = 0.3,
	--Default bounciness factor for a rigid body
	defaultBounciness = 0.5,
	--Velocity threshold for contact velocity restitution
	restitutionVelocityThreshold = 0.5,
	--True if the sleeping technique is enabled
	isSleepingEnabled = true;
	--Number of iterations when solving the velocity constraints of the Sequential Impulse technique
	defaultVelocitySolverNbIterations = 6,
	--Number of iterations when solving the position constraints of the Sequential Impulse technique
	defaultPositionSolverNbIterations = 3,
	--Time (in seconds) that a body must stay still to be considered sleeping
	defaultTimeBeforeSleep = 1.0,
	--A body with a linear velocity smaller than the sleep linear velocity (in m/s) might enter sleeping mode.
	defaultSleepLinearVelocity = 0.02,
	--A body with angular velocity smaller than the sleep angular velocity (in rad/s) might enter sleeping mode
	defaultSleepAngularVelocity = 3.0 * (math.pi / 180.0),
	-- This is used to test if two contact manifold are similar (same contact normal) in order to
	-- merge them. If the cosine of the angle between the normals of the two manifold are larger
	-- than the value bellow, the manifold are considered to be similar.
	cosAngleSimilarContactManifold = 0.95,
}
```



## OverlapPair

* `collider1` ([Collider](collider.md))
* `collider2` ([Collider](collider.md))
* `body1` ([CollisionBody](collision_body.md))
* `body2` ([CollisionBody](collision_body.md))
* `eventType` ([OverlapPair.EventType](rp3d.md#rp3doverlappair))


## ContactPair

* `collider1` ([Collider](collider.md))
* `collider2` ([Collider](collider.md))
* `body1` ([CollisionBody](collision_body.md))
* `body2` ([CollisionBody](collision_body.md))
* `eventType` ([ContactPair.EventType](rp3d.md#rp3dcontactpair))
* `contacts` ([ContactPairContact](#contactpaircontact)[])

## ContactPairContact

* `penetrationDepth` (number) 
* `worldNormal` (vector3) 
* `localPointOnCollider1` (vector3) 
* `localPointOnCollider2` (vector3) 


## EventListener
```lua
local EventListener = {
	---@param contacts ContactPair[]
	onContact = function(contacts)
        
	end,
	---@param triggers OverlapPair[]
	onTrigger = function(triggers)
		
	end
}
```

## RaycastCallback
```lua
---@param info RaycastInfo
local raycastCallback = function(info) 
    return info.hitFraction
end
```


## Methods

* World:[getName](#worldgetname)() string
* World:[getGravity](#worldgetgravity)() vector3
* World:[setGravity](#worldsetgravitygravity)(gravity)
* World:[isGravityEnabled](#worldisgravityenabled)() bool
* World:[setIsGravityEnabled](#worldsetisgravityenabledisgravityenabled)(isGravityEnabled)
* World:[getNbIterationsVelocitySolver](#worldgetnbiterationsvelocitysolver)() number
* World:[setNbIterationsVelocitySolver](#worldsetnbiterationsvelocitysolvernbiterations)(nbIterations)
* World:[getNbIterationsPositionSolver](#worldgetnbiterationspositionsolver)() number
* World:[setNbIterationsPositionSolver](#worldsetnbiterationspositionsolvernbiterations)(nbIterations)
* World:[isSleepingEnabled](#worldissleepingenabled)() bool
* World:[enableSleeping](#worldenablesleepingissleepingenabled)(isSleepingEnabled)
* World:[getTimeBeforeSleep](#worldgettimebeforesleep)() number
* World:[setTimeBeforeSleep](#worldsettimebeforesleeptimebeforesleep)(timeBeforeSleep)
* World:[getSleepLinearVelocity](#worldgetsleeplinearvelocity)() number
* World:[setSleepLinearVelocity](#worldsetsleeplinearvelocitysleeplinearvelocity)(sleepLinearVelocity)
* World:[getSleepAngularVelocity](#worldgetsleepangularvelocity)() number
* World:[setSleepAngularVelocity](#worldsetsleepangularvelocitysleepangularvelocity)(sleepAngularVelocity)
* World:[update](#worldupdatetimestep)(timeStep)
* World:[setContactsPositionCorrectionTechnique](#worldsetcontactspositioncorrectiontechniquetechnique)(technique)
* World:[enableDisableJoints](#worldenabledisablejoints)()
* World:[getNbCollisionBodies](#worldgetnbcollisionbodies)() number
* World:[getCollisionBody](#worldgetcollisionbodyindex)(index) [CollisionBody](collision_body.md)
* World:[getNbRigidBodies](#worldgetnbrigidbodies)() number
* World:[getRigidBody](#worldgetcollisionbodyindex)(index) [RigidnBody](rigid_body.md)
* World:[getIsDebugRenderingEnabled](#worldgetisdebugrenderingenabled)() bool
* World:[setIsDebugRenderingEnabled](#worldsetisdebugrenderingenabledisenabled)(isEnabled)
* World:[createCollisionBody](#worldcreatecollisionbodytransform)(transform) [CollisionBody](collision_body.md)
* World:[destroyCollisionBody](#worlddestroycollisionbodycollisionbody)(collisionBody)
* World:[createRigidBody](#worldcreaterigidbodytransform)(transform) [RigidBody](rigid_body.md)
* World:[destroyRigidBody](#worlddestroyrigidbodyrigidbody)(rigidBody)
* World:[getDebugRenderer](#worldgetdebugrenderer)() [DebugRenderer](debug_renderer.md)
* World:[raycast](#worldraycastray-cb-categorymaskbits)(ray, cb, categoryMaskBits)
* World:[testOverlap2Bodies](#worldtestoverlap2bodiesbody1-body2)(body1, body2) bool
* World:[testOverlapBodyList](#worldtestoverlapbodylistbody)(body) [OverlapPair](#overlappair)[]
* World:[testOverlapList](#worldtestoverlaplist)() [OverlapPair](#overlappair)[]
* World:[testCollision2Bodies](#worldtestcollision2bodiesbody1-body2)(body1, body2) [ContactPair](#contactpair)|nil
* World:[testCollisionBodyList](#worldtestcollisionbodylistbody)(body) [ContactPair](#contactpair)[]
* World:[testCollisionList](#worldtestcollisionlist)() [ContactPair](#overlappair)[]
* World:[setEventListener](#worldseteventlistenerlistener)(listener)
* World:[createJoint](#worldcreatejointjointinfo)(jointInfo) [Joint](joints/join.md)

---
### World:getName()
Return the name of the world.

**RETURN**
* (string)

---
### World:getGravity()
Return the gravity vector of the world.

**RETURN**
* (vector3)

---
### World:setGravity(gravity)
Set the gravity vector of the world.

**PARAMETERS**
* `gravity` (vector3)

---
### World:isGravityEnabled()
Return if the gravity is on.

**RETURN**
* (bool)

---
### World:setIsGravityEnabled(isGravityEnabled)
Enable/Disable the gravity.

**PARAMETERS**
* `isGravityEnabled` (bool)

---
### World:getNbIterationsVelocitySolver()
Get the number of iterations for the velocity constraint solver.

**RETURN**
* (number)

---
### World:setNbIterationsVelocitySolver(nbIterations)
Set the number of iterations for the velocity constraint solver.

**PARAMETERS**
* `nbIterations` (number)

---
### World:getNbIterationsPositionSolver()
Get the number of iterations for the position constraint solver.

**RETURN**
* (number)

---
### World:setNbIterationsPositionSolver(nbIterations)
Set the number of iterations for the position constraint solver.

**PARAMETERS**
* `nbIterations` (number)

---
### World:isSleepingEnabled()
Return true if the sleeping technique is enabled.

**RETURN**
* (bool)

---
### World:enableSleeping(isSleepingEnabled)
Enable/Disable the sleeping technique.

**PARAMETERS**
* `isSleepingEnabled` (bool)

---
### World:getTimeBeforeSleep()
Return the time a body is required to stay still before sleeping.

**RETURN**
* (number)

---
### World:setTimeBeforeSleep(timeBeforeSleep)
Set the time a body is required to stay still before sleeping.

**PARAMETERS**
* `timeBeforeSleep` (number)

---
### World:getSleepLinearVelocity()
Return the current sleep linear velocity.

**RETURN**
* (number)

---
### World:setSleepLinearVelocity(sleepLinearVelocity)
Set the sleep linear velocity.

**PARAMETERS**
* `sleepLinearVelocity` (number)

---
### World:getSleepAngularVelocity()
Return the current sleep angular velocity. 

**RETURN**
* (number)

---
### World:setSleepAngularVelocity(sleepAngularVelocity)
Set the sleep angular velocity.

**PARAMETERS**
* `sleepAngularVelocity` (number)

---
### World:update(timeStep)
Update the physics simulation.

**PARAMETERS**
* `timeStep` (number)

---
### World:setContactsPositionCorrectionTechnique(technique)
Set the position correction technique used for contacts.

**PARAMETERS**
* `technique` ([ContactsPositionCorrectionTechnique](rp3d.md#rp3dcontactspositioncorrectiontechnique))

---
### World:enableDisableJoints()
Disable the joints for pair of sleeping bodies. 

---
### World:getNbCollisionBodies()
Return the number of CollisionBody in the physics world.

**RETURN**
* (number)

---
### World:getCollisionBody(index)
Return a CollisionBody of the world.

**PARAMETERS**
* `index` (number)

**RETURN**
* ([CollisionBody](collision_body.md))

---
### World:getNbRigidBodies()
Return the number of RigidBody in the physics world.

**RETURN**
* (number)

---
### World:getRigidBody(index)
Return a RigidBody of the world.

**PARAMETERS**
* `index` (number)

**RETURN**
* ([RigidBody](rigid_body.md))

---
### World:getIsDebugRenderingEnabled() 
Return true if the debug rendering is enabled

**RETURN**
* (bool)

---
### World:setIsDebugRenderingEnabled(isEnabled)
Set to true if debug rendering is enabled.

**PARAMETERS**
* `isEnabled` (bool)

---
### World:createCollisionBody(transform)
Create a collision body.

**PARAMETERS**
* `transform` ([Transform](transform.md))

**RETURN**
* ([CollisionBody](collision_body.md))

---
### World:destroyCollisionBody(collisionBody)
Destroy a collision body.

**PARAMETERS**
* `collisionBody` ([CollisionBody](collision_body.md))

---
### World:createRigidBody(transform)
Create a rigid body into the physics world.

**PARAMETERS**
* `transform` ([Transform](transform.md))

**RETURN**
* ([RigidBody](rigid_body.md))

---
### World:destroyRigidBody(rigidBody)
Destroy a rigid body and all the joints which it belongs.

**PARAMETERS**
* `rigidBody` ([rigidBody](rigid_body.md))

---
### World:getDebugRenderer()
Return a reference to the Debug Renderer of the world.

**RETURN**
* ([DebugRenderer](debug_renderer.md))

---
### World:raycast(ray, cb, categoryMaskBits)
Ray cast method.

**PARAMETERS**
* `ray` ([Ray](ray.md))
* `cb` ([RaycastCallback](raycast_info.md))
* `categoryMaskBits` (number|nil)

---
### World:testOverlap2Bodies(body1, body2)
Return true if two bodies overlap (collide) 

**PARAMETERS**
* `body1` ([CollisionBody](collision_body.md))
* `body2` ([CollisionBody](collision_body.md))

**RETURN**
* (bool)

---
### World:testOverlapBodyList(body) 
Report all the bodies that overlap (collide) with the body in parameter.

**PARAMETERS**
* `body` ([CollisionBody](collision_body.md))

**RETURN**
* ([OverlapPair](#overlappair)[])

---
### World:testOverlapList()
Report all the bodies that overlap (collide) in the world.

**RETURN**
* ([OverlapPair](#overlappair)[])

---
### World:testCollision2Bodies(body1, body2)
Test collision and report contacts between two bodies.

**PARAMETERS**
* `body1` ([CollisionBody](collision_body.md))
* `body2` ([CollisionBody](collision_body.md))

**RETURN**
* ([ContactPair](#contactpair)|nil)

---
### World:testCollisionBodyList(body)
Test collision and report all the contacts involving the body in parameter.

**PARAMETERS**
* `body` ([CollisionBody](collision_body.md))

**RETURN**
* ([ContactPair](#contactpair)[])

---
### World:testCollisionList()
Test collision and report contacts between each colliding bodies in the world.

**RETURN**
* ([ContactPair](#contactpair)[])

---
### World:setEventListener(listener)
Set an event listener object to receive events callbacks.

**PARAMETERS**
* `listener` ([EventListener](#eventlistener)|nil)

---
### World:createJoint(jointInfo)
Create a joint between two bodies in the world and return a new joint.

**PARAMETERS**
* `jointInfo` ([JointInfo](joints/joint_info.md))

**RETURN**
* ([Joint](joints/joint.md))
