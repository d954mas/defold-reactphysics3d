local UTILS = require "tests.test_utils"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dCollisionBody[]
local bodies = {}
return function()
	describe("CollisionBody", function()
		before(function()
			UTILS.set_env(getfenv(1))
			w = rp3d.createPhysicsWorld()
			bodies[1] = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			bodies[2] = w:createRigidBody({ position = vmath.vector3(), quat = vmath.quat() })
		end)
		after(function()
			w:destroyCollisionBody(bodies[1])
			w:destroyRigidBody(bodies[2])
			rp3d.destroyPhysicsWorld(w)
		end)

		test("world destroyed.Destroy collision bodies", function()
			local world = rp3d.createPhysicsWorld()
			local collision_body = world:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local rigid_body = world:createRigidBody({ position = vmath.vector3(), quat = vmath.quat() })
			assert_false(collision_body:isRigidBody())
			assert_true(rigid_body:isRigidBody())
			rp3d.destroyPhysicsWorld(world)

			local status, error = pcall(collision_body.isRigidBody, collision_body)
			assert_false(status)
			UTILS.test_error(error, "rp3d::CollisionBody was destroyed")

			status, error = pcall(rigid_body.isRigidBody, rigid_body)
			assert_false(status)
			UTILS.test_error(error, "rp3d::CollisionBody was destroyed")
		end)

		test("getEntityId()", function()
			for _, body in ipairs(bodies) do
				assert_type(body:getEntityId(), "number")
			end
		end)

		test("isRigidBody()", function()
			assert_false(bodies[1]:isRigidBody())
			assert_true(bodies[2]:isRigidBody())
		end)
		test("is/set Active()", function()
			for _, body in ipairs(bodies) do
				UTILS.test_method_get_set(body, "Active",
						{
							getter_full = "isActive",
							setter_full = "setIsActive",
							values = { false, true, true, false }
						})
			end
		end)

		test("get/set UserData()", function()
			for _, body in ipairs(bodies) do
				assert_nil(body:getUserData())
				local data = {}
				local data2 = {}
				body:setUserData(data)
				assert_equal(data, body:getUserData())
				body:setUserData(data2)
				assert_not_equal(data, body:getUserData())
				assert_equal(data2, body:getUserData())
				body:setUserData(nil)
				assert_nil(body:getUserData())
				local status, error = pcall(body.setUserData, body, "data")
				assert_false(status)
				UTILS.test_error(error, "userdata can be only table or nil")

			end
		end)

		test("get/set Transform()", function()
			for _, body in ipairs(bodies) do
				local initTransform = body:getTransform()
				assert_not_nil(initTransform)
				assert_equal_v3(initTransform.position, vmath.vector3(0, 0, 0))
				assert_equal_quat(initTransform.quat, vmath.quat())
				body:setTransform({ position = vmath.vector3(1, 2, 3), quat = vmath.quat_rotation_z(math.pi) })
				local transform2 = body:getTransform()
				assert_equal_v3(transform2.position, vmath.vector3(1, 2, 3))
				assert_equal_quat(transform2.quat, vmath.quat_rotation_z(math.pi))

				local status, error = pcall(body.setTransform, body, {})
				assert_false(status)
				UTILS.test_error(error, "transform need position")

			end
		end)

		test("addCollider()", function()
			for _, b in ipairs(bodies) do
				local shape = rp3d.createBoxShape(vmath.vector3(2))
				local collider = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				assert_not_nil(collider)
			end
		end)
		test("getNbColliders()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _, b in ipairs(bodies) do
				assert_equal(b:getNbColliders(), 0)
				local c = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				assert_equal(b:getNbColliders(), 1)
				b:removeCollider(c)
				assert_equal(b:getNbColliders(), 0)
			end

		end)

		test("removeCollider()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _, b in ipairs(bodies) do
				local c = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				b:removeCollider(c)
				local status, error = pcall(c.getEntityId, c)
				assert_false(status)
				UTILS.test_error(error, "rp3d::Collider was destroyed")
			end

		end)

		test("getCollider()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _, b in ipairs(bodies) do
				local c = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				local c2 = b:getCollider(0)
				assert_equal(c, c2)
				local status, error = pcall(b.getCollider, b, 1)
				assert_false(status)
				UTILS.test_error(error, "bad idx:1. Size:1")
			end

		end)

		test("testPointInside()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _, b in ipairs(bodies) do
				assert_false(b:testPointInside(vmath.vector3(0)))
				b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				assert_true(b:testPointInside(vmath.vector3(0)))
				assert_true(b:testPointInside(vmath.vector3(1.99)))
				assert_false(b:testPointInside(vmath.vector3(2.1)))
			end

		end)

		test("testRaycast()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _, b in ipairs(bodies) do
				local c = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				local ray_miss = { point1 = vmath.vector3(-100, 0, 0),
								   point2 = vmath.vector3(-100, 100, 0),
								   maxFraction = 1 }
				local ray1 = { point1 = vmath.vector3(-100, 0, 0),
							   point2 = vmath.vector3(-1.99, 0, 0),
							   maxFraction = 1 }

				assert_nil(b:raycast(ray_miss))
				local info = b:raycast(ray1)
				assert_not_nil(info)
				assert_equal_v3(info.worldNormal, vmath.vector3(-1, 0, 0))
				assert_greater_than(info.hitFraction, 0.99)
				assert_less_than(info.hitFraction, 1)
				assert_equal(info.meshSubpart, -1)
				assert_equal(info.triangleIndex, -1)
				assert_equal(info.body, b)
				assert_equal(c, c)
				ray1.maxFraction = 0.9
				assert_nil(b:raycast(ray1))
			end

		end)

		test("testAABBOverlap()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _, b in ipairs(bodies) do
				local box = rp3d.createBoxShape(vmath.vector3(1))
				local aabb = box:computeAABB({ position = vmath.vector3(10), quat = vmath.quat() })
				local aabb2 = box:computeAABB({ position = vmath.vector3(1.1), quat = vmath.quat() })

				assert_false(b:testAABBOverlap(aabb))
				assert_false(b:testAABBOverlap(aabb2))
				b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				assert_false(b:testAABBOverlap(aabb))
				assert_true(b:testAABBOverlap(aabb2))
				b:addCollider(shape, { position = vmath.vector3(10), quat = vmath.quat() })
				assert_true(b:testAABBOverlap(aabb))
				assert_true(b:testAABBOverlap(aabb2))
			end
		end)

		test("getAABB()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _, b in ipairs(bodies) do
				local aabb = b:getAABB()
				assert_equal_v3(aabb:getMin(), vmath.vector3(0))
				assert_equal_v3(aabb:getMax(), vmath.vector3(0))
				b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				aabb = b:getAABB()
				assert_equal_v3(aabb:getMin(), vmath.vector3(-2))
				assert_equal_v3(aabb:getMax(), vmath.vector3(2))
			end
		end)

		test("getWorldPoint/getLocalPoint()", function()
			for _, b in ipairs(bodies) do
				b:setTransform({ position = vmath.vector3(0, 10, 0), quat = vmath.quat() })
				local world_point = b:getWorldPoint(vmath.vector3(1))
				assert_equal_v3(vmath.vector3(1, 11, 1), world_point)
				assert_equal_v3(vmath.vector3(1), b:getLocalPoint(world_point))
			end
		end)

		test("getWorldVector/getLocalVector()", function()
			for _, b in ipairs(bodies) do
				b:setTransform({ position = vmath.vector3(0, 10, 0), quat = vmath.quat_rotation_z(math.rad(180)) })
				local world_v3 = b:getWorldVector(vmath.vector3(1))
				assert_equal_v3(vmath.vector3(-1, -1, 1), world_v3,0.0001)
				assert_equal_v3(vmath.vector3(1), b:getLocalVector(world_v3),0.0001)
			end
		end)

		test("toString()", function()
			assert_equal(tostring(bodies[1]):sub(1, 19), "rp3d::CollisionBody")
			assert_equal(tostring(bodies[2]):sub(1, 15), "rp3d::RigidBody")
		end)


	end)
end
