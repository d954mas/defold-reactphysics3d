local UTILS = require "tests.test_utils"

local array = nil
local array_normals = nil
local function init_mesh()
	local vertices = {}
	vertices[0] = -3;
	vertices[1] = -3;
	vertices[2] = 3;
	vertices[3] = 3;
	vertices[4] = -3;
	vertices[5] = 3;
	vertices[6] = 3;
	vertices[7] = -3;
	vertices[8] = -3;

	local indices = {}
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	array = rp3d.createTriangleVertexArray(vertices, indices)

	local normals = {}
	normals[0] = 1;
	normals[1] = 0;
	normals[2] = 0;
	normals[3] = 1;
	normals[4] = 0;
	normals[5] = 0;
	normals[6] = 1
	normals[7] = 0;
	normals[8] = 0;

	array_normals = rp3d.createTriangleVertexArray(vertices, indices, normals)
end

local function dispose_mesh()
	rp3d.destroyTriangleVertexArray(array)
	rp3d.destroyTriangleVertexArray(array_normals)
end

return function()
	describe("TriangleVertexArray", function()
		before(function()
			UTILS.set_env(getfenv(1))
			init_mesh()
		end)
		after(function()
			dispose_mesh()
		end)

		test("create/destroy triangleVertexArray", function()
			assert_not_nil(array)
			dispose_mesh()
			init_mesh()
		end)

		test("create bad", function()
			local vertices = {}
			vertices[0] = -3;
			vertices[1] = -3;
			vertices[2] = 3;
			vertices[3] = 3;
			vertices[4] = -3;
			vertices[5] = 3;
			vertices[6] = 3;
			vertices[7] = -3;
			vertices[8] = -3;

			local indices = {}
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 2;

			vertices[9] = 2
			local status, error = pcall(rp3d.createTriangleVertexArray, vertices, indices)
			assert_false(status)
			UTILS.test_error(error, "vertices bad number.Should be power of 3")
			vertices[9] = nil

			indices[3] = 1;
			status, error = pcall(rp3d.createTriangleVertexArray, vertices, indices)
			assert_false(status)
			UTILS.test_error(error, "indices bad number.Should be power of 3")
			indices[3] = nil

			local normals = {}
			normals[0] = 1;
			normals[1] = 0;
			normals[2] = 0;
			normals[3] = 1;
			normals[4] = 0;
			normals[5] = 0;
			normals[6] = 1
			normals[7] = 0;
			normals[8] = 0;

			normals[9] = 1;
			status, error = pcall(rp3d.createTriangleVertexArray, vertices, indices, normals)
			assert_false(status)
			UTILS.test_error(error, "normals count not same as vertices")
			normals[9] = nil
		end)

		test("getNbVertices()", function()
			assert_equal(array:getNbVertices(),3)
		end)
		test("getNbTriangles()", function()
			assert_equal(array:getNbTriangles(),1)
		end)
		test("getTriangleVertices()", function()
			local t0 = array:getTriangleVertices(0)
			assert_equal(#t0,3)
			assert_equal_v3(t0[1],vmath.vector3(-3,-3,3))
			assert_equal_v3(t0[2],vmath.vector3(3,-3,3))
			assert_equal_v3(t0[3],vmath.vector3(3,-3,-3))
			local status, error = pcall(array.getTriangleVertices,array,1)
			assert_false(status)
			UTILS.test_error(error,"Bad idx:1. Triangles:1")
		end)

		test("getTriangleVerticesNormals()", function()
			local t0 = array:getTriangleVerticesNormals(0)
			assert_equal(#t0,3)
			assert_equal_v3(t0[1],vmath.vector3(0,1,0))
			assert_equal_v3(t0[2],vmath.vector3(0,1,0))
			assert_equal_v3(t0[3],vmath.vector3(0,1,0))
			local status, error = pcall(array.getTriangleVerticesNormals,array,1)
			assert_false(status)
			UTILS.test_error(error,"Bad idx:1. Triangles:1")
		end)
		test("tostring()", function()
			assert_equal(tostring(array):sub(1, 25), "rp3d::TriangleVertexArray")
		end)
	end)

end
