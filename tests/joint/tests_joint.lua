local UTILS = require "tests.test_utils"

local M = {}

---@param joint Rp3dJoint
function M.test_joint(joint, data)
	assert_not_nil(joint)
	assert_equal(joint:getType(),data.type)
	assert_equal(joint:getBody1(),data.body1)
	assert_equal(joint:getBody2(),data.body2)
	assert_type(joint:getReactionForce(1/60),"userdata")
	assert_type(joint:getReactionTorque(1/60),"userdata")
	assert_type(joint:getEntityId(),"number")
	if (data.isCollisionEnabled ~= nil) then
		assert_equal(joint:isCollisionEnabled(), data.isCollisionEnabled)
	else
		assert_true(joint:isCollisionEnabled())
	end
end

function M.set_env(env)
	for k, v in pairs(M) do
		if (type(v) == "function" and k ~= "set_env") then
			setfenv(v,env)
		end
	end
end


return M
