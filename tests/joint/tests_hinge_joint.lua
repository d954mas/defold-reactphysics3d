local UTILS = require "tests.test_utils"
local TEST_JOINT = require "tests.joint.tests_joint"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dRigidBody
local body1
---@type Rp3dRigidBody
local body2
---@type Rp3dHingeJoint
local joint

return function()
	describe("HingeJoint", function()
		before(function()
			UTILS.set_env(getfenv(1))
			TEST_JOINT.set_env(getfenv(1))

			w = rp3d.createPhysicsWorld()
			body1 = w:createRigidBody({ position = vmath.vector3(-10, 0, 0), quat = vmath.quat() })
			body2 = w:createRigidBody({ position = vmath.vector3(10, 0, 0), quat = vmath.quat() })
			local info = rp3d.createHingeJointInfoWorldSpace(body1, body2, vmath.vector3(0, 1, 0),vmath.vector3(0, 1, 0))
			joint = w:createJoint(info)
			assert_not_nil(joint)
		end)
		after(function()
			w:destroyRigidBody(body1)
			w:destroyRigidBody(body2)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("create", function()
			assert_not_nil(joint)
			TEST_JOINT.test_joint(joint, { type = rp3d.JointType.HINGEJOINT, body1 = body1, body2 = body2 })
		end)

		test("destroy", function()
			w:destroyJoint(joint)

			local status, error = pcall(joint.getType, joint)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Joint was destroyed")
		end)


		test("isLimitEnabled/enableLimit", function()
			UTILS.test_method_get_set(joint, "isLimitEnabled",
					{ getter_full = "isLimitEnabled",
					  setter_full = "enableLimit",
					  values = { false, true, false }
					})
		end)

		test("isMotorEnabled/enableMotor", function()
			UTILS.test_method_get_set(joint, "isMotorEnabled",
					{ getter_full = "isMotorEnabled",
					  setter_full = "enableMotor",
					  values = { false, true, false }
					})
		end)

		test("get/set MinAngleLimit", function()
			UTILS.test_method_get_set(joint, "MinAngleLimit",
					{
						float = true,
					  values = {  -1,0, -2, -math.pi, -math.pi * 2  }
					})
		end)

		test("get/set MaxAngleLimit", function()
			UTILS.test_method_get_set(joint, "MaxAngleLimit",
					{
						float = true,
						values = { 1,0, 2, math.pi, math.pi * 2 }
					})
		end)

		test("get/set MotorSpeed", function()
			UTILS.test_method_get_set(joint, "MotorSpeed",
					{	float = true,
						values = { -1,0, 2, math.pi, math.pi * 2 }
					})
		end)

		test("get/set MaxMotorTorque", function()
			UTILS.test_method_get_set(joint, "MaxMotorTorque",
					{ 	float = true,
						values = { 1,0, 2, math.pi, math.pi * 2 }
					})
		end)

		test("getMotorTorque", function()
			assert_equal_float(0,joint:getMotorTorque(1/60))
		end)

		test("getAngle", function()
			assert_equal_float(0, joint:getAngle())
		end)



	end)
end
