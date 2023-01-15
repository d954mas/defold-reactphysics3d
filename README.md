# ReactPhysics3D for Defold

ReactPhysics3D lua bindings for the Defold Game Engine.

This project based on [ReactPhysics3D](https://github.com/DanielChappuis/reactphysics3d)

ReactPhysics3D is an open source C++ physics engine library that can be used in 3D simulations and games.

www.reactphysics3d.com



I tried to keep the lua api the same as the c++ api when possible.

If you like the extension you can support me on patreon.
It will help me make more libraries for defold.

[![](https://c5.patreon.com/external/logo/become_a_patron_button.png)](https://www.patreon.com/d954mas)

Try the demo: 


##Be carefull
1. This is c++ library. I add some function parameters checks but you can crash it in some cases.

2. Call destroy. Or you will have memory leaks.

3. rp3d.destroyPhysicsWorld will destroy and free all used memory,except shapes.

4. Destroy shapes after destroy all objects that use shape
or you will get crash.
```lua
--CRASH
rp3d.destroyBoxShape(self.shape)
self.world:destroyCollisionBody(self.body)

--GOOD
self.world:destroyCollisionBody(self.body)
rp3d.destroyBoxShape(self.shape)
```

## Limits
1)Defold vector instead of rp3d::Vector
2)Defold quaternion instead of rp3d::Quat
3)no Transform userdata. Use table with vector3 and quaternion

