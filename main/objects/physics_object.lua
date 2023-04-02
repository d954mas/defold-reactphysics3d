local CLASS = require "libs.middleclass"

---@class GamePhysObject
---@field body Rp3dRigidBody
local Body = CLASS.class("PhysObject")

---@param world Rp3dPhysicsWorld
function Body:initialize(world)
	self.world = assert(world)
	self.color = vmath.vector4(1)
	self.color_sleeping = vmath.vector4(1, 0, 0, 1)
	self.colors = {
		objectColorDemo = vmath.vector4(0.0, 0.68, 0.99, 1.0),
		floorColorDemo = vmath.vector4(0.7, 0.7, 0.7, 1.0),
		sleepingColorDemo = vmath.vector4(1.0, 0.0, 0.0, 1.0),
		selectedObjectColorDemo = vmath.vector4(0.09, 0.88, 0.09, 1.0),
	}
	self:setColor(self.colors.objectColorDemo)
	self:setColorSleeping(self.colors.sleepingColorDemo)
	self.selected = false
end

function Body:setSelected(selected)
	self.selected = selected
end

function Body:setEnabled(enable)
	msg.post(self.go.root, enable and "enable" or "disable")
end




function Body:setColor(color)
	self.color = vmath.vector4(color)
end
function Body:setColorSleeping(color)
	self.color_sleeping = vmath.vector4(color)
end

---@param transform Rp3dTransform
function Body:setTransform(transform)
	self.body:setTransform(transform)
	if (self.body:isRigidBody()) then
		self.body:setLinearVelocity(vmath.vector3())
		self.body:setAngularVelocity(vmath.vector3())
	end
	self:updateTransform()
end

function Body:updateTransform()
	local transform = self.body:getTransform()
	if (self.go) then
		go.set_position(transform.position, self.go.root)
		go.set_rotation(transform.quat, self.go.root)
	end
end

function Body:updateColor()
	if (self.go and self.go.mesh) then
		local color = self.color
		if (self.body:isRigidBody() and self.body:isSleeping()) then
			color = self.color_sleeping
		end
		if(self.selected)then
			color = self.colors.selectedObjectColorDemo
		end
		go.set(self.go.mesh, "tint", color)
	end
end

function Body:dispose()
	if (self.body:isRigidBody()) then
		self.world:destroyRigidBody(self.body)
	else
		self.world:destroyCollisionBody(self.body)
	end
	if (self.go and self.go.root) then
		go.delete(self.go.root, true)
		self.go = nil
	end

end

return Body