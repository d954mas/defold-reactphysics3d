# BallAndSocketJointinfo

This structure is used to gather the information needed to create a ball-and-socket joint.

---

BallAndSocketJointinfo extends [JointInfo](joint_info.md)

---

* `isUsingLocalSpaceAnchors` (bool) True if this object has been constructed using local-space anchors.
* `anchorPointWorldSpace` (vector3) Anchor point (in world-space coordinates)
* `anchorPointBody1LocalSpace` (vector3) Anchor point on body 1 (in local-space coordinates)
* `anchorPointBody2LocalSpace` (vector3) Anchor point on body 2 (in local-space coordinates)

## Create

```lua
local infoWorld = rp3d.createBallAndSocketJointInfoWorldSpace(body_1, body_2, vmath.vector3(0, 1, 0))

local infoLocal = rp3d.createBallAndSocketJointInfoLocalSpace(body_1, body_2, vmath.vector3(0, -1, 0), vmath.vector3(0, 1, 0))
```