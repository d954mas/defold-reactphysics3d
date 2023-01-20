local UTILS = require "tests.test_utils"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dCollisionBody
local b
---@type Rp3dCollisionShape
local shape
---@type Rp3dCollider
local collider

return function()
	describe("Collider", function()
		before(function()
			UTILS.set_env(getfenv(1))
			shape = rp3d.createBoxShape(vmath.vector3(1))
			w = rp3d.createPhysicsWorld()
			b = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			collider = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
		end)
		after(function()
			w:destroyCollisionBody(b)
			rp3d.destroyBoxShape(shape)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("create()", function()
			local body = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c = body:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			assert_not_nil(c)
			w:destroyCollisionBody(body)
		end)
		test("destroy body", function()
			local body = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c = body:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			assert_not_nil(c)
			w:destroyCollisionBody(body)
			local status, error = pcall(c.getEntityId, c)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Collider was destroyed")
		end)

		test("destroy collider", function()
			local body = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c = body:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			assert_not_nil(c)
			body:removeCollider(c)
			local status, error = pcall(c.getEntityId, c)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Collider was destroyed")
		end)

		test("destroy world", function()
			local world = rp3d.createPhysicsWorld()
			local body = world:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c = body:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			local body_rigid = world:createRigidBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c2 = body_rigid:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			assert_not_nil(c)
			assert_not_nil(c2)
			rp3d.destroyPhysicsWorld(world)
			local status, error = pcall(c.getEntityId, c)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Collider was destroyed")
			status, error = pcall(c2.getEntityId, c2)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Collider was destroyed")
		end)

		--[[test("equals()", function()
			local body = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c = body:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			local c2 = body:getCollider(0);
			assert_equal(c,c2)
		end)--]]

		test("get/set UserData()", function()
			assert_nil(collider:getUserData())
			local data = {}
			local data2 = {}
			collider:setUserData(data)
			assert_equal(data, collider:getUserData())
			collider:setUserData(data2)
			assert_not_equal(data, collider:getUserData())
			assert_equal(data2, collider:getUserData())
			collider:setUserData(nil)
			assert_nil(collider:getUserData())
			local status, error = pcall(collider.setUserData, collider, "data")
			assert_false(status)
			UTILS.test_error(error, "userdata can be only table or nil")
		end)

		test("getEntityId()", function()
			assert_type(collider:getEntityId(), "number")
		end)

		test("getCollisionShape()", function()
			assert_equal(collider:getCollisionShape(), shape)
		end)

		test("getBody()", function()
			assert_equal(collider:getBody(), b)
		end)

		test("get/set LocalToBodyTransform()", function()
			local t = collider:getLocalToBodyTransform()
			assert_equal_v3(t.position, vmath.vector3(0))
			assert_equal_quat(t.quat, vmath.quat())
			collider:setLocalToBodyTransform({ position = vmath.vector3(1, 2, 3), quat = vmath.quat_rotation_z(3.14) })

			t = collider:getLocalToBodyTransform()
			assert_equal_v3(t.position, vmath.vector3(1, 2, 3))
			assert_equal_quat(t.quat, vmath.quat_rotation_z(3.14))
		end)

		test("getLocalToWorldTransform()", function()
			local t = collider:getLocalToWorldTransform()
			assert_equal_v3(t.position, vmath.vector3(0))
			assert_equal_quat(t.quat, vmath.quat())
		end)

		test("getWorldAABB()", function()
			local aabb = collider:getWorldAABB()
			assert_equal_v3(aabb:getMin(), vmath.vector3(-1))
			assert_equal_v3(aabb:getMax(), vmath.vector3(1))
		end)

		test("testPointInside()", function()
			assert_true(collider:testPointInside(vmath.vector3(0)))
			assert_true(collider:testPointInside(vmath.vector3(0.99)))
			assert_false(collider:testPointInside(vmath.vector3(1.1)))
		end)

		test("testAABBOverlap()", function()
			local aabb = shape:computeAABB({ position = vmath.vector3(10), quat = vmath.quat() })
			local aabb2 = shape:computeAABB({ position = vmath.vector3(1.1), quat = vmath.quat() })

			assert_false(collider:testAABBOverlap(aabb))
			assert_true(collider:testAABBOverlap(aabb2))
		end)

		test("testRaycast()", function()
			local ray_miss = { point1 = vmath.vector3(-100, 0, 0),
							   point2 = vmath.vector3(-100, 100, 0),
							   maxFraction = 1 }
			local ray1 = { point1 = vmath.vector3(-100, 0, 0),
						   point2 = vmath.vector3(-0.99, 0, 0),
						   maxFraction = 1 }

			assert_nil(collider:raycast(ray_miss))
			local info = collider:raycast(ray1)
			assert_not_nil(info)
			assert_equal_v3(info.worldPoint, vmath.vector3(-1, 0, 0))
			assert_equal_v3(info.worldNormal, vmath.vector3(-1, 0, 0))
			assert_greater_than(info.hitFraction, 0.99)
			assert_less_than(info.hitFraction, 1)
			assert_equal(info.meshSubpart, -1)
			assert_equal(info.triangleIndex, -1)
			assert_equal(info.body, b)
			assert_equal(info.collider, collider)
			ray1.maxFraction = 0.9
			assert_nil(collider:raycast(ray1))

		end)
		test("set/get CollideWithMaskBits()", function()
			UTILS.test_method_get_set(collider, "CollideWithMaskBits", {
				values = { bit.tobit(0), bit.lshift(1, 1), bit.lshift(1, 2), bit.lshift(1, 15) }
			})
		end)

		test("set/get CollisionCategoryBits()", function()
			UTILS.test_method_get_set(collider, "CollisionCategoryBits", {
				values = { bit.tobit(0), bit.lshift(1, 1), bit.lshift(1, 2), bit.lshift(1, 15) }
			})
		end)

		test("getBroadPhaseId()", function()
			assert_equal(collider:getBroadPhaseId(), 0)
		end)

		test("set/get IsTrigger()", function()
			UTILS.test_method_get_set(collider, "IsTrigger", {
				values = { false, true, false, false }
			})
		end)

		test("toString()", function()
			assert_equal(tostring(collider):sub(1, 14), "rp3d::Collider")
		end)


	end)
end
