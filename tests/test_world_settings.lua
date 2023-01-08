local UTILS = require "tests.test_utils"

return function()
    describe("WorldSettings", function()
        before(function()
            UTILS.set_env(getfenv(1))
        end)
        after(function() end)

        test("config empty", function()
            local cfg = {}
            local w = rp3d.createPhysicsWorld(cfg)
            assert_true(true)
            rp3d.destroyPhysicsWorld(w)
        end)

        test("config all fields", function()
            local settings = {
                --Name of the world
                worldName = "TestWorld",
                --Gravity force vector of the world (in Newtons)
                gravity = vmath.vector3(1, 2, 3),
                --Distance threshold for two contact points for a valid persistent contact (in meters)
                persistentContactDistanceThreshold = 0.06,
                --Default friction coefficient for a rigid body
                defaultFrictionCoefficient = 0.6,
                --Default bounciness factor for a rigid body
                defaultBounciness = 0.4,
                --Velocity threshold for contact velocity restitution
                restitutionVelocityThreshold = 0.3,
                --True if the sleeping technique is enabled
                isSleepingEnabled = false;
                --Number of iterations when solving the velocity constraints of the Sequential Impulse technique
                defaultVelocitySolverNbIterations = 5,
                --Number of iterations when solving the position constraints of the Sequential Impulse technique
                defaultPositionSolverNbIterations = 4,
                --Time (in seconds) that a body must stay still to be considered sleeping
                defaultTimeBeforeSleep = 1.5,
                --A body with a linear velocity smaller than the sleep linear velocity (in m/s) might enter sleeping mode.
                defaultSleepLinearVelocity = 0.05,
                --A body with angular velocity smaller than the sleep angular velocity (in rad/s) might enter sleeping mode
                defaultSleepAngularVelocity = 6.0 * (math.pi / 180.0),
                -- This is used to test if two contact manifold are similar (same contact normal) in order to
                -- merge them. If the cosine of the angle between the normals of the two manifold are larger
                -- than the value bellow, the manifold are considered to be similar.
                cosAngleSimilarContactManifold = 0.96,
            }
            local w = rp3d.createPhysicsWorld(settings)
            assert_equal("TestWorld",w:getName())
            assert_equal_v3(vmath.vector3(1, 2, 3),w:getGravity())
            assert_equal(5,w:getNbIterationsVelocitySolver())
            assert_equal(4,w:getNbIterationsPositionSolver())
            assert_equal(false,w:isSleepingEnabled())
            assert_equal(1.5,w:getTimeBeforeSleep())
            assert_equal_float(0.05,w:getSleepLinearVelocity())
            assert_equal_float(6.0 * (math.pi / 180.0),w:getSleepAngularVelocity())

            rp3d.destroyPhysicsWorld(w)
        end)

        test("config all fields bad", function()
            local settings = {
                world_name = "bad field",
                --Name of the world
                worldName = "TestWorld",
                --Gravity force vector of the world (in Newtons)
                gravity = vmath.vector3(1, 2, 3),
                --Distance threshold for two contact points for a valid persistent contact (in meters)
                persistentContactDistanceThreshold = 0.06,
                --Default friction coefficient for a rigid body
                defaultFrictionCoefficient = 0.6,
                --Default bounciness factor for a rigid body
                defaultBounciness = 0.4,
                --Velocity threshold for contact velocity restitution
                restitutionVelocityThreshold = 0.3,
                --True if the sleeping technique is enabled
                isSleepingEnabled = false;
                --Number of iterations when solving the velocity constraints of the Sequential Impulse technique
                defaultVelocitySolverNbIterations = 5,
                --Number of iterations when solving the position constraints of the Sequential Impulse technique
                defaultPositionSolverNbIterations = 4,
                --Time (in seconds) that a body must stay still to be considered sleeping
                defaultTimeBeforeSleep = 1.5,
                --A body with a linear velocity smaller than the sleep linear velocity (in m/s) might enter sleeping mode.
                defaultSleepLinearVelocity = 0.05,
                --A body with angular velocity smaller than the sleep angular velocity (in rad/s) might enter sleeping mode
                defaultSleepAngularVelocity = 6.0 * (math.pi / 180.0),
                -- This is used to test if two contact manifold are similar (same contact normal) in order to
                -- merge them. If the cosine of the angle between the normals of the two manifold are larger
                -- than the value bellow, the manifold are considered to be similar.
                cosAngleSimilarContactManifold = 0.96,
            }
            local status,error = pcall(rp3d.createPhysicsWorld,settings)
            assert_false(status)
            assert_equal(error,"unknown key:world_name")
        end)

    end)
end
