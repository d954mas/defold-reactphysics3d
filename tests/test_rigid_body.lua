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
			body = w:createRigidBody({ position = vmath.vector3(), quat = vmath.quat() })
		end)
		after(function()
			w:destroyRigidBody(body)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("CollisionBody instead of RigidBody", function()
			local b = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local status, error = pcall(body.updateMassPropertiesFromColliders, b)
			assert_false(status)
			UTILS.test_error(error, "Need RigidBody.Get CollisionBody")
		end)

		test("updateLocalCenterOfMassFromColliders()", function()
			body:updateLocalCenterOfMassFromColliders()
			assert_true(true)
		end)

		test("updateLocalInertiaTensorFromColliders()", function()
			body:updateLocalInertiaTensorFromColliders()
			assert_true(true)
		end)

		test("updateMassFromColliders()", function()
			body:updateMassFromColliders()
			assert_true(true)
		end)

		test("updateMassPropertiesFromColliders()", function()
			body:updateMassPropertiesFromColliders()
			assert_true(true)
		end)

		test("get/set Type()", function()
			assert_equal(body:getType(), rp3d.BodyType.DYNAMIC)
			body:setType(rp3d.BodyType.KINEMATIC)
			assert_equal(body:getType(), rp3d.BodyType.KINEMATIC)
			body:setType(rp3d.BodyType.STATIC)
			assert_equal(body:getType(), rp3d.BodyType.STATIC)
			body:setType(rp3d.BodyType.DYNAMIC)
			assert_equal(body:getType(), rp3d.BodyType.DYNAMIC)
			local status, error = pcall(body.setType, body, "ssss");
			assert_false(status)
			UTILS.test_error(error, "unknown BodyType:ssss")
		end)

		test("set/get Mass()", function()
			UTILS.test_method_get_set(body, "Mass", {
				values = { 1, 5, 10 }
			})
		end)

		test("set/get LinearVelocity()", function()
			UTILS.test_method_get_set(body, "LinearVelocity",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, -10, 0), vmath.vector3(5, 6, 7) }
					})
		end)
		test("set/get AngularVelocity()", function()
			UTILS.test_method_get_set(body, "AngularVelocity",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, -10, 0), vmath.vector3(5, 6, 7) }
					})
		end)

		test("set/get LocalInertiaTensor()", function()
			UTILS.test_method_get_set(body, "LocalInertiaTensor",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, -10, 0), vmath.vector3(5, 6, 7) }
					})
		end)

	end)
end
