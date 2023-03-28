# HingeJointInfo

This structure is used to gather the information needed to create a hinge joint.

---

HingeJointInfo extends [JointInfo](joint_info.md)

---

* `isUsingLocalSpaceAnchors` (bool) True if this object has been constructed using local-space anchors.
* `anchorPointWorldSpace` (vector3) Anchor point (in world-space coordinates)
* `anchorPointBody1LocalSpace` (vector3) Anchor point on body 1 (in local-space coordinates)
* `anchorPointBody2LocalSpace` (vector3) Anchor point on body 2 (in local-space coordinates)
* `rotationAxisWorld` (vector3) Hinge rotation axis (in world-space coordinates)
* `rotationAxisBody1Local` (vector3) Hinge rotation axis of body 1 (in local-space coordinates)
* `rotationAxisBody2Local` (vector3) Hinge rotation axis of body 2 (in local-space coordinates)
* `isLimitEnabled` (bool) True if the hinge joint limits are enabled.
* `isMotorEnabled` (bool) True if the hinge joint motor is enabled.
* `minAngleLimit` (number) Minimum allowed rotation angle (in radian) if limits are enabled.
* `maxAngleLimit` (number) Maximum allowed rotation angle (in radian) if limits are enabled.
* `motorSpeed` (number) Motor speed (in radian/second)
* `maxMotorTorque` (number) Maximum motor torque (in Newtons * meters) that can be applied to reach to desired motor speed.

## Create

```lua
local infoWorld = rp3d.createHingeJointInfoWorldSpace(body_1, body_2, 
        initAnchorPointWorldSpace, initRotationAxisWorld)

local infoLocal = rp3d.createHingeJointInfoLocalSpace(body_1, body_2,
        anchorPointBody1Local, anchorPointBody2Local, 
        rotationBody1AxisLocal, rotationBody2AxisLocal)
```