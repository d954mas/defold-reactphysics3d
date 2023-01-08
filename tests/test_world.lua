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

		test("enums exist", function()
			local function test_enum(enum_name, config)
				assert_not_nil(rp3d[enum_name])
				for k, v in pairs(config) do
					assert_equal(rp3d[enum_name][k], v)
				end
			end
			test_enum("ContactsPositionCorrectionTechnique", { BAUMGARTE_CONTACTS = 0, SPLIT_IMPULSES = 1 })
		end)


	end)
end
