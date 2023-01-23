local UTILS = require "tests.test_utils"

return function()
	describe("World", function()
		before(function()
			UTILS.set_env(getfenv(1))
		end)
		after(function() end)

		test("create", function()
			local w = rp3d.createPhysicsWorld()
			assert_not_nil(w)
			assert_not_nil(w.__userdata_rp3d)
			assert_equal(w.__userdata_type_rp3d, "rp3d::World")

			rp3d.destroyPhysicsWorld(w)
			assert_not_nil(w)
			assert_nil(w.__userdata_rp3d)
			assert_equal(w.__userdata_type_rp3d, "rp3d::World")
		end)

		test("create config", function()
			local cfg = {}
			local w = rp3d.createPhysicsWorld(cfg)
			assert_not_nil(w)
			assert_not_nil(w.__userdata_rp3d)
			assert_equal(w.__userdata_type_rp3d, "rp3d::World")
			--TODO CHECK CONFIG DATA

			rp3d.destroyPhysicsWorld(w)
			assert_not_nil(w)
			assert_nil(w.__userdata_rp3d)
			assert_equal(w.__userdata_type_rp3d, "rp3d::World")
		end)

		test("update", function()
			local w = rp3d.createPhysicsWorld()
			w:update(1 / 60)
			w:update(1 / 30)
			w:update(0.001)
			w:update(1 / 120)

			local status, error = pcall(w.update, w)
			assert_false(status)
			UTILS.test_error(error, "This function requires 2 arguments. Got 1.")

			rp3d.destroyPhysicsWorld(w)
		end)

		test("Set/Get NbIterationsPositionSolver()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "NbIterationsPositionSolver", {
				values = { 1, 5, 10 }
			})
			rp3d.destroyPhysicsWorld(w)
		end)

		test("Set/Get NbIterationsVelocitySolver()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "NbIterationsVelocitySolver", {
				values = { 1, 5, 10 }
			})
			rp3d.destroyPhysicsWorld(w)
		end)

		test("Set/Get Gravity()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "Gravity",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, -10, 0), vmath.vector3(5, 6, 7) }
					})
			rp3d.destroyPhysicsWorld(w)
		end)

		test("Set/Get SleepAngularVelocity()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "SleepAngularVelocity",
					{ float = true,
					  values = { 0,0.002,1,0.05 }
					})
			rp3d.destroyPhysicsWorld(w)
		end)

		test("Set/Get SleepLinearVelocity()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "SleepLinearVelocity",
					{ float = true,
						values = { 0.1,0.2,0.3,0.4 }
					})
			rp3d.destroyPhysicsWorld(w)
		end)

		test("Set/Get TimeBeforeSleep()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "TimeBeforeSleep",
					{ float = true,
					  values = { 1,0.2,2,32,0.5 }
					})
			rp3d.destroyPhysicsWorld(w)
		end)

		test("Is/SetIs GravityEnabled()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "GravityEnabled",
					{ 
					  getter_full = "isGravityEnabled",
					  setter_full = "setIsGravityEnabled",
					  values = { false, true, true, false }
					})
			rp3d.destroyPhysicsWorld(w)
		end)
		test("Is/Enable Sleeping()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "SleepingEnabled",
					{
						getter_full = "isSleepingEnabled",
						setter_full = "enableSleeping",
						values = { false, true, true, false }
					})
			rp3d.destroyPhysicsWorld(w)
		end)

		test("Set/Get IsDebugRenderingEnabled()", function()
			local w = rp3d.createPhysicsWorld()
			UTILS.test_method_get_set(w, "IsDebugRenderingEnabled",
					{
						values = { false, true, true, false }
					})
			rp3d.destroyPhysicsWorld(w)
		end)
		test("SetContactsPositionCorrectionTechnique()", function()
			local w = rp3d.createPhysicsWorld()
			w:setContactsPositionCorrectionTechnique(rp3d.ContactsPositionCorrectionTechnique.BAUMGARTE_CONTACTS)
			w:setContactsPositionCorrectionTechnique(rp3d.ContactsPositionCorrectionTechnique.SPLIT_IMPULSES)
			local status, error = pcall(w.setContactsPositionCorrectionTechnique, w, 3)
			assert_false(status)
			UTILS.test_error(error, "unknown ContactsPositionCorrectionTechnique")
			rp3d.destroyPhysicsWorld(w)
		end)
		test("EnableDisableJoints()", function()
			local w = rp3d.createPhysicsWorld()
			w:enableDisableJoints()
			assert_true(true)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("getNbRigidBodies()", function()
			local w = rp3d.createPhysicsWorld()
			assert_equal(0,w:getNbRigidBodies())
			rp3d.destroyPhysicsWorld(w)
		end)

		test("getNbCollisionBodies()", function()
			local w = rp3d.createPhysicsWorld()
			assert_equal(0,w:getNbCollisionBodies())
			rp3d.destroyPhysicsWorld(w)
		end)

		test("createCollisionBody()", function()
			local w = rp3d.createPhysicsWorld()
			local collisionBody = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(collisionBody)
			assert_false(collisionBody:isRigidBody())
			rp3d.destroyPhysicsWorld(w)
		end)

		test("createRigidBody()", function()
			local w = rp3d.createPhysicsWorld()
			local collisionBody = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(collisionBody)
			assert_true(collisionBody:isRigidBody())
			rp3d.destroyPhysicsWorld(w)
		end)

		test("destroyCollisionBody()", function()
			local w = rp3d.createPhysicsWorld()
			local body = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(body)
			w:destroyCollisionBody(body)
			local status, error = pcall(body.isRigidBody,body)
			assert_false(status,error)
			UTILS.test_error(error,"rp3d::CollisionBody was destroyed")
			rp3d.destroyPhysicsWorld(w)
		end)

		test("destroyRigidBody()", function()
			local w = rp3d.createPhysicsWorld()
			local body = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(body)
			w:destroyRigidBody(body)
			local status, error = pcall(body.isRigidBody,body)
			assert_false(status,error)
			UTILS.test_error(error,"rp3d::CollisionBody was destroyed")
			rp3d.destroyPhysicsWorld(w)
		end)

		test("destroyCollisionBody(rigid)", function()
			local w = rp3d.createPhysicsWorld()
			local body = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(body)
			local status, error = pcall(w.destroyCollisionBody,w,body)
			assert_false(status,error)
			UTILS.test_error(error,"can't destroy RigidBody.Need CollisionBody")
			rp3d.destroyPhysicsWorld(w)
		end)

		test("destroyRigidBody(collision)", function()
			local w = rp3d.createPhysicsWorld()
			local body = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(body)
			local status, error = pcall(w.destroyRigidBody,w,body)
			assert_false(status,error)
			UTILS.test_error(error,"can't destroy CollisionBody.Need RigidBody")
			rp3d.destroyPhysicsWorld(w)
		end)

		test("getDebugRenderer()", function()
			local w = rp3d.createPhysicsWorld()
			assert_not_nil(w:getDebugRenderer())
			rp3d.destroyPhysicsWorld(w)
		end)

		test("raycast()", function()
			local w = rp3d.createPhysicsWorld()
			local shape = rp3d.createBoxShape(vmath.vector3(1))

			local body_1 = w:createRigidBody({ position = vmath.vector3(5, 0, 0),quat = vmath.quat() })
			local body_2 = w:createRigidBody({ position = vmath.vector3(10, 0, 0),quat = vmath.quat() })
			local body_3 = w:createRigidBody({ position = vmath.vector3(15, 0, 0),quat = vmath.quat() })

			local c1= body_1:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c2= body_2:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c3= body_3:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})

			---@type Rp3dRaycastInfo[]
			local cb_results = {}
			local cb_closest = function(info)
				assert_not_nil(info)
				assert_not_nil(info.worldPoint)
				assert_not_nil(info.worldNormal)
				assert_not_nil(info.hitFraction)
				assert_not_nil(info.meshSubpart)
				assert_not_nil(info.triangleIndex)
				assert_not_nil(info.body)
				assert_not_nil(info.collider)
				table.insert(cb_results, info)
				return info.hitFraction
			end

			local cb_all = function(info)
				table.insert(cb_results, info)
				return 1
			end

			local cb_any = function(info)
				table.insert(cb_results, info)
				return 0
			end

			local p1 = vmath.vector3(0, 0, 0)
			local point_no = vmath.vector3(0, 10, 0)
			local point_one = vmath.vector3(5, 0, 0)
			local point_all = vmath.vector3(15, 0, 0)
			local ray_no = {point1 = p1,point2 = point_no,maxFraction = 1}
			local ray_1 = {point1 = p1,point2 = point_one,maxFraction = 1}
			local ray_all = {point1 = p1,point2 = point_all,maxFraction = 1}

			--*** NO ***
			w:raycast(ray_no, cb_closest)
			assert_equal(#cb_results, 0)
			w:raycast(ray_no, cb_closest)
			assert_equal(#cb_results, 0)
			w:raycast(ray_no, cb_closest)
			assert_equal(#cb_results, 0)

			--*** ONE ***
			w:raycast(ray_1, cb_closest)
			assert_equal(#cb_results, 1)
			assert_equal(cb_results[1].body, body_1)
			cb_results = {}
			w:raycast(ray_1,cb_all)
			assert_equal(#cb_results, 1)
			cb_results = {}
			w:raycast(ray_1,cb_any)
			assert_equal(#cb_results, 1)
			cb_results = {}

			--*** ALL ***
			w:raycast(ray_all,cb_closest)
			assert_equal(cb_results[#cb_results].body, body_1)
			cb_results = {}
			w:raycast(ray_all,cb_all)
			assert_equal(#cb_results, 3)
			cb_results = {}
			w:raycast(ray_all,cb_any)
			assert_equal(#cb_results, 1)
			cb_results = {}

			w:raycast(ray_all,cb_all,bit.tobit(math.pow(2,16)-1))
			assert_equal(#cb_results, 3)
			cb_results = {}

			--c1:setCollideWithMaskBits(1)
			--c2:setCollideWithMaskBits(1)
			--c3:setCollideWithMaskBits(1)

		--	c1:setCollisionCategoryBits(1)
		--	c2:setCollisionCategoryBits(1)
		--	c3:setCollisionCategoryBits(1)

			w:raycast(ray_all,cb_all,bit.tobit(1))
			assert_equal(#cb_results, 3)
			cb_results = {}

			w:raycast(ray_all,cb_all,bit.tobit(2))
			assert_equal(#cb_results, 0)
			cb_results = {}

			w:raycast(ray_all,cb_all,bit.tobit(math.pow(2,16)-1))
			assert_equal(#cb_results, 3)
			cb_results = {}


			c1:setCollisionCategoryBits(2)
			c2:setCollisionCategoryBits(2)
			c3:setCollisionCategoryBits(2)
			w:raycast(ray_all,cb_all,bit.tobit(1))
			assert_equal(#cb_results, 0)
			cb_results = {}

			w:raycast(ray_all,cb_all,bit.tobit(2))
			assert_equal(#cb_results, 3)
			cb_results = {}

			w:raycast(ray_all,cb_all,bit.tobit(math.pow(2,16)-1))
			assert_equal(#cb_results, 3)
			cb_results = {}

			local cb_error = function() error("error happened") end
			local status, error = pcall(w.raycast, w, ray_all,cb_error)
			assert_false(status)
			--remove line number
			UTILS.test_error(error, "error happened")

			cb_error = function() w.aaaa() end
			status, error = pcall(w.raycast, w, ray_all,cb_error)
			assert_false(status)
			UTILS.test_error(error, " attempt to call field 'aaaa' (a nil value)")

			rp3d.destroyPhysicsWorld(w)
			rp3d.destroyBoxShape(shape)
		end)

		test("testOverlap2Bodies()", function()
			local w = rp3d.createPhysicsWorld()
			local shape = rp3d.createBoxShape(vmath.vector3(2.5))

			local body_1 = w:createRigidBody({ position = vmath.vector3(0, 0, 0),quat = vmath.quat() })
			local body_2 = w:createRigidBody({ position = vmath.vector3(3, 0, 0),quat = vmath.quat() })
			local body_3 = w:createRigidBody({ position = vmath.vector3(6, 0, 0),quat = vmath.quat() })

			local c1= body_1:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c2= body_2:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c3= body_3:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})

			assert_false(w:testOverlap2Bodies(body_1,body_1))
			assert_true(w:testOverlap2Bodies(body_1,body_2))
			assert_true(w:testOverlap2Bodies(body_2,body_3))
			assert_false(w:testOverlap2Bodies(body_1,body_3))



			rp3d.destroyPhysicsWorld(w)
			rp3d.destroyBoxShape(shape)
		end)


		test("testOverlapBodyList()", function()
			local w = rp3d.createPhysicsWorld()
			local shape = rp3d.createBoxShape(vmath.vector3(2.5))

			local body_1 = w:createRigidBody({ position = vmath.vector3(0, 0, 0),quat = vmath.quat() })
			local body_2 = w:createRigidBody({ position = vmath.vector3(3, 0, 0),quat = vmath.quat() })
			local body_3 = w:createRigidBody({ position = vmath.vector3(6, 0, 0),quat = vmath.quat() })

			local c1= body_1:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c2= body_2:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c3= body_3:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})


			local list1 = w:testOverlapBodyList(body_1)
			local list2 = w:testOverlapBodyList(body_2)
			local list3 = w:testOverlapBodyList(body_3)

			assert_equal(#list1,1)
			assert_equal(#list2,2)
			assert_equal(#list3,1)

			assert_equal(list1[1].body1,body_2)
			assert_equal(list1[1].body2,body_1)
			assert_equal(list1[1].collider1,c2)
			assert_equal(list1[1].collider2,c1)
			assert_equal(list1[1].eventType,rp3d.OverlapPair.EventType.OverlapStart)

			w:destroyRigidBody(body_2)
			w:destroyRigidBody(body_3)

			local list4 = w:testOverlapBodyList(body_1)
			assert_equal(#list4,0)



			rp3d.destroyPhysicsWorld(w)
			rp3d.destroyBoxShape(shape)
		end)

		test("testOverlapList()", function()
			local w = rp3d.createPhysicsWorld()
			local shape = rp3d.createBoxShape(vmath.vector3(2.5))
			local shape_big = rp3d.createBoxShape(vmath.vector3(10))

			local body_1 = w:createRigidBody({ position = vmath.vector3(0, 0, 0),quat = vmath.quat() })
			local body_2 = w:createRigidBody({ position = vmath.vector3(3, 0, 0),quat = vmath.quat() })
			local body_3 = w:createRigidBody({ position = vmath.vector3(6, 0, 0),quat = vmath.quat() })

			local c1= body_1:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c2= body_2:addCollider( shape,{position = vmath.vector3(),quat = vmath.quat()})
			local c3= body_3:addCollider( shape_big,{position = vmath.vector3(),quat = vmath.quat()})


			local list1 = w:testOverlapList()

			assert_equal(#list1,3)


			rp3d.destroyPhysicsWorld(w)
			rp3d.destroyBoxShape(shape)
			rp3d.destroyBoxShape(shape_big)
		end)



	end)
end
