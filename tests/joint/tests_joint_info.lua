local UTILS = require "tests.test_utils"

local M = {}

---@param jointInfo Rp3dJointInfo
function M.test_joint_info(jointInfo, data)
	assert_equal(jointInfo.body1, data.body1)
	assert_equal(jointInfo.body2, data.body2)
	assert_equal(jointInfo.type, data.type)
	assert_equal(jointInfo.positionCorrectionTechnique, data.positionCorrectionTechnique or rp3d.JointsPositionCorrectionTechnique.NON_LINEAR_GAUSS_SEIDEL)
	if (data.isCollisionEnabled ~= nil) then
		assert_equal(jointInfo.isCollisionEnabled, data.isCollisionEnabled)
	else
		assert_true(jointInfo.isCollisionEnabled)
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
