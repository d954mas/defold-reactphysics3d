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
			local status,error = pcall(c.getEntityId,c)
			assert_false(status)
			assert_equal(error,"rp3d::Collider was destroyed")
		end)

		test("destroy collider", function()
			local body = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c = body:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			assert_not_nil(c)
			body:removeCollider(c)
			local status,error = pcall(c.getEntityId,c)
			assert_false(status)
			assert_equal(error,"rp3d::Collider was destroyed")
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
			local status,error = pcall(c.getEntityId,c)
			assert_false(status)
			assert_equal(error,"rp3d::Collider was destroyed")
			status,error = pcall(c2.getEntityId,c2)
			assert_false(status)
			assert_equal(error,"rp3d::Collider was destroyed")
		end)

		--[[test("equals()", function()
			local body = w:createCollisionBody({ position = vmath.vector3(), quat = vmath.quat() })
			local c = body:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
			local c2 = body:getCollider(0);
			assert_equal(c,c2)
		end)--]]



		test("toString()", function()
			assert_equal(tostring(collider):sub(1,14), "rp3d::Collider")
		end)


	end)
end
