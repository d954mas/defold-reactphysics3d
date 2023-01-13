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
			assert_equal(error, "This function requires 2 arguments. Got 1.")

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
			assert_equal(error, "unknown ContactsPositionCorrectionTechnique")
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
			assert_equal(error,"rp3d::CollisionBody was destroyed")
			rp3d.destroyPhysicsWorld(w)
		end)

		test("destroyRigidBody()", function()
			local w = rp3d.createPhysicsWorld()
			local body = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(body)
			w:destroyRigidBody(body)
			local status, error = pcall(body.isRigidBody,body)
			assert_false(status,error)
			assert_equal(error,"rp3d::CollisionBody was destroyed")
			rp3d.destroyPhysicsWorld(w)
		end)

		test("destroyCollisionBody(rigid)", function()
			local w = rp3d.createPhysicsWorld()
			local body = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(body)
			local status, error = pcall(w.destroyCollisionBody,w,body)
			assert_false(status,error)
			assert_equal(error,"can't destroy RigidBody.Need CollisionBody")
			rp3d.destroyPhysicsWorld(w)
		end)

		test("destroyRigidBody(collision)", function()
			local w = rp3d.createPhysicsWorld()
			local body = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
			assert_not_nil(body)
			local status, error = pcall(w.destroyRigidBody,w,body)
			assert_false(status,error)
			assert_equal(error,"can't destroy CollisionBody.Need RigidBody")
			rp3d.destroyPhysicsWorld(w)
		end)
	end)
end
