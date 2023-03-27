# Joint

This abstract class represents a joint between two bodies. 

---
Subclasses:
1. [BallAndSocketJoint](ball_and_socket_joint.md)
---

## Methods

* Joint:[getBody1](#jointgetbody1)() [RigidBody](../rigid_body.md)
* Joint:[getBody2](#jointgetbody2)() [RigidBody](../rigid_body.md)
* Joint:[getType](#jointgettype)() [JointType](../rp3d.md#rp3djointtype)
* Joint:[getReactionForce](#jointgetreactionforcetimestep)(timeStep) vector3
* Joint:[getReactionTorque](#jointgetreactiontorquetimestep)(timeStep) vector3
* Joint:[isCollisionEnabled](#jointiscollisionenabled)() bool
* Joint:[getEntityId](#jointgetentityid)() number


---
### Joint:getBody1()

Return the body 1.

**RETURN**

* ([RigidBody](../rigid_body.md))

---
### Joint:getBody2()

Return the body 2.

**RETURN**

* ([RigidBody](../rigid_body.md))

---
### Joint:getType()

Return the type of the constraint.

**RETURN**

* ([JointType](../rp3d.md#rp3djointtype))

---
### Joint:getReactionForce(timeStep)

Return the force (in Newtons) on body 2 required to satisfy the joint constraint. 

**PARAMETERS**
* `timeStep` (number)

**RETURN**

* (vector3)

---
### Joint:getReactionTorque(timeStep)

Return the torque (in Newtons * meters) on body 2 required to satisfy the joint constraint. 

**PARAMETERS**
* `timeStep` (number)

**RETURN**

* (vector3)

---
### Joint:isCollisionEnabled()

Return true if the collision between the two bodies of the joint is enabled.

**RETURN**

* (bool)

---
### Joint:getEntityId()

**RETURN**

* (number)
