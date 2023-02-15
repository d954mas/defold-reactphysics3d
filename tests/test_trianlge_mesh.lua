local UTILS = require "tests.test_utils"

local array = nil
local array_normals = nil
local function init_array()
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

local function dispose_array()
	rp3d.destroyTriangleVertexArray(array)
	rp3d.destroyTriangleVertexArray(array_normals)
end

return function()
	describe("TriangleMesh", function()
		before(function()
			UTILS.set_env(getfenv(1))
			init_array()
		end)
		after(function()
			dispose_array()
		end)

		test("create/destroy triangleMesh", function()
			assert_not_nil(array)
			local mesh = rp3d.createTriangleMesh()

			rp3d.destroyTriangleMesh(mesh)
			assert_equal(mesh.__userdata, nil)
		end)

		test("subpart", function()
			assert_not_nil(array)
			local mesh = rp3d.createTriangleMesh()

			mesh:addSubpart(array)
			assert_equal(mesh:getNbSubparts(),1)

			assert_equal(mesh:getSubpart(0),array)

			local status, error = pcall(mesh.getSubpart, mesh,1)
			assert_false(status)
			UTILS.test_error(error,"bad idx:1. Size:1")

			rp3d.destroyTriangleMesh(mesh)
			assert_equal(mesh.__userdata, nil)
		end)


		test("tostring()", function()
			local mesh = rp3d.createTriangleMesh()
			assert_equal(tostring(mesh):sub(1, 18), "rp3d::TriangleMesh")
			rp3d.destroyTriangleMesh(mesh)
		end)
	end)

end
