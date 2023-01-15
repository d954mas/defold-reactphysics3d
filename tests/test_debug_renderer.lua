local UTILS = require "tests.test_utils"

---@type Rp3dPhysicsWorld
local w

return function()
	describe("DebugRenderer", function()
		before(function()
			UTILS.set_env(getfenv(1))
			w = rp3d.createPhysicsWorld()
		end)
		after(function()
			rp3d.destroyPhysicsWorld(w)
		end)

		test("create()", function()
			local renderer = w:getDebugRenderer();
			assert_not_nil(renderer)
		end)

		test("destroy world", function()
			local world = rp3d.createPhysicsWorld()
			local renderer = world:getDebugRenderer();
			assert_not_nil(renderer)
			rp3d.destroyPhysicsWorld(world)
			local status, error = pcall(renderer.setIsDebugItemDisplayed,renderer,rp3d.DebugRenderer.DebugItem.COLLIDER_AABB,true)
			assert_false(status)
			assert_equal(error,"rp3d::DebugRenderer was destroyed")
		end)

		test("toString()", function()
			local renderer = w:getDebugRenderer();
			assert_equal(tostring(renderer):sub(1,19), "rp3d::DebugRenderer")
		end)




	end)
end
