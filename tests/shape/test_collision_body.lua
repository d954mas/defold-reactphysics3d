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

		test("world destroyed.Destroy collision bodies", function()
			local world = rp3d.createPhysicsWorld()
			local collision_body  = world:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
			local rigid_body  = world:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_false(collision_body:isRigidBody())
			assert_true(rigid_body:isRigidBody())
			rp3d.destroyPhysicsWorld(world)


			local status, error = pcall(collision_body.isRigidBody,collision_body)
			assert_false(status)
			assert_equal(error,"rp3d::CollisionBody was destroyed")

			status, error = pcall(rigid_body.isRigidBody,rigid_body)
			assert_false(status)
			assert_equal(error,"rp3d::CollisionBody was destroyed")
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
