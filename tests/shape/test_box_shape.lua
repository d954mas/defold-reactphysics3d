local UTILS = require "tests.test_utils"

return function()
	describe("BoxShape", function()
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
			UTILS.test_error(error,"rp3d::CollisionShape was destroyed")
		end)

		test("Set/Get HalfExtents()", function()
			local w = rp3d.createPhysicsWorld()
			local shape = rp3d.createBoxShape(vmath.vector3(1,1,1))
			UTILS.test_method_get_set(shape, "HalfExtents",
					{ v3 = true,
					  values = { vmath.vector3(1, 1, 1), vmath.vector3(1, 2, 1), vmath.vector3(2, 2, 2) }
					})
			rp3d.destroyBoxShape(shape)
			rp3d.destroyPhysicsWorld(w)
		end)




	end)
end
