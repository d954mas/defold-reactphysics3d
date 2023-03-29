# HingeJoint


---

HingeJoint extends [Joint](joint.md)

---

## Methods

* HingeJoint:[isLimitEnabled](#hingejointislimitenabled)() bool
* HingeJoint:[isMotorEnabled](#hingejointismotorenabled)() bool
* HingeJoint:[enableLimit](#hingejointenablelimitislimitenabled)(isLimitEnabled) 
* HingeJoint:[enableMotor](#hingejointenablemotorismotorenabled)(isMotorEnabled) 
* HingeJoint:[getMinAngleLimit](#hingejointgetminanglelimit)() number
* HingeJoint:[setMinAngleLimit](#hingejointsetminanglelimitlowerlimit)(lowerLimit)
* HingeJoint:[getMaxAngleLimit](#hingejointgetmaxanglelimit)() number
* HingeJoint:[setMaxAngleLimit](#hingejointsetmaxanglelimitupperlimit)(upperLimit)
* HingeJoint:[getMotorSpeed](#hingejointgetmotorspeed)() number
* HingeJoint:[setMotorSpeed](#hingejointsetmotorspeedmotorspeed)(motorSpeed)
* HingeJoint:[getMaxMotorTorque](#hingejointgetmaxmotortorque)() number
* HingeJoint:[setMaxMotorTorque](#hingejointsetmaxmotortorquemaxmotortorque)(maxMotorTorque)
* HingeJoint:[getMotorTorque](#hingejointgetmotortorquetimestep)(timeStep) number
* HingeJoint:[getAngle](#hingejointgetangle)() number

---
### HingeJoint:isLimitEnabled()

Return true if the limits or the joint are enabled. 

**RETURN**
* (bool)

---
### HingeJoint:isMotorEnabled()

Return true if the motor of the joint is enabled.

**RETURN**
* (bool)

---
### HingeJoint:enableLimit(isLimitEnabled)

Enable/Disable the limits of the joint.

**PARAMETERS**
* `isLimitEnabled` (bool)

---
### HingeJoint:enableMotor(isMotorEnabled)

Enable/Disable the motor of the joint.

**PARAMETERS**
* `isMotorEnabled` (bool)

---
### HingeJoint:getMinAngleLimit()

Return the minimum angle limit.

**RETURN**
* (number)

---
### HingeJoint:setMinAngleLimit(lowerLimit)

Set the minimum angle limit.

**PARAMETERS**
* `lowerLimit` (number)

---
### HingeJoint:getMaxAngleLimit()

Return the maximum angle limit.

**RETURN**
* (number)

---
### HingeJoint:setMaxAngleLimit(upperLimit)

Set the maximum angle limit.

**PARAMETERS**
* `upperLimit` (number)

---
### HingeJoint:getMotorSpeed()

Return the motor speed.

**RETURN**
* (number)

---
### HingeJoint:setMotorSpeed(motorSpeed)

Set the motor speed.

**PARAMETERS**
* `motorSpeed` (number)

---
### HingeJoint:getMaxMotorTorque()

Return the maximum motor torque.

**RETURN**
* (number)

---
### HingeJoint:setMaxMotorTorque(maxMotorTorque)

Set the maximum motor torque.

**PARAMETERS**
* `maxMotorTorque` (number)

---
### HingeJoint:getMotorTorque(timeStep)

Return the intensity of the current torque applied for the joint motor.

**PARAMETERS**
* `timeStep` (number)

**RETURN**
* (number)

---
### HingeJoint:getAngle()

Return the current hinge angle (in radians)

**RETURN**
* (number)
