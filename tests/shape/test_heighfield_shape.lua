local UTILS = require "tests.test_utils"
local PERLIN = require "libs.perlin"

local NB_POINTS_WIDTH = 90;
local NB_POINTS_LENGTH = 100;
local DATA = {}

---@type Rp3dHeightFieldShape
local shape = nil
local function init_shape()
	DATA = {}
	local min = 0
	local max = 0
	local width = (NB_POINTS_WIDTH - 1);
	local length = (NB_POINTS_LENGTH - 1);
	local persistence = 9;
	local frequency = 0.28;
	local amplitude = 12;
	local octaves = 1;
	local randomseed = 23;
	local perlinNoise = PERLIN(persistence, frequency, amplitude, octaves, randomseed);

	for i = 0, NB_POINTS_WIDTH-1 do
		for j = 0, NB_POINTS_LENGTH-1 do
			local arrayIndex = i * NB_POINTS_LENGTH+j;
			local h = perlinNoise:GetHeight(-width * 0.5 + i, -length * 0.5 + j)

			if (i == 0 and j == 0) then
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

		test("getNbRows()", function()
			assert_equal(shape:getNbRows(), 100)
		end)

		test("getNbColumns()", function()
			assert_equal(shape:getNbColumns(), 90)
		end)

		test("getVertexAt()", function()
			assert_type(shape:getVertexAt(0, 0), "userdata")
			assert_type(shape:getVertexAt(89, 99), "userdata")
			local status, error = pcall(shape.getVertexAt,shape,90, 99)
			assert_false(status)
			UTILS.test_error(error, 'Bad x:90. Columns:90.')

			status, error = pcall(shape.getVertexAt,shape,89, 100)
			assert_false(status)
			UTILS.test_error(error, 'Bad y:100. Rows:100.')
		end)

		test("getHeightAt()", function()
			assert_type(shape:getHeightAt(0, 0), "number")
			assert_type(shape:getHeightAt(89, 99), "number")
			local status, error = pcall(shape.getHeightAt,shape,90, 99)
			assert_false(status)
			UTILS.test_error(error, 'Bad x:90. Columns:90.')

			status, error = pcall(shape.getHeightAt,shape,89, 100)
			assert_false(status)
			UTILS.test_error(error, 'Bad y:100. Rows:100.')
		end)

		test("getHeightDataType()", function()
			assert_equal(shape:getHeightDataType(),rp3d.HeightDataType.HEIGHT_FLOAT_TYPE)
		end)


	end)
end
