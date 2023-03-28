local UTILS = require "tests.test_utils"
local TEST_JOINT = require "tests.joint.tests_joint"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dRigidBody
local body1
---@type Rp3dRigidBody
local body2
---@type Rp3dBallAndSocketJoint
local joint

return function()
	describe("BallAndSocketJoint", function()
		before(function()
			UTILS.set_env(getfenv(1))
			TEST_JOINT.set_env(getfenv(1))

			w = rp3d.createPhysicsWorld()
			body1 = w:createRigidBody({ position = vmath.vector3(-10, 0, 0), quat = vmath.quat() })
			body2 = w:createRigidBody({ position = vmath.vector3(10, 0, 0), quat = vmath.quat() })
			local info = rp3d.createBallAndSocketJointInfoWorldSpace(body1, body2, vmath.vector3(0, 1, 0))
			joint = w:createJoint(info)
		end)
		after(function()
			w:destroyRigidBody(body1)
			w:destroyRigidBody(body2)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("create", function()

			TEST_JOINT.test_joint(joint, { type = rp3d.JointType.BALLSOCKETJOINT, body1 = body1, body2 = body2 })
		end)

		test("destroy", function()
			w:destroyJoint(joint)

			local status, error = pcall(joint.getType, joint)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Joint was destroyed")
		end)

		test("destroyBody", function()
			local body1 = w:createRigidBody({ position = vmath.vector3(-10, 0, 0), quat = vmath.quat() })
			local body2 = w:createRigidBody({ position = vmath.vector3(10, 0, 0), quat = vmath.quat() })
			local info = rp3d.createBallAndSocketJointInfoWorldSpace(body1, body2, vmath.vector3(0, 1, 0))
			local joint = w:createJoint(info)

			w:destroyRigidBody(body1)

			local status, error = pcall(joint.getType, joint)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Joint was destroyed")
		end)

		test("destroyWorld", function()
			local w = rp3d.createPhysicsWorld()
			local body1 = w:createRigidBody({ position = vmath.vector3(-10, 0, 0), quat = vmath.quat() })
			local body2 = w:createRigidBody({ position = vmath.vector3(10, 0, 0), quat = vmath.quat() })
			local info = rp3d.createBallAndSocketJointInfoWorldSpace(body1, body2, vmath.vector3(0, 1, 0))
			local joint = w:createJoint(info)

			rp3d.destroyPhysicsWorld(w)

			local status, error = pcall(joint.getType, joint)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Joint was destroyed")
		end)

		test("isEnabled/enableConeLimit", function()
			UTILS.test_method_get_set(joint, "ConeLimit",
					{ getter_full = "isConeLimitEnabled",
					  setter_full = "enableConeLimit",
					  values = { false, true, false }
					})
		end)

		test("set/get ConeLimitHalfAngle", function()
			UTILS.test_method_get_set(joint, "ConeLimitHalfAngle",
					{
						float = true, epsilwon = 0.001,
						values = { 1, 2, math.pi, math.pi * 5 }
					})
		end)

		test("getConeHalfAngle", function()
			assert_equal_float( 0.1993366, joint:getConeHalfAngle())
		end)


	end)
end
