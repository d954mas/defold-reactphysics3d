# FixedJointInfo

This structure is used to gather the information needed to create a fixed  joint.

---

FixedJointInfo extends [JointInfo](joint_info.md)

---

* `isUsingLocalSpaceAnchors` (bool) True if this object has been constructed using local-space anchors.
* `anchorPointWorldSpace` (vector3) Anchor point (in world-space coordinates)
* `anchorPointBody1LocalSpace` (vector3) Anchor point on body 1 (in local-space coordinates)
* `anchorPointBody2LocalSpace` (vector3) Anchor point on body 2 (in local-space coordinates)

## Create

```lua
local infoWorld = rp3d.createFixedJointInfoWorldSpace(body1, body2, initAnchorPointWorldSpace)

local infoLocal = rp3d.createFixedJointInfoLocalSpace(body1, body2, anchorPointBody1Local, anchorPointBody2Local)
```