local UTILS = require "tests.test_utils"
local TEST_JOINT = require "tests.joint.tests_joint"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dRigidBody
local body1
---@type Rp3dRigidBody
local body2
---@type Rp3dFixedJoint
local joint

return function()
	describe("Rp3dFixedJoint", function()
		before(function()
			UTILS.set_env(getfenv(1))
			TEST_JOINT.set_env(getfenv(1))

			w = rp3d.createPhysicsWorld()
			body1 = w:createRigidBody({ position = vmath.vector3(-10, 0, 0), quat = vmath.quat() })
			body2 = w:createRigidBody({ position = vmath.vector3(10, 0, 0), quat = vmath.quat() })
			local info = rp3d.createFixedJointInfoWorldSpace(body1, body2, vmath.vector3(0, 1, 0))
			joint = w:createJoint(info)
		end)
		after(function()
			w:destroyRigidBody(body1)
			w:destroyRigidBody(body2)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("create", function()
			TEST_JOINT.test_joint(joint, { type = rp3d.JointType.FIXEDJOINT, body1 = body1, body2 = body2 })
		end)

		test("destroy", function()
			w:destroyJoint(joint)

			local status, error = pcall(joint.getType, joint)
			assert_false(status)
			UTILS.test_error(error, "rp3d::Joint was destroyed")
		end)




	end)
end
