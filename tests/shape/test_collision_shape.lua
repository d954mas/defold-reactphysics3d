local UTILS = require "tests.test_utils"


local shapes = nil
local function init_shapes()
	shapes = {
		box = rp3d.createBoxShape(vmath.vector3(1,1,1))
	}
end

local function dispose_shapes()
	rp3d.destroyBoxShape(shapes.box)

	shapes = nil

end

return function()
	describe("CollsionShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
			init_shapes()
		end)
		after(function()
			dispose_shapes()
		end)


		test("getName", function()
			assert_equal(shapes.box:getName(), rp3d.CollisionShapeName.BOX)
		end)




	end)
end
