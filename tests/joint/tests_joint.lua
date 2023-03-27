local UTILS = require "tests.test_utils"

local M = {}

---@param joint Rp3dJoint
function M.test_joint(joint, data)
	assert_not_nil(joint)
	assert_equal(joint:getType(),data.type)
end

function M.set_env(env)
	for k, v in pairs(M) do
		if (type(v) == "function" and k ~= "set_env") then
			setfenv(v,env)
		end
	end
end


return M
