local UTILS = require "tests.test_utils"

return function()
	describe("rp3d", function()
		before(function()
			UTILS.set_env(getfenv(1))
		end)
		after(function() end)

		test("enums exist", function()
			local function test_enum(enum_name, config)
				assert_not_nil(rp3d[enum_name])
				for k, v in pairs(config) do
					assert_equal(rp3d[enum_name][k], v)
				end
			end
			test_enum("ContactsPositionCorrectionTechnique", { BAUMGARTE_CONTACTS = "BAUMGARTE_CONTACTS", SPLIT_IMPULSES = "SPLIT_IMPULSES" })
			test_enum("CollisionShapeName", { TRIANGLE = "TRIANGLE", SPHERE = "SPHERE",
											  CAPSULE = "CAPSULE", BOX = "BOX", CONVEX_MESH = "CONVEX_MESH", TRIANGLE_MESH = "TRIANGLE_MESH", HEIGHTFIELD = "HEIGHTFIELD" })
			test_enum("CollisionShapeType", {
				SPHERE = "SPHERE", CAPSULE = "CAPSULE", CONVEX_POLYHEDRON = "CONVEX_POLYHEDRON", CONCAVE_SHAPE = "CONCAVE_SHAPE"
			})
		end)
	end)
end
