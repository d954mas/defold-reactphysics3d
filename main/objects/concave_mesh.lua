local CLASS = require "libs.middleclass"
local PhysObject = require "main.objects.physics_object"

---@class GameConcaveMesh:GamePhysObject
local Box = CLASS.class("ConcaveMesh", PhysObject)

---@param world Rp3dPhysicsWorld
function Box:initialize(rigid_body, mesh,factory_url, world)
	PhysObject.initialize(self, world)
	self.rigid_body = rigid_body
	self.mesh = mesh
	self.shape = rp3d.createConcaveMeshShape(mesh)
	self.scale = vmath.vector3(1)
	self.collection = collectionfactory.create(factory_url, nil, nil, nil, self.scale)
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

function Box:setScale(scale,go_scale)
	self.shape:setScale(scale)
	self.scale = scale
	go.set_scale(go_scale,self.go.root)
end

function Box:dispose()
	PhysObject.dispose(self)
	rp3d.destroyConcaveMeshShape(self.shape)
end

return Box