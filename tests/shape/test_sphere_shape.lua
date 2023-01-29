local UTILS = require "tests.test_utils"

return function()
	describe("SphereShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
		end)
		after(function() end)


		test("create/destroy sphere", function()
			local shape = rp3d.createSphereShape(1)
			assert_not_nil(shape)
			assert_equal( rp3d.CollisionShapeName.SPHERE,shape:getName())

			rp3d.destroySphereShape(shape)
			local status, error = pcall(rp3d.destroySphereShape,shape)
			assert_false(status)
			UTILS.test_error(error,"rp3d::CollisionShape was destroyed")
		end)

		test("Set/Get Radius()", function()
			local shape = rp3d.createSphereShape(1)
			UTILS.test_method_get_set(shape, "Radius",
					{ float = true,
					  values = {1,0.1,2,5 }
					})
			rp3d.destroySphereShape(shape)
		end)


	end)
end
