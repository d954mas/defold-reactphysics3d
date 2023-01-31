local CLASS = require "libs.middleclass"
local PhysObject = require "main.objects.physics_object"

---@class GameDumbBell:GamePhysObject
local Dumbbell = CLASS.class("GameDumbBell", PhysObject)

---@param world Rp3dPhysicsWorld
function Dumbbell:initialize(rigid_body, world)
	PhysObject.initialize(self, world)
	self.rigid_body = rigid_body
	self.collection = collectionfactory.create("/factory#dumbbell", nil, nil, nil, 1)
	self.distanceBetweenSphere = 8
	self.shape_sphere = rp3d.createSphereShape(1.5)
	self.shape_capsule = rp3d.createCapsuleShape(0.5, 7)

	self.go = {
		root = msg.url(self.collection["/root"]),
		mesh = nil
	}
	self.go.mesh = msg.url(self.go.root.socket, self.go.root.path, "mesh")
	local transform_identity = {
		position = vmath.vector3(),
		quat = vmath.quat()
	}
	local transformSphereShape1 = {
		position = vmath.vector3(0, self.distanceBetweenSphere / 2.0, 0),
		quat = vmath.quat()
	}
	local transformSphereShape2 = {
		position = vmath.vector3(0, -self.distanceBetweenSphere / 2.0, 0),
		quat = vmath.quat()
	}
	local transformCylinderShape1 = {
		position = vmath.vector3(0, 0, 0),
		quat = vmath.quat()
	}
	if (rigid_body) then
		self.body = world:createRigidBody(transform_identity);
		self.sphere1 = self.body:addCollider(self.shape_sphere, transformSphereShape1);
		self.sphere2 = self.body:addCollider(self.shape_sphere, transformSphereShape2);
		self.capsule = self.body:addCollider(self.shape_capsule, transformCylinderShape1);
		self.sphere1:setMaterialMassDensity(2)
		self.sphere2:setMaterialMassDensity(2)
		self.body:updateMassPropertiesFromColliders();
	else
		self.body = world:createCollisionBody(transform_identity);
		self.sphere1 = self.body:addCollider(self.shape_sphere, transformSphereShape1);
		self.sphere2 = self.body:addCollider(self.shape_sphere, transformSphereShape2);
		self.capsule = self.body:addCollider(self.shape_capsule, transformCylinderShape1);

	end
	self.body:setUserData(self)

end

function Dumbbell:dispose()
	PhysObject.dispose(self)
	rp3d.destroyCapsuleShape(self.shape_capsule)
	rp3d.destroySphereShape(self.shape_sphere)
end

return Dumbbell