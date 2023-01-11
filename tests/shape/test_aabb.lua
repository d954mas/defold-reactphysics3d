local UTILS = require "tests.test_utils"

return function()
	describe("CollsionShape", function()
		before(function()
			UTILS.set_env(getfenv(1))

		end)
		after(function()

		end)

		test("getAABB()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB(pos, quat)
			assert_equal("rp3d::AABB", tostring(aabb):sub(1, 10))
			rp3d.destroyBoxShape(box)
		end)


	end)
end
