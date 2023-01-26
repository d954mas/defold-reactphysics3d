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

local function assert_two_vectors(v1_result,v2_result,v1,v2)
	assert_equal_v3(v1_result,v1)
	assert_equal_v3(v2_result,v2)
end

return function()
	describe("ConvexShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
			setfenv(assert_two_vectors,getfenv(1))
			init_shapes()
		end)
		after(function()
			dispose_shapes()
		end)


		test("getMargin()", function()
			assert_equal(shapes.box:getMargin(),0)
		end)

	end)
end
