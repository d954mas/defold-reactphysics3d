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

		test("isRigidBody()", function()
			assert_false(bodies[1]:isRigidBody())
			assert_true(bodies[2]:isRigidBody())
		end)
		test("is/set Active()", function()
			for _,body in ipairs(bodies)do
				UTILS.test_method_get_set(body, "Active",
					{
						getter_full = "isActive",
						setter_full = "setIsActive",
						values = { false, true, true, false }
					})
				end
		end)

		test("get/set UserData()", function()
			for _,body in ipairs(bodies)do
				assert_nil(body:getUserData())
				local data = {}
				local data2 = {}
				body:setUserData(data)
				assert_equal(data,body:getUserData())
				body:setUserData(data2)
				assert_not_equal(data,body:getUserData())
				assert_equal(data2,body:getUserData())
				body:setUserData(nil)
				assert_nil(body:getUserData())
				local status,error = pcall(body.setUserData,body,"data")
				assert_false(status)
				assert_equal(error,"userdata can be only table or nil")

			end
		end)

		test("get/set Transform()", function()
			for _,body in ipairs(bodies)do
				local initTransform = body:getTransform()
				assert_not_nil(initTransform)
				assert_equal_v3(initTransform.position,vmath.vector3(0,0,0))
				assert_equal_quat(initTransform.quat,vmath.quat())
				body:setTransform({position =  vmath.vector3(1,2,3),quat = vmath.quat_rotation_z(math.pi)})
				local transform2 = body:getTransform()
				assert_equal_v3(transform2.position,vmath.vector3(1,2,3))
				assert_equal_quat(transform2.quat,vmath.quat_rotation_z(math.pi))

				local status,error = pcall(body.setTransform,body,{})
				assert_false(status)
				assert_equal(error,"transform need position")

			end
		end)

		test("addCollider()", function()
			for _,b in ipairs(bodies)do
				local shape = rp3d.createBoxShape(vmath.vector3(2))
				local collider = b:addCollider(shape,{position = vmath.vector3(),quat = vmath.quat()})
				assert_not_nil(collider)
			end
		end)
		test("getNbColliders()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _,b in ipairs(bodies)do
				assert_equal(b:getNbColliders(),0)
				local c = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				assert_equal(b:getNbColliders(),1)
				b:removeCollider(c)
				assert_equal(b:getNbColliders(),0)
			end

		end)

		test("removeCollider()", function()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for _,b in ipairs(bodies)do
				local c = b:addCollider(shape, { position = vmath.vector3(), quat = vmath.quat() })
				b:removeCollider(c)
				local status, error = pcall(c.getEntityId,c)
				assert_false(status)
				assert_equal(error,"rp3d::Collider was destroyed")
			end

		end)


		test("toString()", function()
			assert_equal(tostring(bodies[1]):sub(1,19),"rp3d::CollisionBody")
			assert_equal(tostring(bodies[2]):sub(1,15),"rp3d::RigidBody")
		end)



	end)
end
