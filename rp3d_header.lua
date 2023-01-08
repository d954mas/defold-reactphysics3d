rp3d = {}


--[[




decimal defaultSleepLinearVelocity;


decimal defaultSleepAngularVelocity;


decimal cosAngleSimilarContactManifold;

--]]

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

--Create and return an instance of PhysicsWorld.
---@param settings Rp3dWorldSettings
---@return Rp3dPhysicsWorld
function rp3d.createPhysicsWorld(settings) end

---@param world Rp3dPhysicsWorld
function rp3d.destroyPhysicsWorld(world) end