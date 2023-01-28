local UTILS = require "tests.test_utils"


local shapes = nil
local function init_shapes()
	shapes = {
		box = rp3d.createBoxShape(vmath.vector3(1,1,1))
	}
end

local function dispose_shapes()
	rp3d.destroyBoxShape(shapes.box)

	shapes = nil

end

local function assert_two_vectors(v1_result,v2_result,v1,v2)
	assert_equal_v3(v1_result,v1)
	assert_equal_v3(v2_result,v2)
end

return function()
	describe("ConvexPolyhedronShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
			setfenv(assert_two_vectors,getfenv(1))
			init_shapes()
		end)
		after(function()
			dispose_shapes()
		end)


		test("getNbFaces()", function()
			assert_equal(shapes.box:getNbFaces(),6)
		end)

		test("getFace()", function()
			local status,error = pcall(shapes.box.getFace,shapes.box,-1)
			assert_false(status)
			UTILS.test_error(error,"bad faceIndex:-1")
			status,error = pcall(shapes.box.getFace,shapes.box,6)
			assert_false(status)
			UTILS.test_error(error,"bad faceIndex:6")

			local face = shapes.box:getFace(0)
			assert_not_nil(face)
			assert_equal(face.edgeIndex,4)
			assert_equal(#face.faceVertices,4)

			face = shapes.box:getFace(5)
			assert_not_nil(face)
			assert_equal(face.edgeIndex,23)
			assert_equal(#face.faceVertices,4)

		end)

		test("getNbVertices()", function()
			assert_equal(shapes.box:getNbVertices(),8)
		end)

		test("getVertex()", function()
			local status,error = pcall(shapes.box.getVertex,shapes.box,-1)
			assert_false(status)
			UTILS.test_error(error,"bad vertexIndex:-1")
			status,error = pcall(shapes.box.getVertex,shapes.box,8)
			assert_false(status)
			UTILS.test_error(error,"bad vertexIndex:8")

			local vertex = shapes.box:getVertex(0)
			assert_not_nil(vertex)
			assert_equal(vertex.edgeIndex,15)
			assert_equal(vertex.vertexPointIndex,0)

			vertex = shapes.box:getVertex(7)
			assert_not_nil(vertex)
			assert_equal(vertex.edgeIndex,21)
			assert_equal(vertex.vertexPointIndex,7)


		end)

	end)
end
