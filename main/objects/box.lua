local CLASS = require "libs.middleclass"
local PhysObject = require "main.objects.physics_object"

---@class GameBox:GamePhysObject
local Box = CLASS.class("Box", PhysObject)

---@param world Rp3dPhysicsWorld
function Box:initialize(rigid_body, size, world)
	PhysObject.initialize(self,world)
	self.rigid_body = rigid_body
	self.size = vmath.vector3(size)
	self.shape = rp3d.createBoxShape(self.size / 2)
	self.collection = collectionfactory.create("/factory#box", nil, nil, nil, self.size)
	self.go = {
		root = msg.url(self.collection["/root"]),
		mesh = nil
	}
	self.go.mesh = msg.url(self.go.root.socket, self.go.root.path, "mesh")
	local transform_identity = {
		position = vmath.vector3(),
		quat = vmath.quat()
	}
	if (rigid_body) then
		self.body = world:createRigidBody(transform_identity);
		self.collider = self.body:addCollider(self.shape, transform_identity);
		self.body:updateMassPropertiesFromColliders();
	else
		self.body = world:createCollisionBody(transform_identity);
		self.collider = self.body:addCollider(self.shape, transform_identity);
	end
	self.body:setUserData(self)

end

function Box:dispose()
	PhysObject.dispose(self)
	rp3d.destroyBoxShape(self.shape)
end

return Box