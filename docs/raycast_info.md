# RaycastInfo
This structure contains the information about a raycast hit.

* `worldPoint` (vector3) Hit point in world-space coordinates.
* `worldNormal` (vector3)  Surface normal at hit point in world-space coordinates.
* `hitFraction` (number)  Fraction distance of the hit point between point1 and point2 of the ray The hit point "p" is such that p = point1 + hitFraction * (point2 - point1)
* `meshSubpart` (number) Mesh subpart index that has been hit (only used for triangles mesh and -1 otherwise)
* `triangleIndex` (number) Hit triangle index (only used for triangles mesh and -1 otherwise)
* `body` ([CollisionBody](collision_body.md))
* `collider` ([Collider](collider.md))