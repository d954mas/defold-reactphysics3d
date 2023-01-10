local UTILS = require "tests.test_utils"

return function()
	describe("World", function()
		before(function()
			UTILS.set_env(getfenv(1))
		end)
		after(function() end)

		test("create/destroy box", function()
			local shape = rp3d.createBoxShape(vmath.vector3(1,1,1))
			assert_not_nil(shape)
			assert_equal( rp3d.CollisionShapeName.BOX,shape:getName())

			rp3d.destroyBoxShape(shape)
			local status, error = pcall(rp3d.destroyBoxShape,shape)
			assert_false(status)
			assert_equal(error,"Can't use destroyed collision shape")
		end)




	end)
end
