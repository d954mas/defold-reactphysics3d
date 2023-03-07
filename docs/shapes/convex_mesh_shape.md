# ConvexMeshShape
ConvexMeshShape extends [ConvexPolyhedronShape](convex_polyhedron_shape.md)

This class represents a convex mesh shape.

In order to create a convex mesh shape, you need to indicate the local-space position of the mesh vertices. The center of mass of the shape will be at the origin of the local-space geometry that you use to create the mesh.


<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/convex_mesh_shape_classes.png">

## Create
You need PolyhedronMesh to create ConvexMeshShape

1.1 Create mesh from data
```lua
local vertices = {}
vertices[0] = -3;
vertices[1] = -3;
vertices[2] = 3;
vertices[3] = 3;
vertices[4] = -3;
vertices[5] = 3;
vertices[6] = 3;
vertices[7] = -3;
vertices[8] = -3;
vertices[9] = -3;
vertices[10] = -3;
vertices[11] = -3;
vertices[12] = -3;
vertices[13] = 3;
vertices[14] = 3;
vertices[15] = 3;
vertices[16] = 3;
vertices[17] = 3;
vertices[18] = 3;
vertices[19] = 3;
vertices[20] = -3;
vertices[21] = -3;
vertices[22] = 3;
vertices[23] = -3;

local indices = {}
indices[0] = 0;
indices[1] = 3;
indices[2] = 2;
indices[3] = 1;
indices[4] = 4;
indices[5] = 5;
indices[6] = 6;
indices[7] = 7;
indices[8] = 0;
indices[9] = 1;
indices[10] = 5;
indices[11] = 4;
indices[12] = 1;
indices[13] = 2;
indices[14] = 6;
indices[15] = 5;
indices[16] = 2;
indices[17] = 3;
indices[18] = 7;
indices[19] = 6;
indices[20] = 0;
indices[21] = 4;
indices[22] = 7;
indices[23] = 3;

-- Description of the six faces of the convex mesh
local polygonFaces = {}

for f = 0, 5 do
	--// First vertex of the face in the indices array
	local face = {
		nbVertices = 4;
		indexBase = f * 4
	}
	polygonFaces[f] = face
end
local mesh = rp3d.createPolyhedronMesh(vertices, indices, polygonFaces)
```
1.2 Or create mesh from vertices
```lua
local res = go.get("/meshes#convex", "vertices")
local buf = resource.get_buffer(res)
local mesh = rp3d.createPolyhedronMeshFromMeshVerticesCopy(buf)
```

2.Create shape from mesh
```lua
shape = rp3d.createConvexMeshShape(mesh)
```

## Methods

* ConvexMeshShape:[getScale](#convexmeshshapegetscale)() vector3
* ConvexMeshShape:[setScale](#convexmeshshapesetscalescale)(scale)

---
### ConvexMeshShape:getScale()
Return the scale. 

**RETURN**
* (vector3)

---
### ConvexMeshShape:setScale(scale)
Set the scale.

Note that you might want to recompute the inertia tensor and center of mass of the body after changing the scale of a collision shape.

**PARAMETERS**
* `halfExtents` (vector3)

