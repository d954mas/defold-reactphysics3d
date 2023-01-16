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
			local function test_enum_v2(parent,enum_name, config)
				assert_not_nil(rp3d[parent])
				assert_not_nil(rp3d[parent][enum_name])
				for k, v in pairs(config) do
					assert_equal(rp3d[parent][enum_name][k], v)
				end
			end

			test_enum("ContactsPositionCorrectionTechnique", { BAUMGARTE_CONTACTS = "BAUMGARTE_CONTACTS", SPLIT_IMPULSES = "SPLIT_IMPULSES" })
			test_enum("CollisionShapeName", { TRIANGLE = "TRIANGLE", SPHERE = "SPHERE",
											  CAPSULE = "CAPSULE", BOX = "BOX", CONVEX_MESH = "CONVEX_MESH", TRIANGLE_MESH = "TRIANGLE_MESH", HEIGHTFIELD = "HEIGHTFIELD" })
			test_enum("CollisionShapeType", {
				SPHERE = "SPHERE", CAPSULE = "CAPSULE", CONVEX_POLYHEDRON = "CONVEX_POLYHEDRON", CONCAVE_SHAPE = "CONCAVE_SHAPE"
			})
			test_enum("BodyType", {
				STATIC = "STATIC", KINEMATIC = "KINEMATIC", DYNAMIC = "DYNAMIC"
			})
			test_enum_v2("DebugRenderer","DebugItem", {
				COLLIDER_AABB = "COLLIDER_AABB", COLLIDER_BROADPHASE_AABB = "COLLIDER_BROADPHASE_AABB",
				COLLISION_SHAPE = "COLLISION_SHAPE", CONTACT_POINT = "CONTACT_POINT", CONTACT_NORMAL = "CONTACT_NORMAL"
			})
		end)

		--crash if have some memory corrupted issues
		test("test memory errors", function()
			for i=1,1000 do
				local w = rp3d.createPhysicsWorld()
				local body = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
				w:destroyCollisionBody(body)
				rp3d.destroyPhysicsWorld(w)
			end

			for i=1,100 do
				local w = rp3d.createPhysicsWorld()
				local body = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
				rp3d.destroyPhysicsWorld(w)
			end

			local w = rp3d.createPhysicsWorld()
			local shape = rp3d.createBoxShape(vmath.vector3(2))
			for i=1,100 do
				local body = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})

				local collision = body:addCollider(shape,{position = vmath.vector3(),quat = vmath.quat()})

				local body_rigid = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
				local collision2 = body_rigid:addCollider(shape,{position = vmath.vector3(),quat = vmath.quat()})

				w:destroyCollisionBody(body)
				w:destroyRigidBody(body_rigid)
			end
			rp3d.destroyBoxShape(shape)
			rp3d.destroyPhysicsWorld(w)

			w = rp3d.createPhysicsWorld()
			shape = rp3d.createBoxShape(vmath.vector3(2))
			for i=1,100 do
				local body = w:createCollisionBody({position = vmath.vector3(),quat = vmath.quat()})
				--local collision = body:addCollider(shape,{position = vmath.vector3(),quat = vmath.quat()})

				local body_rigid = w:createRigidBody({position = vmath.vector3(),quat = vmath.quat()})
				--local collision2 = body_rigid:addCollider(shape,{position = vmath.vector3(),quat = vmath.quat()})
			end
			rp3d.destroyPhysicsWorld(w)
			rp3d.destroyBoxShape(shape)
			assert_true(true)

		end)
	end)
end
