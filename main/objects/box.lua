local CLASS = require "libs.middleclass"

local Box = CLASS.class("Box")

---@param world Rp3dPhysicsWorld
function Box:initialize(rigid_body, size, world)
	self.rigid_body = rigid_body
	self.size = vmath.vector3(size)
	self.world = assert(world)
	self.shape = rp3d.createBoxShape(self.size)

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

function Box:dispose()
	if(self.rigid_body)then
		self.world:destroyRigidBody(self.body)
	else
		self.world:destroyCollisionBody(self.body)
	end
	rp3d.destroyBoxShape(self.shape)
end

return Box