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
			assert_true(true)
		end)

		test("get/set Type", function()
			assert_equal(body:getType(),rp3d.BodyType.DYNAMIC)
			body:setType(rp3d.BodyType.KINEMATIC)
			assert_equal(body:getType(),rp3d.BodyType.KINEMATIC)
			body:setType(rp3d.BodyType.STATIC)
			assert_equal(body:getType(),rp3d.BodyType.STATIC)
			body:setType(rp3d.BodyType.DYNAMIC)
			assert_equal(body:getType(),rp3d.BodyType.DYNAMIC)
			local status,error = pcall(body.setType,body,"ssss");
			assert_false(status)
			assert_equal(error,"unknown BodyType:ssss")
		end)

	end)
end
