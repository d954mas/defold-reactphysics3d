local UTILS = require "tests.test_utils"

local array = nil
local mesh = nil
---@type Rp3dConcaveShape
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

		test("create", function()
			local shape_scale = rp3d.createConcaveMeshShape(mesh, vmath.vector3(2))
			assert_equal_v3(shape_scale:getScale(),vmath.vector3(2))
		end)
		test("get/set RaycastTestType()", function()
			assert_equal(shape:getRaycastTestType(),rp3d.TriangleRaycastSide.FRONT)
			shape:setRaycastTestType(rp3d.TriangleRaycastSide.BACK)
			assert_equal(shape:getRaycastTestType(),rp3d.TriangleRaycastSide.BACK)
		end)

		test("set/get Scale()", function()
			UTILS.test_method_get_set(shape, "Scale",
					{ v3 = true,
					  values = { vmath.vector3(1), vmath.vector3(3), vmath.vector3(1,2,3) }
					})
		end)
	end)

end
