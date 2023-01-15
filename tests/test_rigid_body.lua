local UTILS = require "tests.test_utils"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dRigidBody
local body
return function()
	describe("RigidBody", function()
		before(function()
			UTILS.set_env(getfenv(1))
			w = rp3d.createPhysicsWorld()
			body = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
		end)
		after(function()
			--w:destroyCollisionBody(bodies[1])
			w:destroyRigidBody(body)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("CollisionBody instead of RigidBody", function()
			local b = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
			local status, error = pcall(body.updateMassPropertiesFromColliders,b)
			assert_false(status)
			assert_equal(error,"Need RigidBody.Get CollisionBody")
		end)

		test("updateMassPropertiesFromColliders", function()
			body:updateMassPropertiesFromColliders()
		end)

	end)
end
