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

    end)
end
