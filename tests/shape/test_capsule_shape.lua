local UTILS = require "tests.test_utils"

return function()
	describe("CapsuleShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
		end)
		after(function() end)


		test("create/destroy capsule", function()
			local shape = rp3d.createCapsuleShape(1,2)
			assert_not_nil(shape)
			assert_equal( rp3d.CollisionShapeName.CAPSULE,shape:getName())

			rp3d.destroyCapsuleShape(shape)
			local status, error = pcall(rp3d.destroyCapsuleShape,shape)
			assert_false(status)
			UTILS.test_error(error,"rp3d::CollisionShape was destroyed")
		end)

		test("Set/Get Radius()", function()
			local shape = rp3d.createCapsuleShape(1,2)
			UTILS.test_method_get_set(shape, "Radius",
					{ float = true,
					  values = {1,0.1,2,5 }
					})
			rp3d.destroyCapsuleShape(shape)
		end)

		test("Set/Get Height()", function()
			local shape = rp3d.createCapsuleShape(1,2)
			UTILS.test_method_get_set(shape, "Height",
					{ float = true,
					  values = {1,0.1,2,5 }
					})
			rp3d.destroyCapsuleShape(shape)
		end)


	end)
end
