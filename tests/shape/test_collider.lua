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

		test("toString()", function()
			assert_equal(tostring(collider):sub(1,14), "rp3d::Collider")
		end)


	end)
end
