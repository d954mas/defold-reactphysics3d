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
	describe("CollsionShape", function()
		before(function()
			UTILS.set_env(getfenv(1))
			setfenv(assert_two_vectors,getfenv(1))
			init_shapes()
		end)
		after(function()
			dispose_shapes()
		end)


		test("getName()", function()
			assert_equal(shapes.box:getName(), rp3d.CollisionShapeName.BOX)
		end)

		test("getType()", function()
			assert_equal(shapes.box:getType(), rp3d.CollisionShapeType.CONVEX_POLYHEDRON)
		end)

		test("isPolyhedron()", function()
			assert_equal(shapes.box:isPolyhedron(), true)
		end)

		test("isConvex()", function()
			assert_equal(shapes.box:isConvex(), true)
		end)

		test("getLocalBounds()", function()
			assert_two_vectors(vmath.vector3(-1),vmath.vector3(1),shapes.box:getLocalBounds())
		end)

		test("getId()", function()
			assert_type(shapes.box:getId(),"number")
		end)
		test("getLocalInertiaTensor()", function()
			assert_type(shapes.box:getLocalInertiaTensor(1),"userdata")
		end)

		test("getVolume()", function()
			assert_type(shapes.box:getVolume(),"number")
		end)
		test("ComputeAABB()", function()
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = shapes.box:computeAABB({position = pos,quat = quat})
			assert_equal("rp3d::AABB",tostring(aabb):sub(1,10))
		end)

		test("toString()", function()
			assert_equal("BoxShape", tostring(shapes.box):sub(1,8))
		end)




	end)
end
