local UTILS = require "tests.test_utils"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dCollisionBody
local bodies = {}
return function()
	describe("CollisionBody", function()
		before(function()
			UTILS.set_env(getfenv(1))
			w = rp3d.createPhysicsWorld()
			bodies[1] = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
			bodies[2] = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
		end)
		after(function()
			--w:destroyCollisionBody(bodies[1])
		--	w:destroyRigidBody(bodies[2])
			rp3d.destroyPhysicsWorld(w)
		end)

		test("getEntityId()", function()
			for _,body in ipairs(bodies)do
				assert_type(body:getEntityId(),"number")
			end
		end)

		test("toString()", function()
			assert_equal(tostring(bodies[1]):sub(1,19),"rp3d::CollisionBody")
			assert_equal(tostring(bodies[2]):sub(1,15),"rp3d::RigidBody")
		end)



	end)
end
