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

		test("set/get IsGravityEnabled()", function()
			UTILS.test_method_get_set(body, "GravityEnabled",
					{  getter_full = "isGravityEnabled",
					   setter_full = "enableGravity",
					  values = { false,true,false }
					})
		end)

		test("set/get IsSleeping()", function()
			body:isSleeping()
			UTILS.test_method_get_set(body, "IsSleeping",
					{  getter_full = "isSleeping",
					   setter_full = "setIsSleeping",
					   values = { false,true,false }
					})
		end)

		test("set/get LinearDamping()", function()
			UTILS.test_method_get_set(body, "LinearDamping",
					{
					  values = { 0,0.5,2,5 }
					})
		end)

		test("set/get AngularDamping()", function()
			UTILS.test_method_get_set(body, "AngularDamping",
					{
						values = { 0,0.5,2,5 }
					})
		end)

		test("set/get LinearLockAxisFactor()", function()
			UTILS.test_method_get_set(body, "LinearLockAxisFactor",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, -10, 0), vmath.vector3(5, 6, 7) }
					})
		end)

		test("set/get AngularLockAxisFactor()", function()
			UTILS.test_method_get_set(body, "AngularLockAxisFactor",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, -10, 0), vmath.vector3(5, 6, 7) }
					})
		end)

		test("applyLocalForceAtCenterOfMass()", function()
			body:applyLocalForceAtCenterOfMass(vmath.vector3(1))
			assert(true)
		end)

		test("applyWorldForceAtCenterOfMass()", function()
			body:applyWorldForceAtCenterOfMass(vmath.vector3(1))
			assert(true)
		end)

		test("applyLocalForceAtLocalPosition()", function()
			body:applyLocalForceAtLocalPosition(vmath.vector3(1),vmath.vector3(0))
			assert(true)
		end)
		test("applyWorldForceAtLocalPosition()", function()
			body:applyWorldForceAtLocalPosition(vmath.vector3(1),vmath.vector3(0))
			assert(true)
		end)
		test("applyLocalForceAtWorldPosition()", function()
			body:applyLocalForceAtWorldPosition(vmath.vector3(1),vmath.vector3(0))
			assert(true)
		end)
		test("applyWorldForceAtWorldPosition()", function()
			body:applyWorldForceAtWorldPosition(vmath.vector3(1),vmath.vector3(0))
			assert(true)
		end)

		test("applyLocalTorque()", function()
			body:applyLocalTorque(vmath.vector3(1))
			assert(true)
		end)

		test("applyWorldTorque()", function()
			body:applyWorldTorque(vmath.vector3(1))
			assert(true)
		end)

		test("resetForce()", function()
			body:resetForce()
			assert(true)
		end)

		test("resetTorque()", function()
			body:resetTorque()
			assert(true)
		end)


	end)
end
