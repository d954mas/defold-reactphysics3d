# JointInfo

This structure is used to gather the information needed to create a joint.

---
Subclasses:
1. [BallAndSocketJointInfo](ball_and_socket_joint_info.md)
2. [HingeJointInfo](hinge_joint_info.md)
3. [SliderJointInfo](slider_joint_info.md)
4. [FixedJointInfo](fixed_joint_info.md)
---

* `body1` ([RigidBody](../rigid_body.md)) First rigid body of the joint.
* `body2` ([RigidBody](../rigid_body.md)) Second rigid body of the joint.
* `type` ([JointType](../rp3d.md#rp3djointtype)) Type of the joint.
* `positionCorrectionTechnique` ([JointsPositionCorrectionTechnique](../rp3d.md#rp3djointspositioncorrectiontechnique)) Position correction technique used for the constraint (used for joints).
* `isCollisionEnabled` (bool) True if the two bodies of the joint are allowed to collide with each other. 