local UTILS = require "tests.test_utils"

return function()
    describe("World", function()
        before(function()
            UTILS.set_env(getfenv(1))
        end)
        after(function() end)

        test("create", function()
            local w = rp3d.createPhysicsWorld()
            assert_not_nil(w)
            assert_not_nil(w.__userdata_rp3d)
            assert_equal(w.__userdata_type_rp3d, "rp3d::World")

            rp3d.destroyPhysicsWorld(w)
            assert_not_nil(w)
            assert_nil(w.__userdata_rp3d)
            assert_equal(w.__userdata_type_rp3d, "rp3d::World")
        end)

        test("create config", function()
            local cfg = {}
            local w = rp3d.createPhysicsWorld(cfg)
            assert_not_nil(w)
            assert_not_nil(w.__userdata_rp3d)
            assert_equal(w.__userdata_type_rp3d, "rp3d::World")
            --TODO CHECK CONFIG DATA

            rp3d.destroyPhysicsWorld(w)
            assert_not_nil(w)
            assert_nil(w.__userdata_rp3d)
            assert_equal(w.__userdata_type_rp3d, "rp3d::World")
        end)

        test("update", function()
            local w = rp3d.createPhysicsWorld()
            w:update(1/60)
            w:update(1/30)
            w:update(0.001)
            w:update(1/120)

            local status, error = pcall(w.update,w)
            assert_false(status)
            assert_equal(error,"This function requires 2 arguments. Got 1.")

            rp3d.destroyPhysicsWorld(w)
        end)

        test("Set/Get NbIterationsPositionSolver()", function()
            local w = rp3d.createPhysicsWorld()
            UTILS.test_method_get_set(w, "NbIterationsPositionSolver", {
                values = { 1, 5,10 }
            })
            rp3d.destroyPhysicsWorld(w)
        end)

        test("Set/Get NbIterationsVelocitySolver()", function()
            local w = rp3d.createPhysicsWorld()
            UTILS.test_method_get_set(w, "NbIterationsVelocitySolver", {
                values = { 1, 5,10 }
            })
            rp3d.destroyPhysicsWorld(w)
        end)



    end)
end
