local UTILS = require "tests.test_utils"
local PERLIN = require "libs.perlin"

PERLIN.init()

local NB_POINTS_WIDTH = 100;
local NB_POINTS_LENGTH = 100;
local DATA = {}

---@type Rp3dCollisionShape
local shape = nil
local function init_shape()
	DATA = {}
	local min = 0
	local max = 0
	local width = (NB_POINTS_WIDTH - 1);
	local length = (NB_POINTS_LENGTH - 1);

	for i = 1, NB_POINTS_WIDTH do
		for j = 1, NB_POINTS_LENGTH do
			local arrayIndex = (j - 1) * NB_POINTS_WIDTH + i;
			local h = PERLIN.noise(0, -width * 0.5 + i, -length * 0.5 + j)

			if (i == 1 and j == 1) then
				min = h
				max = h
			end

			min = math.min(min, h)
			max = math.max(max, h)
			DATA[arrayIndex] = h
		end
	end
	shape = rp3d.createHeightFieldShape(NB_POINTS_WIDTH, NB_POINTS_LENGTH, min, max, DATA, rp3d.HeightDataType.HEIGHT_FLOAT_TYPE)
	assert(shape)
end

local function dispose_shape()
	rp3d.destroyHeightFieldShape(shape)
	shape = nil
end

return function()
	describe("HeightFieldShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
			init_shape()
		end)
		after(function()
			dispose_shape()
		end)

		test("create/destroy HeightFieldShape", function()
			assert_not_nil(shape)
			assert_equal(rp3d.CollisionShapeName.HEIGHTFIELD, shape:getName())

			rp3d.destroyHeightFieldShape(shape)
			local status, error = pcall(rp3d.destroyHeightFieldShape, shape)
			assert_false(status)
			UTILS.test_error(error, "rp3d::CollisionShape was destroyed")
			init_shape()
		end)


	end)
end
