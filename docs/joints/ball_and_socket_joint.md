# BallAndSocketJoint

This class represents a ball-and-socket joint that allows arbitrary rotation between two bodies.

---

BallAndSocketJoint extends [Joint](joint.md)

---

## Methods

* BallAndSocketJoint:[enableConeLimit](#ballandsocketjointenableconelimitislimitenabled)(isLimitEnabled) 
* BallAndSocketJoint:[isConeLimitEnabled](#ballandsocketjointisconelimitenabled)() bool
* BallAndSocketJoint:[setConeLimitHalfAngle](#ballandsocketjointsetconelimithalfangleconehalfangle)(coneHalfAngle)
* BallAndSocketJoint:[getConeLimitHalfAngle](#ballandsocketjointgetconelimithalfangle)() number
* BallAndSocketJoint:[getConeHalfAngle](#ballandsocketjointgetconehalfangle)() number

---
### BallAndSocketJoint:enableConeLimit(isLimitEnabled)

Enable/disable the cone limit of the joint.

**PARAMETERS**
* `isLimitEnabled` (bool)

---
### BallAndSocketJoint:isConeLimitEnabled()

Return true if the cone limit or the joint is enabled.

**RETURN**
* (bool)

---
### BallAndSocketJoint:setConeLimitHalfAngle(coneHalfAngle)

Set the cone limit half angle.

**PARAMETERS**
* `coneHalfAngle` (number) The angle of the cone limit (in radian) from [0; PI] 

---
### BallAndSocketJoint:getConeLimitHalfAngle()

Return the cone limit half angle (in radians)

**RETURN**
* (number)

---
### BallAndSocketJoint:getConeHalfAngle()

Return the current cone half angle (in radians)

**RETURN**
* (number)



