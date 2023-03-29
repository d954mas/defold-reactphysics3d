# SliderJointInfo

This structure is used to gather the information needed to create a slider joint.

---

SliderJointInfo extends [JointInfo](joint_info.md)

---

* `isUsingLocalSpaceAnchors` (bool) True if this object has been constructed using local-space anchors.
* `anchorPointWorldSpace` (vector3) Anchor point (in world-space coordinates)
* `anchorPointBody1LocalSpace` (vector3) Anchor point on body 1 (in local-space coordinates)
* `anchorPointBody2LocalSpace` (vector3) Anchor point on body 2 (in local-space coordinates)
* `sliderAxisWorldSpace` (vector3) Slider axis (in world-space coordinates)
* `sliderAxisBody1Local` (vector3) Hinge slider axis of body 1 (in local-space coordinates)
* `isLimitEnabled` (bool) True if the slider limits are enabled.
* `isMotorEnabled` (bool) True if the slider motor is enabled.
* `minTranslationLimit` (number) Mininum allowed translation if limits are enabled.
* `maxTranslationLimit` (number) Maximum allowed translation if limits are enabled.
* `motorSpeed` (number) Motor speed.
* `maxMotorForce` (number) Maximum motor force (in Newtons) that can be applied to reach to desired motor speed.


## Create

```lua
local infoWorld = rp3d.createSliderJointInfoWorldSpace(body1, body2,
		initAnchorPointWorldSpace, initSliderAxisWorldSpace)

local infoLocal = rp3d.createSliderJointInfoLocalSpace(body1, body2,
        anchorPointBody1Local, anchorPointBody2Local,
		sliderAxisBody1Local)
```