local CLASS = require "libs.middleclass"

local Box = CLASS.class("Box")

function Box:initialize(rigid_body,size)
	self.size = vmath.vector3(size)
	self.shape = rp3d.createBoxShape(self.size)

end

function  Box:dispose()
	rp3d.destroyBoxShape(self.shape)
end


return Box