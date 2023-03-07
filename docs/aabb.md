# AABB
This class represents a bounding volume of type "Axis Aligned Bounding Box".

It's a box where all the edges are always aligned with the world coordinate system. The AABB is defined by the minimum and maximum world coordinates of the three axis.

## Create

```lua
local minCoordinates = vmath.vector3(0,0,0)
local maxCoordinates = vmath.vector3(1,1,1)
local aabb = rp3d:createAABB(minCoordinates, maxCoordinates)
```

## Methods

* AABB:[getCenter](#aabbgetcenter)() vector3
* AABB:[getMin](#aabbgetmin)() vector3
* AABB:[setMin](#aabbsetminmin)(min) 
* AABB:[getMax](#aabbgetmax)() vector3
* AABB:[setMax](#aabbsetmaxmax)(max)
* AABB:[getExtent](#aabbgetextent)() vector3
* AABB:[inflate](#aabbinflatedx-dy-dz)(dx, dy, dz)
* AABB:[testCollision](#aabbtestcollisionaabb)(aabb) bool
* AABB:[getVolume](#aabbgetvolume)() number
* AABB:[mergeWithAABB](#aabbmergewithaabbaabb)(aabb)
* AABB:[mergeTwoAABBs](#aabbmergetwoaabbsaabb1-aabb2)(aabb1,aabb2)
* AABB:[contains](#aabbcontainsaabb)(aabb) bool
* AABB:[containsPoint](#aabbcontainspointpoint)(point) bool
* AABB:[testCollisionTriangleAABB](#aabbtestcollisiontriangleaabbp1-p2-p3)(p1, p2, p3) bool
* AABB:[testRayIntersect](#aabbtestrayintersectrayOrigin-rayDirectionInv-rayMaxFraction)(rayOrigin, rayDirectionInv, rayMaxFraction) bool
* AABB:[raycast](#aabbraycastray)(ray) nil|vector3
* AABB:[applyScale](#aabbapplyscalescale)(scale)


---
### AABB:getCenter()
Return the center point.

**RETURN**
* (vector3)

---
### AABB:getMin()
Return the minimum coordinates of the AABB.

**RETURN**
* (vector3)

---
### AABB:setMin(min)
Set the minimum coordinates of the AABB.

**PARAMETERS**
* `min` (vector3)

---
### AABB:getMax()
Return the maximum coordinates of the AABB.

**RETURN**
* (vector3)

---
### AABB:setMax(max)
Set the maximum coordinates of the AABB.

**PARAMETERS**
* `max` (vector3)

---
### AABB:getExtent()
Return the size of the AABB in the three dimension x, y and z. 

**RETURN**
* (vector3)

---
### AABB:inflate(dx, dy, dz)
Inflate each side of the AABB by a given size. 

**PARAMETERS**
* `dx` (number)
* `dy` (number)
* `dz` (number)

---
### AABB:testCollision(aabb)
Return true if the current AABB is overlapping with the AABB in argument.

Two AABBs overlap if they overlap in the three x, y and z axis at the same time.


**PARAMETERS**
* `aabb` ([AABB](aabb.md))

**RETURN**
* (bool)

---
### AABB:getVolume()
Return the volume of the AABB.

**RETURN**
* (number)

---
### AABB:mergeWithAABB(aabb)
Merge the AABB in parameter with the current one. 

**PARAMETERS**
* `aabb` ([AABB](aabb.md))

---
### AABB:mergeTwoAABBs(aabb1, aabb2)
Replace the current AABB with a new AABB that is the union of two AABBs in parameters.

**PARAMETERS**
* `aabb1` ([AABB](aabb.md))
* `aabb2` ([AABB](aabb.md))

---
### AABB:contains(aabb)
Return true if the current AABB contains the AABB given in parameter.

**PARAMETERS**
* `aabb` ([AABB](aabb.md))

**RETURN**
* (bool)

---
### AABB:containsPoint(point)
Return true if a point is inside the AABB.

**PARAMETERS**
* `point` (vector3)

**RETURN**
* (bool)

---
### AABB:testCollisionTriangleAABB(p1, p2, p3)
Return true if the AABB of a triangle intersects the AABB. 

**PARAMETERS**
* `p1` (vector3)
* `p2` (vector3)
* `p3` (vector3)

**RETURN**
* (bool)

---
### AABB:testRayIntersect(rayOrigin, rayDirectionInv, rayMaxFraction)
Return true if the ray intersects the AABB.

**PARAMETERS**
* `rayOrigin` (vector3)
* `rayDirectionInv` (vector3) - inverse direction. (1 / rayDirection.x, 1 / rayDirection.y, 1 / rayDirection.z);
* `rayMaxFraction` (vector3)

**RETURN**
* (bool)

---
### AABB:raycast(ray)
Compute the intersection of a ray and the AABB. 

**PARAMETERS**
* `ray` [(Ray)](ray.md)

**RETURN**
* (vector3|nil)

---
### AABB:applyScale(scale)
Apply a scale factor to the AABB. 

**PARAMETERS**
* `scale` (vector3)