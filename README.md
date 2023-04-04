[![GitHub release (latest by date)](https://img.shields.io/github/v/release/d954mas/defold-reactphysics3d)](https://github.com/d954mas/defold-reactphysics3d/releases)
[![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/d954mas/defold-reactphysics3d/bob.yml?branch=master)](https://github.com/d954mas/defold-reactphysics3d)
# ReactPhysics3D for Defold

ReactPhysics3D lua bindings for the Defold Game Engine.

This project based on [ReactPhysics3D](https://github.com/DanielChappuis/reactphysics3d)

ReactPhysics3D is an open source C++ physics engine library that can be used in 3D simulations and games.

www.reactphysics3d.com



I tried to keep the lua api the same as the c++ api when possible.

If you like the extension you can support me on patreon.
It will help me make more libraries for defold.

[![](https://c5.patreon.com/external/logo/become_a_patron_button.png)](https://www.patreon.com/d954mas)

[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/d954mas)

Try the [demo](https://d954mas.github.io/defold-reactphysics3d)

---
## WARNING

1. This is c++ library. I add some function parameters checks but you can crash it in some cases.

2. Call destroy. Or you will have memory leaks.

3. rp3d.destroyPhysicsWorld will destroy and free all used memory by world objects. But for example shapes will not be free.

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

5. In most places used 0 index.
---
## TODO
1.Add Joints


## Limits
1)Defold vector instead of rp3d::Vector

2)Defold quaternion instead of rp3d::Quat

3)no Transform userdata. Use table with vector3 and quaternion

---
## Setup

### Dependency

You can use the **rp3d** extension in your own project by adding this project as a [Defold library dependency](https://www.defold.com/manuals/libraries/). Open your game.project file and in the dependencies field under project add:

> [https://github.com/d954mas/defold-reactphysics3d/archive/master.zip](https://github.com/d954mas/defold-reactphysics3d/archive/master.zip)

Or point to the ZIP file of a [specific release](https://github.com/d954mas/defold-reactphysics3d/releases).

### Emmylua
Make lua file with Emmylua annotations. Use it for autocomplete.

[Emmylua header](https://github.com/d954mas/defold-reactphysics3d/blob/master/rp3d_header.lua)

---
## How to use
1.[ReactPhysics3D c++ manual](https://www.reactphysics3d.com/documentation.html)

User manual and api for c++ library. Read it first

2.[Lua API](#api)

3.[Examples](https://github.com/d954mas/defold-reactphysics3d/tree/master/main/test_scenes)

Look at examples. You can download this repository and run them.

4.[Tests](https://github.com/d954mas/defold-reactphysics3d/tree/master/tests)

Every function have a test. You can use test as example.

---
## Lua API

[rp3d](docs/rp3d.md)

[AABB](docs/aabb.md)\
[BallAndSocketJoint](docs/joints/ball_and_socket_joint.md)\
[BallAndSocketJointInfo](docs/joints/ball_and_socket_joint_info.md)\
[BoxShape](docs/shapes/box_shape.md)\
[CapsuleShape](docs/shapes/capsule_shape.md)\
[Collider](docs/collider.md)\
[CollisionBody](docs/collision_body.md)\
[CollisionShape](docs/shapes/collision_shape.md)\
[ConcaveMeshShape](docs/shapes/concave_mesh_shape.md)\
[ConcaveShape](docs/shapes/concave_shape.md)\
[ConvexMeshShape](docs/shapes/convex_mesh_shape.md)\
[ConvexPolyhedronShape](docs/shapes/convex_polyhedron_shape.md)\
[ConvexShape](docs/shapes/convex_shape.md)\
[DebugRenderer](docs/debug_renderer.md)\
[EventListener](docs/world.md#eventlistener)\
[FixedJoint](docs/joints/fixed_joint.md)\
[FixedJointInfo](docs/joints/fixed_joint_info.md)\
[HalfEdgeStructure](docs/half_edge_structure.md)\
[HeightFieldShape](docs/shapes/heightfield_shape.md)\
[HingeJoint](docs/joints/hinge_joint.md)\
[HingeJointInfo](docs/joints/hinge_joint_info.md)\
[Joint](docs/joints/joint.md)\
[JointInfo](docs/joints/joint_info.md)\
[Material](docs/material.md)\
[PhysicsCommon](docs/rp3d.md) rp3d in lua\
[PhysicsWorld](docs/world.md)\
[PolyhedronMesh](docs/polyhedron_mesh.md)\
[Ray](docs/ray.md)\
[RaycastCallback](docs/world.md#raycastcallback)\
[RaycastInfo](docs/raycast_info.md)\
[RigidBody](docs/rigid_body.md)\
[SliderJoint](docs/joints/slider_joint.md)\
[SliderJointInfo](docs/joints/slider_joint_info.md)\
[SphereShape](docs/shapes/sphere_shape.md)\
[Transform](docs/transform.md)\
[TriangleMesh](docs/triangle_mesh.md)\
[TriangleVertexArray](docs/triangle_vertex_array.md)

