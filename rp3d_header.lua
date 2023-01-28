rp3d = {}

---@class Rp3dWorldSettings
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

--The ray goes from point1 to point1 + maxFraction * (point2 - point1).
--The points are specified in world-space coordinates.
---@class Rp3dRay
local Rp3dRay = {
	point1 = vmath.vector3(),
	point2 = vmath.vector3(),
	maxFraction = 0 --[0-1] if nil use 1.
}

---@class Rp3dRaycastInfo
---@field worldPoint vector3 Hit point in world-space coordinates.
---@field worldNormal vector3 Surface normal at hit point in world-space coordinates.
---@field hitFraction number Fraction distance of the hit point between point1 and point2 of the ray The hit point "p" is such that p = point1 + hitFraction * (point2 - point1)
---@field meshSubpart number Mesh subpart index that has been hit (only used for triangles mesh and -1 otherwise)
---@field triangleIndex number Hit triangle index (only used for triangles mesh and -1 otherwise)
---@field body Rp3dCollisionBody
---@field collider Rp3dCollider
local Rp3dRaycastInfo = {}

---@class Rp3dOverlapPair
---@field collider1 Rp3dCollider
---@field collider2 Rp3dCollider
---@field body1 Rp3dCollisionBody
---@field body2 Rp3dCollisionBody
---@field eventType string OverlapPair.EventType
local Rp3dOverlapPair = {}

---@class Rp3dContactPair
---@field collider1 Rp3dCollider
---@field collider2 Rp3dCollider
---@field body1 Rp3dCollisionBody
---@field body2 Rp3dCollisionBody
---@field eventType string ContactPair.EventType
---@field contacts Rp3dContactPairContact[]
local Rp3dContactPair = {}

---@class Rp3dContactPairContact
---@field penetrationDepth  number
---@field worldNormal vector3
---@field localPointOnCollider1 vector3
---@field localPointOnCollider2 vector3
local Rp3dContactPairContact = {}

---@class Rp3dHalfEdgeStructureFace
---@field edgeIndex number
---@field faceVertices number[]
local Rp3dHalfEdgeStructureFace = {}

---@class Rp3dHalfEdgeStructureVertex
---@field edgeIndex number
---@field vertexPointIndex number
local Rp3dHalfEdgeStructureVertex = {}

---@class Rp3dTransform
local Rp3dTransform = {
	position = vmath.vector3(),
	quat = vmath.quat(),
}

---@class Rp3dMaterial
local Rp3dMaterial = {
	bounciness = 0,
	frictionCoefficient = 0,
	massDensity = 0,
}

---@class Rp3dCollider
local Collider = {}

---@return number
function Collider:getEntityId() end

---@return Rp3dCollisionShape
function Collider:getCollisionShape() end

---@return Rp3dCollisionBody
function Collider:getBody() end

---@return table|nil
function Collider:getUserData() end

---@param userdata table|nil
function Collider:setUserData(userdata) end

--Return the local to parent body transform.
---@return Rp3dTransform
function Collider:getLocalToBodyTransform() end


--Set the local to parent body transform.
---@param transform Rp3dTransform
function Collider:setLocalToBodyTransform(transform) end

--Return the local to world transform.
---@return Rp3dTransform
function Collider:getLocalToWorldTransform() end

--Return the AABB of the collider in world-space.
---@return Rp3dAABB
function Collider:getWorldAABB() end

--return true if a point is inside the collision shape.
---@return boolean
---@param worldPoint vector3
function Collider:testPointInside(worldPoint) end

--Test if the collider overlaps with a given AABB.
---@return boolean
---@param worldAABB Rp3dAABB
function Collider:testAABBOverlap(worldAABB) end

function Collider:raycast(ray) end

--Return the broad-phase id.
---@return number
function Collider:getBroadPhaseId() end

function Collider:getCollideWithMaskBits() end

--	Set the collision bits mask.
---@param collideWithMaskBits number
function Collider:setCollideWithMaskBits(collideWithMaskBits) end

--Return the collision category bits.
---@return number
function Collider:getCollisionCategoryBits() end

--Set the collision category bits.
---@param collisionCategoryBits number
function Collider:setCollisionCategoryBits(collisionCategoryBits) end

--Return true if the collider is a trigger.
---@return boolean
function Collider:getIsTrigger() end

--Set whether the collider is a trigger.
---@param isTrigger boolean
function Collider:setIsTrigger(isTrigger) end


--	Return material properties of the collider.
---@return Rp3dMaterial
function Collider:getMaterial() end

--Set a new material for this collider.
---@param material Rp3dMaterial
function Collider:setMaterial(material) end

---@return number
function Collider:getMaterialBounciness() end

---@param bounciness number
function Collider:setMaterialBounciness(bounciness) end

---@return number
function Collider:getMaterialFrictionCoefficient() end

---@param frictionCoefficient number
function Collider:setMaterialFrictionCoefficient(frictionCoefficient) end

---@return number
function Collider:getMaterialMassDensity() end

---@param massDensity number
function Collider:setMaterialMassDensity(massDensity) end

---@class Rp3dCollisionBody
local CollisionBody = {}

---@return number
function CollisionBody:getEntityId() end

---@return boolean
function CollisionBody:isRigidBody() end


--Return true if the body is active.
---@return boolean
function CollisionBody:isActive() end


--Return a table or nil user data attached to this body.
---@return table|nil
function CollisionBody:getUserData() end

--Attach user data to this body.
---@param userdata table|nil
function CollisionBody:setUserData(userdata) end

--Return the current position and orientation.
---@return Rp3dTransform
function CollisionBody:getTransform() end

--Set the current position and orientation.
---@param transform Rp3dTransform
function CollisionBody:setTransform(transform) end

--Create a new collider and add it to the body.
--A collider is an object with a collision shape that is attached to a body.
--It is possible to attach multiple colliders to a given body.
--You can use the returned collider to get and set information about the corresponding collision shape for that body.
---@param collisionShape Rp3dCollisionShape
---@param transform Rp3dTransform
---@return Rp3dCollider
function CollisionBody:addCollider(collisionShape, transform) end

---@return Rp3dCollider
---@param index number [0,size)
function CollisionBody:getCollider(index) end

--Return the number of colliders associated with this body.
---@return number
function CollisionBody:getNbColliders() end

---@param collider Rp3dCollider
function CollisionBody:removeCollider(collider) end

--Return true if a point is inside the collision body.
---@param worldPoint vector3 The point to test (in world-space coordinates)
---@return boolean
function CollisionBody:testPointInside(worldPoint) end


--Raycast method with feedback information.
--The method returns the closest hit among all the collision shapes of the body.
---@param ray Rp3dRay
---@return Rp3dRaycastInfo|nil nil if no hit point
function CollisionBody:raycast(ray) end

--Test if the collision body overlaps with a given AABB
---@param aabb Rp3dAABB
---@return boolean
function CollisionBody:testAABBOverlap(aabb) end

--Compute and return the AABB of the body by merging all colliders AABBs.
---@return Rp3dAABB
function CollisionBody:getAABB() end

--Return the world-space coordinates of a point given the local-space coordinates of the body.
---@param localPoint vector3
---@return vector3
function CollisionBody:getWorldPoint(localPoint) end

--Return the world-space vector of a vector given in local-space coordinates of the body.
---@param localVector vector3
---@return vector3
function CollisionBody:getWorldVector(localVector) end

--Return the body local-space coordinates of a point given in the world-space coordinates.
---@param worldPoint vector3
---@return vector3
function CollisionBody:getLocalPoint(worldPoint) end

--Return the body local-space coordinates of a vector given in the world-space coordinates.
---@param worldVector vector3
---@return vector3
function CollisionBody:getLocalVector(worldVector) end

--	Set whether or not the body is active.
---@param isActive boolean
function CollisionBody:setIsActive(isActive) end

--Return true if the body is active.
---@return boolean
function CollisionBody:isActive() end

---@class Rp3dRigidBody:Rp3dCollisionBody
local RigidBody = {}

--Compute and set the local-space center of mass of the body using its colliders.
function RigidBody:updateLocalCenterOfMassFromColliders() end

--Compute and set the local-space inertia tensor of the body using its colliders.
function RigidBody:updateLocalInertiaTensorFromColliders() end

--Compute and set the mass of the body using its colliders.
function RigidBody:updateMassFromColliders() end

--Compute and set the center of mass, the mass and the local-space inertia tensor of the body using its colliders.
function RigidBody:updateMassPropertiesFromColliders() end

---@param type string rp3d.BodyType
function RigidBody:setType(type) end

---@return string
function RigidBody:getType() end

--Return the mass of the body.
---@return number
function RigidBody:getMass() end

--Set the mass of the rigid body.
---@param mass number
function RigidBody:setMass(mass) end

--Return the linear velocity.
---@return vector3
function RigidBody:getLinearVelocity() end

--Set the linear velocity of the body.
---@param linearVelocity vector3
function RigidBody:setLinearVelocity(linearVelocity) end

--Return the angular velocity.
---@return vector3
function RigidBody:getAngularVelocity() end

--Set the angular velocity.
---@param angularVelocity vector3
function RigidBody:setAngularVelocity(angularVelocity) end

--Return the local inertia tensor of the body (in body coordinates)
---@return vector3
function RigidBody:getLocalInertiaTensor() end

--	Set the local inertia tensor of the body (in body coordinates)
---@param inertiaTensorLocal vector3
function RigidBody:setLocalInertiaTensor(inertiaTensorLocal) end

--Return the center of mass of the body (in local-space coordinates)
---@return vector3
function RigidBody:getLocalCenterOfMass() end

--Set the center of mass of the body (in local-space coordinates)
---@param centerOfMass vector3
function RigidBody:setLocalCenterOfMass(centerOfMass) end

--Return true if the gravity needs to be applied to this rigid body.
---@return boolean
function RigidBody:isGravityEnabled() end

--Set the variable to know if the gravity is applied to this rigid body.
---@param isEnabled boolean
function RigidBody:enableGravity(isEnabled) end

--Set the variable to know whether or not the body is sleeping.
---@param isSleeping boolean
function RigidBody:setIsSleeping(isSleeping) end

--Return whether or not the body is sleeping.
---@return boolean
function RigidBody:isSleeping() end

--Return the linear velocity damping factor.
---@return number
function RigidBody:getLinearDamping() end

--Set the linear damping factor.
---@param linearDamping number
function RigidBody:setLinearDamping(linearDamping) end

--Return the angular velocity damping factor.
---@return number
function RigidBody:getAngularDamping() end

--Set the angular damping factor.
---@param angularDamping number
function RigidBody:setAngularDamping(angularDamping) end



--Return the lock translation factor.
---@return vector3
function RigidBody:getLinearLockAxisFactor() end

--Set the linear lock factor.
---@param linearLockAxisFactor vector3
function RigidBody:setLinearLockAxisFactor(linearLockAxisFactor) end

--Return the lock rotation factor.
---@return vector3
function RigidBody:getAngularLockAxisFactor() end

--Set the lock rotation factor.
---@param angularLockAxisFactor vector3
function RigidBody:setAngularLockAxisFactor(angularLockAxisFactor) end


--Manually apply an external force (in local-space) to the body at its center of mass.
---@param force vector3
function RigidBody:applyLocalForceAtCenterOfMass(force) end

--Manually apply an external force (in world-space) to the body at its center of mass.
---@param force vector3
function RigidBody:applyWorldForceAtCenterOfMass(force) end


--Manually apply an external force (in local-space) to the body at a given point (in local-space).
---@param force vector3
---@param point vector3
function RigidBody:applyLocalForceAtLocalPosition(force, point) end

--Manually apply an external force (in world-space) to the body at a given point (in local-space).
---@param force vector3
---@param point vector3
function RigidBody:applyWorldForceAtLocalPosition(force, point) end

--Manually apply an external force (in local-space) to the body at a given point (in world-space).
---@param force vector3
---@param point vector3
function RigidBody:applyLocalForceAtWorldPosition(force, point) end

--Manually apply an external force (in world-space) to the body at a given point (in world-space).
---@param force vector3
---@param point vector3
function RigidBody:applyWorldForceAtWorldPosition(force, point) end

--Manually apply an external torque to the body (in local-space).
---@param torque vector3
function RigidBody:applyLocalTorque(torque) end

--Manually apply an external torque to the body (in world-space).
---@param torque vector3
function RigidBody:applyWorldTorque(torque) end

--Reset the manually applied force to zero.
function RigidBody:resetForce() end

--Reset the manually applied torque to zero.
function RigidBody:resetTorque() end

--Return the total manually applied force on the body (in world-space)
---@return vector3
function RigidBody:getForce() end

--	Return the total manually applied torque on the body (in world-space)
---@return vector3
function RigidBody:getTorque() end

--Return whether or not the body is allowed to sleep.
---@return boolean
function RigidBody:isAllowedToSleep() end

--Set whether or not the body is allowed to go to sleep.
---@param isAllowedToSleep boolean
function RigidBody:setIsAllowedToSleep(isAllowedToSleep) end

---@class Rp3dDebugRenderer
local DebugRenderer = {}

---@param item string rp3d.DebugRenderer.DebugItem
---@return boolean
function DebugRenderer:getIsDebugItemDisplayed(item) end

---@param item string rp3d.DebugRenderer.DebugItem
---@param isDisplayed boolean
function DebugRenderer:setIsDebugItemDisplayed(item, isDisplayed) end

---@return number
function DebugRenderer:getContactPointSphereRadius() end

---@param radius number
function DebugRenderer:setContactPointSphereRadius(radius) end

---@return number
function DebugRenderer:getContactNormalLength() end

---@param length number
function DebugRenderer:setContactNormalLength(length) end

---post draw_line messages to render
function DebugRenderer:draw() end

---@class Rp3dPhysicsWorld
local PhysicsWorld = {}


--[[
CollisionDispatch & 	getCollisionDispatch ()
	 Get the collision dispatch configuration.

void 	raycast (const Ray &ray, RaycastCallback *raycastCallback, unsigned short raycastWithCategoryMaskBits=0xFFFF) const
	 Ray cast method.

bool 	testOverlap (CollisionBody *body1, CollisionBody *body2)
	 Return true if two bodies overlap (collide)

void 	testOverlap (CollisionBody *body, OverlapCallback &overlapCallback)
	 Report all the bodies that overlap (collide) with the body in parameter.

void 	testOverlap (OverlapCallback &overlapCallback)
	 Report all the bodies that overlap (collide) in the world.

void 	testCollision (CollisionBody *body1, CollisionBody *body2, CollisionCallback &callback)
	 Test collision and report contacts between two bodies.

void 	testCollision (CollisionBody *body, CollisionCallback &callback)
	 Test collision and report all the contacts involving the body in parameter.

void 	testCollision (CollisionCallback &callback)
	 Test collision and report contacts between each colliding bodies in the world.

MemoryManager & 	getMemoryManager ()
	 Return a reference to the memory manager of the world.

AABB 	getWorldAABB (const Collider *collider) const
	 Return the current world-space AABB of given collider.

Joint * 	createJoint (const JointInfo &jointInfo)
	 Create a joint between two bodies in the world and return a pointer to the new joint.

void 	destroyJoint (Joint *joint)
	 Destroy a joint.
void 	setEventListener (EventListener *eventListener)
	 Set an event listener object to receive events callbacks.

uint32 	getNbCollisionBodies () const
	 Return the number of CollisionBody in the physics world.

const CollisionBody * 	getCollisionBody (uint32 index) const
	 Return a constant pointer to a given CollisionBody of the world.

CollisionBody * 	getCollisionBody (uint32 index)
	 Return a pointer to a given CollisionBody of the world.


const RigidBody * 	getRigidBody (uint32 index) const
	 Return a constant pointer to a given RigidBody of the world.

RigidBody * 	getRigidBody (uint32 index)
	 Return a pointer to a given RigidBody of the world.

--]]

--Return the name of the world.
function PhysicsWorld:getName() end

--Return the gravity vector of the world.
---@return vector3
function PhysicsWorld:getGravity() end

--Get the number of iterations for the velocity constraint solver.
---@return number
function PhysicsWorld:getNbIterationsVelocitySolver() end

--Get the number of iterations for the position constraint solver.
---@return number
function PhysicsWorld:getNbIterationsPositionSolver() end

--Enable/Disable the sleeping technique.
---@param isSleepingEnabled bool
function PhysicsWorld:enableSleeping(isSleepingEnabled) end

--Return true if the sleeping technique is enabled.
---@return bool
function PhysicsWorld:isSleepingEnabled() end

--Return the time a body is required to stay still before sleeping.
---@return number
function PhysicsWorld:getTimeBeforeSleep() end

--Set the time a body is required to stay still before sleeping.
---@param timeBeforeSleep number
function PhysicsWorld:setTimeBeforeSleep(timeBeforeSleep) end

-- Return the current sleep linear velocity.
---@return number
function PhysicsWorld:getSleepLinearVelocity() end

-- 	Set the sleep linear velocity.
---@param sleepLinearVelocity number
function PhysicsWorld:setSleepLinearVelocity(sleepLinearVelocity) end

--Return the current sleep angular velocity.
---@return number
function PhysicsWorld:getSleepAngularVelocity() end

--Set the sleep angular velocity.
---@param sleepAngularVelocity number
function PhysicsWorld:setSleepAngularVelocity(sleepAngularVelocity) end

--Update the physics simulation.
---@param timeStep number
function PhysicsWorld:update(timeStep) end

--Set the number of iterations for the velocity constraint solver.
---@param nbIterations number
function PhysicsWorld:setNbIterationsVelocitySolver(nbIterations) end

--Set the number of iterations for the position constraint solver.
---@param nbIterations number
function PhysicsWorld:setNbIterationsPositionSolver(nbIterations) end

--the position correction technique used for contacts.
---@param technique number rp3d.ContactsPositionCorrectionTechnique
function PhysicsWorld:setContactsPositionCorrectionTechnique(technique) end


--Disable the joints for pair of sleeping bodies.
function PhysicsWorld:enableDisableJoints() end

--Set the gravity vector of the world.
---@param gravity vector3
function PhysicsWorld:setGravity(gravity) end

--Return if the gravity is on.
---@return  bool
function PhysicsWorld:isGravityEnabled() end

--Enable/Disable the gravity.
---@param isGravityEnabled bool
function PhysicsWorld:setIsGravityEnabled(isGravityEnabled) end

--Return the number of CollisionBody in the physics world.
---@return number
function PhysicsWorld:getNbCollisionBodies() end

--Return the number of RigidBody in the physics world.
---@return number
function PhysicsWorld:getNbRigidBodies() end

--Return true if the debug rendering is enabled.
---@return bool
function PhysicsWorld:getIsDebugRenderingEnabled() end

--Set to true if debug rendering is enabled.
---@param isEnabled bool
function PhysicsWorld:setIsDebugRenderingEnabled(isEnabled) end

--Create a collision body.
---@param transform Rp3dTransform
---@return Rp3dCollisionBody
function PhysicsWorld:createCollisionBody(transform) end

---Destroy a collision body.
---@param body Rp3dCollisionBody
function PhysicsWorld:destroyCollisionBody(body) end

--Create a rigid body into the physics world.
---@param transform Rp3dTransform
---@return Rp3dRigidBody
function PhysicsWorld:createRigidBody(transform) end

---Destroy a rigid body and all the joints which it belongs.
---@param body Rp3dRigidBody
function PhysicsWorld:destroyRigidBody(body) end

---@return Rp3dDebugRenderer
function PhysicsWorld:getDebugRenderer() end


--Return true if two bodies overlap (collide)
---@param body1 Rp3dCollisionBody
---@param body2 Rp3dCollisionBody
---@return boolean
function PhysicsWorld:testOverlap2Bodies(body1, body2) end

--Return all the bodies that overlap (collide) with the body in parameter.
--Use this method if you are not interested in contacts but if you simply want to know which bodies overlap with the body in parameter.
--If you want to get the contacts, you need to use the testCollisionBodyList() method instead.
---@param body1 Rp3dCollisionBody
---@return Rp3dOverlapPair[]
function PhysicsWorld:testOverlapBodyList(body1) end

--Return all the bodies that overlap (collide) in the world.
--Use this method if you are not interested in contacts but if you simply want to know which bodies overlap.
--If you want to get the contacts, you need to use the testCollision() method instead.
---@return Rp3dOverlapPair[]
function PhysicsWorld:testOverlapList() end


--Use this method if you only want to get all the contacts between two bodies.
--If you are not interested in the contacts but you only want to know if the bodies collide,
--you can use the testOverlap() method instead.
---@param body1 Rp3dCollisionBody
---@return Rp3dContactPair|nil
function PhysicsWorld:testCollision2Bodies() end


--Test collision and report all the contacts involving the body in parameter.
--Use this method if you only want to get all the contacts involving a given body.
--If you are not interested in the contacts but you only want to know if the bodies collide,
--you can use the testOverlap() method instead.
---@param body1 Rp3dCollisionBody
---@return Rp3dContactPair[]
function PhysicsWorld:testCollisionBodyList(body1) end

--Test collision and report contacts between each colliding bodies in the world.
--Use this method if you want to get all the contacts between colliding bodies in the world.
--If you are not interested in the contacts but you only want to know if the bodies collide,
--you can use the testOverlap() method instead.
---@return Rp3dContactPair[]
function PhysicsWorld:testCollisionList() end

--Return a CollisionBody of the world
---@param index number
---@return Rp3dCollisionBody
function PhysicsWorld:getCollisionBody(index) end

--Return a RigidBody of the world
---@param index number
---@return Rp3dRigidBody
function PhysicsWorld:getRigidBody(index) end

---@class Rp3dCollisionShape
local CollisionShape = {}

---@return string the type of the collision shape.
function CollisionShape:getType() end

---@return string the name of the collision shape.
function CollisionShape:getName() end

---@return bool true if the collision shape is a polyhedron.
function CollisionShape:isPolyhedron() end

---@return bool true if the collision shape is convex, false if it is concave.
function CollisionShape:isConvex() end


--Return the local bounds of the shape in x, y and z directions.
---@return vector3 min
---@return vector3 max
function CollisionShape:getLocalBounds() end

--Return the id of the shape.
---@return number
function CollisionShape:getId() end

--Return the local inertia tensor of the collision shapes.
---@param mass number
---@return vector3
function CollisionShape:getLocalInertiaTensor(mass) end

--Compute and return the volume of the collision shape.
---@return number
function CollisionShape:getVolume() end

--Compute the world-space AABB of the collision shape given a transform.
---@param transform Rp3dTransform
---@param quaternion quaternion
---@return Rp3dAABB
function CollisionShape:computeAABB(transform) end

---@class Rp3dConvexShape:Rp3dCollisionShape
local ConvexShape = {}

--Return the current object margin.
---@return number
function ConvexShape:getMargin() end

---@class Rp3dConvexPolyhedronShape:Rp3dConvexShape
local ConvexPolyhedronShape = {}

--Return the number of faces of the polyhedron.
---@return number
function ConvexPolyhedronShape:getNbFaces() end

--Return a given face of the polyhedron.
---@param faceIndex number
---@return Rp3dHalfEdgeStructureFace
function ConvexPolyhedronShape:getFace(faceIndex) end

--Return the number of vertices of the polyhedron.
---@return number
function ConvexPolyhedronShape:getNbVertices() end

--Return a given vertex of the polyhedron.
---@param vertexIndex number
---@return Rp3dHalfEdgeStructureVertex
function ConvexPolyhedronShape:getVertex(vertexIndex) end

--Return the position of a given vertex.
---@param vertexIndex number
---@return vector3
function ConvexPolyhedronShape:getVertexPosition(vertexIndex) end

--Return the normal vector of a given face of the polyhedron.
---@param faceIndex number
---@return vector3
function ConvexPolyhedronShape:getFaceNormal(faceIndex) end

---@class Rp3dBoxShape:Rp3dConvexPolyhedronShape
local BoxShape = {}

---@class Rp3dAABB
local Rp3dAABB = {}

--Return the center point.
---@return vector3
function Rp3dAABB:getCenter() end

--Return the minimum coordinates of the AABB.
---@return vector3
function Rp3dAABB:getMin() end

--Set the minimum coordinates of the AABB.
---@param vector3 number
function Rp3dAABB:setMin(min) end

--Return the maximum coordinates of the AABB.
---@return vector3
function Rp3dAABB:getMax() end

--Set the maximum coordinates of the AABB.
---@param max vector3
function Rp3dAABB:setMax(max) end

--Return the size of the AABB in the three dimension x, y and z.
---@return vector3
function Rp3dAABB:getExtent() end

--Inflate each side of the AABB by a given size.
---@param x number
---@param y number
---@param z number
function Rp3dAABB:inflate(x, y, z) end


--Return true if the current AABB is overlapping with the AABB in argument.
--Two AABBs overlap if they overlap in the three x, y and z axis at the same time.
---@param aabb Rp3dAABB
---@return bool
function Rp3dAABB:testCollision(aabb) end

--Return the volume of the AABB.
---@return number
function Rp3dAABB:getVolume() end

--Merge the AABB in parameter with the current one.
---@param aabb Rp3dAABB
function Rp3dAABB:mergeWithAABB(aabb) end

--Replace the current AABB with a new AABB that is the union of two AABBs in parameters.
---@param aabb1 Rp3dAABB
---@param aabb2 Rp3dAABB
function Rp3dAABB:mergeTwoAABBs(aabb1, aabb2) end

--Return true if the current AABB contains the AABB given in parameter.
---@param aabb Rp3dAABB
---@return bool
function Rp3dAABB:contains(aabb) end

--Return true if a point is inside the AABB.
---@param point vector3
---@return bool
function Rp3dAABB:containsPoint(point) end

--Return true if the AABB of a triangle intersects the AABB.
---@param trianglePoints vector3[] 3 points
---@return bool
function Rp3dAABB:testCollisionTriangleAABB(trianglePoints) end


--Return true if the ray intersects the AABB.
---@param rayOrigin vector3
---@param rayDirectionInv vector3 inverse 1 / rayDirection.x, 1 / rayDirection.y, 1 / rayDirection.z);
---@param rayMaxFraction number
---@return bool
function Rp3dAABB:testRayIntersect(rayOrigin, rayDirectionInv, rayMaxFraction) end

--Apply a scale factor to the AABB.
---@param scale vector3
function Rp3dAABB:applyScale(scale) end


--Compute the intersection of a ray and the AABB.
---@param ray Rp3dRay infinity ray. Ignore maxFraction. Ignore distance of ray
---@return nil|vector3
function Rp3dAABB:raycast(ray) end





--Create and return an instance of PhysicsWorld.
---@param settings Rp3dWorldSettings
---@return Rp3dPhysicsWorld
function rp3d.createPhysicsWorld(settings) end

---@param world Rp3dPhysicsWorld
function rp3d.destroyPhysicsWorld(world) end


--Create and return a box collision shape.
---@param halfExtents vector3
---@return Rp3dBoxShape
function rp3d.createBoxShape(halfExtents) end

--Destroy a box collision shape.
---@param boxShape Rp3dBoxShape
function rp3d.destroyBoxShape(boxShape) end

rp3d.ContactsPositionCorrectionTechnique = {
	BAUMGARTE_CONTACTS = "BAUMGARTE_CONTACTS",
	SPLIT_IMPULSES = "SPLIT_IMPULSES",
}

rp3d.CollisionShapeName = {
	TRIANGLE = "TRIANGLE", SPHERE = "SPHERE", CAPSULE = "CAPSULE",
	BOX = "BOX", CONVEX_MESH = "CONVEX_MESH", TRIANGLE_MESH = "TRIANGLE_MESH",
	HEIGHTFIELD = "HEIGHTFIELD"
}

rp3d.CollisionShapeType = {
	SPHERE = "SPHERE", CAPSULE = "CAPSULE",
	CONVEX_POLYHEDRON = "CONVEX_POLYHEDRON", CONCAVE_SHAPE = "CONCAVE_SHAPE"
}
--Enumeration for the type of a body
-- STATIC : A static body has infinite mass, zero velocity but the position can be
--          changed manually. A static body does not collide with other static or kinematic bodies.
-- KINEMATIC : A kinematic body has infinite mass, the velocity can be changed manually and its
--             position is computed by the physics engine. A kinematic body does not collide with
--             other static or kinematic bodies.
-- DYNAMIC : A dynamic body has non-zero mass, non-zero velocity determined by forces and its
--           position is determined by the physics engine. A dynamic body can collide with other
--           dynamic, static or kinematic bodies.
rp3d.BodyType = {
	STATIC = "STATIC",
	KINEMATIC = "KINEMATIC",
	DYNAMIC = "DYNAMIC"
}

rp3d.DebugRenderer = {
	DebugItem = {
		COLLIDER_AABB = "COLLIDER_AABB",
		COLLIDER_BROADPHASE_AABB = "COLLIDER_BROADPHASE_AABB",
		COLLISION_SHAPE = "COLLISION_SHAPE",
		CONTACT_POINT = "CONTACT_POINT",
		CONTACT_NORMAL = "CONTACT_NORMAL",
	},
}

rp3d.OverlapPair = {
	EventType = {
		OverlapStart = "OverlapStart",
		OverlapStay = "OverlapStay",
		OverlapExit = "OverlapExit",
	},
}

rp3d.ContactPair = {
	EventType = {
		ContactStart = "ContactStart",
		ContactStay = "ContactStay",
		ContactExit = "ContactExit",
	},
}



