local UTILS = require "tests.test_utils"
local TEST_JOINT = require "tests.joint.tests_joint"

---@type Rp3dPhysicsWorld
local w
---@type Rp3dRigidBody
local body1
---@type Rp3dRigidBody
local body2

return function()
	describe("BallAndSocketJoint", function()
		before(function()
			UTILS.set_env(getfenv(1))
			TEST_JOINT.set_env(getfenv(1))

			w = rp3d.createPhysicsWorld()
			body1 = w:createRigidBody({ position = vmath.vector3(-10, 0, 0), quat = vmath.quat() })
			body2 = w:createRigidBody({ position = vmath.vector3(10, 0, 0), quat = vmath.quat() })
		end)
		after(function()
			w:destroyRigidBody(body1)
			w:destroyRigidBody(body2)
			rp3d.destroyPhysicsWorld(w)
		end)

		test("create", function()
			local info = rp3d.createBallAndSocketJointInfoWorldSpace(body1, body2, vmath.vector3(0, 1, 0))
			local joint = w:createJoint(info)
			TEST_JOINT.test_joint(joint, { type = rp3d.JointType.BALLSOCKETJOINT, body1 = body1, body2 = body2 })
		end)


	end)
end
