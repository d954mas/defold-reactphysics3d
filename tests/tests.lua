local DEFTEST = require "deftest.deftest"
local TELESCOPE = require "deftest.telescope"

local TEST_RP3D = require "tests.test_rp3d"
local TEST_WORLD = require "tests.test_world"
local TEST_COLLISION_SHAPE = require "tests.shape.test_collision_shape"
local TEST_CONVEX_SHAPE = require "tests.shape.test_convex_shape"
local TEST_CONVEX_POLYHEDRON_SHAPE = require "tests.shape.test_convex_polyhedron_shape"
local TEST_BOX_SHAPE = require "tests.shape.test_box_shape"
local TEST_SPHERE_SHAPE = require "tests.shape.test_sphere_shape"
local TEST_CAPSULE_SHAPE = require "tests.shape.test_capsule_shape"
local TEST_HEIGHTFIELD_SHAPE = require "tests.shape.test_heighfield_shape"
local TEST_COLLISION_BODY = require "tests.test_collision_body"
local TEST_RIGID_BODY = require "tests.test_rigid_body"
local TEST_WORLD_SETTINGS = require "tests.test_world_settings"
local TEST_AABB = require "tests.test_aabb"
local TEST_COLLIDER = require "tests.test_collider"
local TEST_DEBUG_RENDERER = require "tests.test_debug_renderer"
local TEST_POLYHEDRON_MESH = require "tests.test_polyhedron_mesh"
local TEST_TRIANGLE_VERTEX_ARRAY = require "tests.test_trianlge_vertex_array_mesh"
local TEST_CONVEX_MESH_SHAPE = require "tests.shape.test_convex_mesh_shape"
local TEST_TRIANGLE_MESH = require "tests.test_trianlge_mesh"
local TEST_CONCAVE_MESH_SHAPE = require "tests.shape.test_concave_mesh_shape"
local TEST_CONCAVE_SHAPE = require "tests.shape.test_concave_shape"

local TEST_BALL_AND_SOCKET_JOINT_INFO = require "tests.joint.tests_ball_and_socket_joint_info"
local TEST_BALL_AND_SOCKET_JOINT = require "tests.joint.tests_ball_and_socket_joint"
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
	DEFTEST.add(TEST_CONVEX_SHAPE)
	DEFTEST.add(TEST_CONVEX_POLYHEDRON_SHAPE)
	DEFTEST.add(TEST_BOX_SHAPE)
	DEFTEST.add(TEST_SPHERE_SHAPE)
	DEFTEST.add(TEST_CAPSULE_SHAPE)
	DEFTEST.add(TEST_CONVEX_MESH_SHAPE)
	DEFTEST.add(TEST_HEIGHTFIELD_SHAPE)
	DEFTEST.add(TEST_AABB)
	DEFTEST.add(TEST_COLLISION_BODY)
	DEFTEST.add(TEST_RIGID_BODY)
	DEFTEST.add(TEST_COLLIDER)
	DEFTEST.add(TEST_DEBUG_RENDERER)
	DEFTEST.add(TEST_POLYHEDRON_MESH)
	DEFTEST.add(TEST_TRIANGLE_VERTEX_ARRAY)
	DEFTEST.add(TEST_TRIANGLE_MESH)
	DEFTEST.add(TEST_CONCAVE_SHAPE)
	DEFTEST.add(TEST_CONCAVE_MESH_SHAPE)
	DEFTEST.add(TEST_BALL_AND_SOCKET_JOINT_INFO)
	DEFTEST.add(TEST_BALL_AND_SOCKET_JOINT)
	DEFTEST.run()
end

function update(self, dt)
	DEFTEST.update(dt)
end

return M