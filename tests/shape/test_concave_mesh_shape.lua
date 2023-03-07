local UTILS = require "tests.test_utils"

local array = nil
local mesh = nil
---@type Rp3dConcaveMeshShape
local shape = nil
local function init_mesh()
	local res = go.get("/meshes#castle", "vertices")
	local buf = resource.get_buffer(res)
	array = rp3d.createTriangleVertexArrayFromMeshVerticesCopy(buf)
	mesh = rp3d.createTriangleMesh()
	mesh:addSubpart(array)
	shape = rp3d.createConcaveMeshShape(mesh)
end

local function dispose_mesh()
	rp3d.destroyConcaveMeshShape(shape)
	rp3d.destroyTriangleMesh(mesh)
	rp3d.destroyTriangleVertexArray(array)

end

return function()
	describe("ConcaveMeshShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
			init_mesh()
		end)
		after(function()
			dispose_mesh()
		end)

		test("create/destroy", function()
			assert_not_nil(mesh)
			assert_not_nil(shape)
			dispose_mesh()
			init_mesh()
			assert_equal(shape:getName(), rp3d.CollisionShapeName.TRIANGLE_MESH)
		end)

		test("set/get Scale()", function()
			UTILS.test_method_get_set(shape, "Scale",
					{ v3 = true,
					  values = { vmath.vector3(1), vmath.vector3(3), vmath.vector3(1, 2, 3) }
					})
		end)

		test("getNbSubparts", function()
			assert_equal(shape:getNbSubparts(), 1)
		end)

		test("getNbTriangles()", function()
			assert_equal(shape:getNbTriangles(0), 1114)

			local status, error = pcall(shape.getNbTriangles, shape, 1)
			assert_false(status)
			UTILS.test_error(error,"Bad subPart:1. Subparts:1")

		end)

		test("getTriangleVerticesIndices()", function()
			assert_equal(shape:getNbTriangles(0), 1114)

			local t1 = shape:getTriangleVerticesIndices(0,0)
			assert_equal(#t1,3)
			assert_equal(t1[1],0)
			assert_equal(t1[2],1)
			assert_equal(t1[3],2)

			local t2 =shape:getTriangleVerticesIndices(0,1113)
			assert_equal(#t2,3)
			assert_equal(t2[1],3339)
			assert_equal(t2[2],3340)
			assert_equal(t2[3],3341)

			local status, error = pcall(shape.getTriangleVerticesIndices, shape, 1,0)
			assert_false(status)
			UTILS.test_error(error,"Bad subPart:1. Subparts:1")

			status, error = pcall(shape.getTriangleVerticesIndices, shape, 0,1114)
			assert_false(status)
			UTILS.test_error(error,"Bad triangle:1114. Triangles:1114")

		end)
	end)

end
