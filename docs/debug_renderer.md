# DebugRenderer
This class is used to display physics debug information directly into the user application view.

Note that you should use this only for debugging purpose and you should disable it when you compile the final release version of your application because computing/rendering phyiscs debug information can be expensive.

## Get

```lua
local renderer = world:getDebugRenderer();
```

## Methods

* DebugRenderer:[getIsDebugItemDisplayed](#debugrenderergetisdebugitemdisplayeditem)(item) [DebugItem](rp3d.md#rp3ddebugrenderer)
* DebugRenderer:[setIsDebugItemDisplayed](#debugrenderersetisdebugitemdisplayeditem-isdisplayed)(item, isDisplayed)
* DebugRenderer:[getContactPointSphereRadius](#debugrenderergetcontactpointsphereradius)() number
* DebugRenderer:[setContactPointSphereRadius](#debugrenderersetcontactpointsphereradiusradius)(radius)
* DebugRenderer:[getContactNormalLength](#debugrenderergetcontactnormalength)() number
* DebugRenderer:[setContactNormalLength](#debugrenderersetcontactnormallengthcontactnormallength)(contactNormalLength)
* DebugRenderer:[draw](#debugrendererdraw)()
* DebugRenderer:[reset](#debugrendererreset)()

---
### DebugRenderer:getIsDebugItemDisplayed(item)
Return whether a debug item is displayed or not.

**PARAMETERS**
* `item` ([DebugItem](rp3d.md#rp3ddebugrenderer))

**RETURN**
* (bool)

---
### DebugRenderer:setIsDebugItemDisplayed(item, isDisplayed)
Set whether a debug info is displayed or not.

**PARAMETERS**
* `item` ([DebugItem](rp3d.md#rp3ddebugrenderer))
* `isDisplayed` (bool)

---
### DebugRenderer:getContactPointSphereRadius()
Get the contact point sphere radius.

**RETURN**
* (number)

---
### DebugRenderer:setContactPointSphereRadius(radius)
Set the contact point sphere radius.

**PARAMETERS**
* `radius` (number)

---
### DebugRenderer:getContactNormalLength()
Return the length of contact normal.

**RETURN**
* (number)

---
### DebugRenderer:setContactNormalLength(contactNormalLength)
Set the length of contact normal.

**PARAMETERS**
* `contactNormalLength` (number)

---
### DebugRenderer:draw()
Draw lines(post draw_line messages to render).

---
### DebugRenderer:reset()
Clear all the debugging primitives (points, lines, triangles, ...) 
