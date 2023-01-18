local UTILS = require "tests.test_utils"

return function()
	describe("AABB", function()
		before(function()
			UTILS.set_env(getfenv(1))

		end)
		after(function()

		end)

		test("getAABB()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_equal("rp3d::AABB", tostring(aabb):sub(1, 10))
			rp3d.destroyBoxShape(box)
		end)

		test("getCenter()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3(5, 6, 7)
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_equal_v3(vmath.vector3(5, 6, 7), aabb:getCenter())
			aabb:setMax(vmath.vector3(8, 9, 10))
			assert_equal_v3(vmath.vector3(6, 7, 8), aabb:getCenter())

			rp3d.destroyBoxShape(box)
		end)

		test("Set/Get Min()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3(0)
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			rp3d.destroyBoxShape(box)
			UTILS.test_method_get_set(aabb, "Min",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, -10, 0), vmath.vector3(5, 6, 7) }
					})
		end)
		test("Set/Get Max()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3(0)
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			rp3d.destroyBoxShape(box)
			UTILS.test_method_get_set(aabb, "Max",
					{ v3 = true,
					  values = { vmath.vector3(0, 0, 0), vmath.vector3(0, 10, 0), vmath.vector3(5, 6, 7) }
					})
		end)

		test("getExtent()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_equal_v3(vmath.vector3(2, 2, 2), aabb:getExtent())
			aabb:setMax(vmath.vector3(2, 3, 4))
			assert_equal_v3(vmath.vector3(3, 4, 5), aabb:getExtent())

			rp3d.destroyBoxShape(box)
		end)

		test("inflate()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_equal_v3(vmath.vector3(2, 2, 2), aabb:getExtent())
			aabb:inflate(1, 0.5, 2)
			assert_equal_v3(vmath.vector3(4, 3, 6), aabb:getExtent())

			rp3d.destroyBoxShape(box)
		end)

		test("testCollision()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			local aabb_collide = box:computeAABB({position = vmath.vector3(0.5, 0.5, 0.5), quat = quat})
			local aabb_notcollide = box:computeAABB({position = vmath.vector3(2.01, 0, 0), quat = quat})

			assert_true(aabb:testCollision(aabb))
			assert_true(aabb:testCollision(aabb_collide))
			assert_false(aabb:testCollision(aabb_notcollide))

			rp3d.destroyBoxShape(box)
		end)

		test("getVolume()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_type(aabb:getVolume(), "number")
			rp3d.destroyBoxShape(box)
		end)

		test("mergeWithAABB()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			local aabb2 = box:computeAABB({position=vmath.vector3(10, 0, 5), quat = quat})

			assert_equal_v3(vmath.vector3(-1, -1, -1), aabb:getMin())
			assert_equal_v3(vmath.vector3(1, 1, 1), aabb:getMax())

			aabb:mergeWithAABB(aabb2)
			assert_equal_v3(vmath.vector3(-1, -1, -1), aabb:getMin())
			assert_equal_v3(vmath.vector3(11, 1, 6), aabb:getMax())
			rp3d.destroyBoxShape(box)
		end)
		test("mergeTwoAABBs()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			local aabb_1 = box:computeAABB({position = vmath.vector3(10, 0, 5), quat = quat})
			local aabb_2 = box:computeAABB({position = vmath.vector3(-10, 0, 10), quat = quat})

			assert_equal_v3(vmath.vector3(-1, -1, -1), aabb:getMin())
			assert_equal_v3(vmath.vector3(1, 1, 1), aabb:getMax())

			aabb:mergeTwoAABBs(aabb_1, aabb_2)
			assert_equal_v3(vmath.vector3(-11, -1, 4), aabb:getMin())
			assert_equal_v3(vmath.vector3(11, 1, 11), aabb:getMax())
			rp3d.destroyBoxShape(box)
		end)
		test("contains()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			local aabb_small = box:computeAABB({position = pos, quat = quat})
			aabb_small:inflate(-0.2, -0.2, -0.2)
			local aabb_big = box:computeAABB({position = pos, quat = quat})
			aabb_big:inflate(0.2, 0.2, 0.2)

			assert_true(aabb:contains(aabb_small))
			assert_true(aabb_big:contains(aabb_small))
			assert_true(aabb_big:contains(aabb))

			assert_false(aabb:contains(aabb_big))
			assert_false(aabb_small:contains(aabb_big))
			assert_false(aabb_small:contains(aabb))

			rp3d.destroyBoxShape(box)
		end)

		test("containsPoint()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_true(aabb:containsPoint(vmath.vector3(0, 0, 0)))
			assert_true(aabb:containsPoint(vmath.vector3(0.99, 0.99, 0.99)))
			assert_true(aabb:containsPoint(vmath.vector3(-0.5, 0.5, 0.99)))

			assert_false(aabb:containsPoint(vmath.vector3(1, 1, 2)))
			assert_false(aabb:containsPoint(vmath.vector3(0, 0, -2)))
			assert_false(aabb:containsPoint(vmath.vector3(100, 100, 40)))

			rp3d.destroyBoxShape(box)
		end)

		test("testCollisionTriangleAABB()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			local status, error = pcall(aabb.testCollisionTriangleAABB, aabb, 2)
			assert_false(status)
			UTILS.test_error(error, "variable should be table")

			status, error = pcall(aabb.testCollisionTriangleAABB, aabb, { vmath.vector3() })
			assert_false(status)
			UTILS.test_error(error, "Need 3 points. Get 1")

			assert_true(aabb:testCollisionTriangleAABB({ vmath.vector3(0, 0, 0), vmath.vector3(0.5, 0, 0), vmath.vector3(0.5, 0.5, 0) }))
			assert_false(aabb:testCollisionTriangleAABB({ vmath.vector3(-1, -2, -3), vmath.vector3(-2, -2, -3), vmath.vector3(-1, -2, -2) }))

			rp3d.destroyBoxShape(box)
		end)

		test("testRayIntersect()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			local direction = vmath.normalize(vmath.vector3(1, 1, 1))
			local direction_inv = vmath.vector3(1 / direction.x, 1 / direction.y, 1 / direction.z)
			assert_false(aabb:testRayIntersect(vmath.vector3(-100, -100, -100), direction_inv,50))
			assert_true(aabb:testRayIntersect(vmath.vector3(-100, -100, -100), direction_inv,174))
			assert_true(aabb:testRayIntersect(vmath.vector3(-100, -100, -100), direction_inv,200))
			rp3d.destroyBoxShape(box)
		end)

		test("applyScale()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_equal_v3(vmath.vector3(2),aabb:getExtent())
			aabb:applyScale(vmath.vector3(1))
			assert_equal_v3(vmath.vector3(2),aabb:getExtent())
			aabb:applyScale(vmath.vector3(2))
			assert_equal_v3(vmath.vector3(4),aabb:getExtent())
			aabb:applyScale(vmath.vector3(0.5))
			assert_equal_v3(vmath.vector3(2),aabb:getExtent())
			aabb:applyScale(vmath.vector3(0.5))
			assert_equal_v3(vmath.vector3(1),aabb:getExtent())
		end)

		test("raycast()", function()
			local box = rp3d.createBoxShape(vmath.vector3(1))
			local pos = vmath.vector3()
			local quat = vmath.quat()
			local aabb = box:computeAABB({position = pos, quat = quat})
			assert_equal_v3(vmath.vector3(-1,-1,-1),aabb:raycast({
				point1 = vmath.vector3(-100,-100,-100),
				point2 = vmath.vector3(0,0,0),
				maxFraction = 1
			}),0.0001)

			assert_equal_v3(vmath.vector3(-1,-1,-1),aabb:raycast({
				point1 = vmath.vector3(-100,-100,-100),
				point2 = vmath.vector3(-99,-99,-99),
				maxFraction = 1
			}),0.0001)

			assert_nil(aabb:raycast({
				point1 = vmath.vector3(-100,-100,-100),
				point2 = vmath.vector3(-101,-99,-99),
				maxFraction = 1
			}))

			local status, error = pcall(aabb.raycast,aabb,2)
			assert_false(status)
			UTILS.test_error(error,"ray should be table")

			status, error = pcall(aabb.raycast,aabb,{

			})
			assert_false(status)
			UTILS.test_error(error,"ray need point1")

			status, error = pcall(aabb.raycast,aabb,{
				point1 = vmath.vector3()
			})
			assert_false(status)
			UTILS.test_error(error,"ray need point2")

			rp3d.destroyBoxShape(box)
		end)


	end)
end
