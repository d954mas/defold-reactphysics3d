local CLASS = require "libs.middleclass"

local Box = CLASS.class("Box")

function Box:initialize(size)
	self.size = vmath.vector3(size)

	local shape = rp3d.createBoxShape(self.size)

end


return Box