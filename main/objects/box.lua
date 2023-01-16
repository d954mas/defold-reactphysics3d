local CLASS = require "libs.middleclass"

---@class GameBox
local Box = CLASS.class("Box")

---@param world Rp3dPhysicsWorld
function Box:initialize(rigid_body, size, world)
	self.rigid_body = rigid_body
	self.size = vmath.vector3(size)
	self.world = assert(world)
	self.shape = rp3d.createBoxShape(self.size/2)
	self.collection = collectionfactory.create("/factory#box", nil, nil, nil, self.size)
	self.go = {
		root = msg.url(self.collection["/root"]),
		mesh = nil
	}
	self.go.mesh = msg.url(self.go.root.socket,self.go.root.path,"mesh")
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

end

function Box:update_transform()
	local transform = self.body:getTransform()
	go.set_position(transform.position, self.go.root)
	go.set_rotation(transform.quat, self.go.root)
end

function Box:dispose()
	if (self.rigid_body) then
		self.world:destroyRigidBody(self.body)
	else
		self.world:destroyCollisionBody(self.body)
	end
	go.delete(self.go.root, true)
	rp3d.destroyBoxShape(self.shape)
end

return Box