local DEFTEST = require "deftest.deftest"
local TELESCOPE = require "deftest.telescope"

local TEST_RP3D = require "tests.test_rp3d"
local TEST_WORLD = require "tests.test_world"
local TEST_COLLISION_SHAPE = require "tests.shape.test_collision_shape"
local TEST_BOX_SHAPE = require "tests.shape.test_box_shape"
local TEST_COLLISION_BODY = require "tests.shape.test_collision_body"
local TEST_WORLD_SETTINGS = require "tests.test_world_settings"
local TEST_AABB = require "tests.shape.test_aabb"
local M = {}

function M.run()
	TELESCOPE.make_assertion(
			"equals_v3",
			function(_, a, b) return string.format(TELESCOPE.assertion_message_prefix .. "'%s' to be equal to '%s'", a, b) end,
			function(a, b)
				if (type(a) ~= "userdata" or type(b) ~= "userdata") then assert("not v3") end
				return a.x == b.x and a.y == b.y and a.z == b.z
			end
	)
	TELESCOPE.make_assertion(
			"equal_v3",
			function(_, a, b) return string.format(TELESCOPE.assertion_message_prefix .. "'%s' to be equal to '%s'", tostring(a), tostring(b)) end,
			function(a, b, epsilon)
				epsilon = epsilon or 0.0000001
				if (type(a) ~= "userdata" or type(b) ~= "userdata") then assert("not v3") end
				local dx = math.abs(a.x - b.x)
				local dy = math.abs(a.y - b.y)
				local dz = math.abs(a.z - b.z)
				return dx <= epsilon and dy <= epsilon and dz <= epsilon
			end
	)
	TELESCOPE.make_assertion(
			"equal_quat",
			function(_, a, b) return string.format(TELESCOPE.assertion_message_prefix .. "'%s' to be equal to '%s'", tostring(a), tostring(b)) end,
			function(a, b, epsilon)
				epsilon = epsilon or 0.0000001
				if (type(a) ~= "userdata" or type(b) ~= "userdata") then assert("not quat") end
				local dx = math.abs(a.x - b.x)
				local dy = math.abs(a.y - b.y)
				local dz = math.abs(a.z - b.z)
				local dw = math.abs(a.w - b.w)
				return dx <= epsilon and dy <= epsilon and dz <= epsilon and dw <= epsilon
			end
	)
	TELESCOPE.make_assertion(
			"equal_float",
			function(_, a, b) return string.format(TELESCOPE.assertion_message_prefix .. "'%s' to be equal to '%s'", a, b) end,
			function(a, b)
				if (type(a) ~= "number" or type(b) ~= "number") then assert("not v3") end
				local d = math.abs(a - b)
				return d >= 0 and d <= 0.0000001
			end
	)
	DEFTEST.add(TEST_RP3D)
	DEFTEST.add(TEST_WORLD)
	DEFTEST.add(TEST_WORLD_SETTINGS)
	DEFTEST.add(TEST_COLLISION_SHAPE)
	DEFTEST.add(TEST_BOX_SHAPE)
	DEFTEST.add(TEST_AABB)
	DEFTEST.add(TEST_COLLISION_BODY)
	DEFTEST.run()
end

return M