# SliderJoint

This class represents a slider joint.

This joint has a one degree of freedom. It only allows relative translation of the bodies along a single direction and no rotation.


---

SliderJoint extends [Joint](joint.md)

---

## Methods

* SliderJoint:[isLimitEnabled](#sliderjointislimitenabled)() bool
* SliderJoint:[isMotorEnabled](#sliderjointismotorenabled)() bool
* SliderJoint:[enableLimit](#sliderjointenablelimitislimitenabled)(isLimitEnabled) 
* SliderJoint:[enableMotor](#sliderjointenablemotorismotorenabled)(isMotorEnabled) 
* SliderJoint:[getTranslation](#sliderjointgettranslation)() number
* SliderJoint:[getMinTranslationLimit](#sliderjointgetmintranslationlimit)() number
* SliderJoint:[setMinTranslationLimit](#sliderjointsetmintranslationlimitlowerlimit)(lowerLimit)
* SliderJoint:[getMaxTranslationLimit](#sliderjointgetmaxtranslationlimit)() number
* SliderJoint:[setMaxTranslationLimit](#sliderjointsetmaxtranslationlimitupperlimit)(upperLimit)
* SliderJoint:[getMotorSpeed](#sliderjointgetmotorspeed)() number
* SliderJoint:[setMotorSpeed](#sliderjointsetmotorspeedmotorspeed)(motorSpeed)
* SliderJoint:[getMaxMotorForce](#sliderjointgetmaxmotorforce)() number
* SliderJoint:[setMaxMotorForce](#sliderjointsetmaxmotorforcemaxmotorforce)(maxMotorForce)
* SliderJoint:[getMotorForce](#sliderjointgetmotorforcetimestep)(timeStep) number---

---
### SliderJoint:isLimitEnabled()

Return true if the limits or the joint are enabled. 

**RETURN**
* (bool)

---
### SliderJoint:isMotorEnabled()

Return true if the motor of the joint is enabled.

**RETURN**
* (bool)

---
### SliderJoint:enableLimit(isLimitEnabled)

Enable/Disable the limits of the joint.

**PARAMETERS**
* `isLimitEnabled` (bool)

---
### SliderJoint:enableMotor(isMotorEnabled)

Enable/Disable the motor of the joint.

**PARAMETERS**
* `isMotorEnabled` (bool)


---
### SliderJoint:getTranslation()

Return the current translation value of the joint.

**RETURN**
* (number)

---
### SliderJoint:getMinTranslationLimit()

Return the minimum translation limit.

**RETURN**
* (number)

---
### SliderJoint:setMinTranslationLimit(lowerLimit)

Set the minimum translation limit.

**PARAMETERS**
* `lowerLimit` (number)

---
### SliderJoint:getMaxTranslationLimit()

Return the maximum translation limit.

**RETURN**
* (number)

---
### SliderJoint:setMaxTranslationLimit(upperLimit)

Set the maximum translation limit.

**PARAMETERS**
* `upperLimit` (number)

---
### SliderJoint:getMotorSpeed()

Return the motor speed.

**RETURN**
* (number)

---
### SliderJoint:setMotorSpeed(motorSpeed)

Set the motor speed.

**PARAMETERS**
* `motorSpeed` (number)

---
### SliderJoint:getMaxMotorForce()

Return the maximum motor getMaxMotorForce.

**RETURN**
* (number)

---
### SliderJoint:setMaxMotorForce(maxMotorForce)

Set the maximum motor force.

**PARAMETERS**
* `maxMotorForce` (number)

---
### SliderJoint:getMotorForce(timeStep)

Return the intensity of the current force applied for the joint motor.

**PARAMETERS**
* `timeStep` (number)

**RETURN**
* (number)



