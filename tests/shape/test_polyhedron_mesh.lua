local UTILS = require "tests.test_utils"

local mesh = nil
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
	vertices[9] = -3;
	vertices[10] = -3;
	vertices[11] = -3;
	vertices[12] = -3;
	vertices[13] = 3;
	vertices[14] = 3;
	vertices[15] = 3;
	vertices[16] = 3;
	vertices[17] = 3;
	vertices[18] = 3;
	vertices[19] = 3;
	vertices[20] = -3;
	vertices[21] = -3;
	vertices[22] = 3;
	vertices[23] = -3;

	local indices = {}
	indices[0] = 0;
	indices[1] = 3;
	indices[2] = 2;
	indices[3] = 1;
	indices[4] = 4;
	indices[5] = 5;
	indices[6] = 6;
	indices[7] = 7;
	indices[8] = 0;
	indices[9] = 1;
	indices[10] = 5;
	indices[11] = 4;
	indices[12] = 1;
	indices[13] = 2;
	indices[14] = 6;
	indices[15] = 5;
	indices[16] = 2;
	indices[17] = 3;
	indices[18] = 7;
	indices[19] = 6;
	indices[20] = 0;
	indices[21] = 4;
	indices[22] = 7;
	indices[23] = 3;

	-- Description of the six faces of the convex mesh
	local polygonFaces = {}

	for f = 0, 5 do
		--// First vertex of the face in the indices array
		local face = {
			nbVertices = 4;
			indexBase = f * 4
		}
		polygonFaces[f] = face
	end
	mesh = rp3d.createPolyhedronMesh(vertices, indices, polygonFaces)

end

local function dispose_mesh()
	rp3d.destroyPolyhedronMesh(mesh)
end

return function()
	describe("PolyhedronShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
			init_mesh()
		end)
		after(function()
			dispose_mesh()
		end)

		test("create/destroy polyhedrone", function()
			assert_not_nil(mesh)
			dispose_mesh()
			init_mesh()
		end)

		test("create from buffer", function()
			local res = go.get("/meshes#box", "vertices")
			local buf = resource.get_buffer(res)
			local mesh_b = rp3d.createPolyhedronMeshFromBufferClone(buf)
			assert_not_nil(mesh_b)
			rp3d.destroyPolyhedronMesh(mesh_b)
		end)

		test("tostring()", function()
			assert_equal(tostring(mesh):sub(1, 20), "rp3d::PolyhedronMesh")
		end)
	end)

end
