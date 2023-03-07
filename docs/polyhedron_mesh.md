# PolyhedronMesh

## PolygonFace

* `nbVertices` (number) Number of vertices in the polygon face.
* `indexBase` (number) Index of the first vertex of the polygon face inside the array with all vertex indices.
```lua
local face = {
    nbVertices = 4;
    indexBase = 0;
}
```

## Create

1.1 Create mesh from table
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

## Methods
* PolyhedronMesh:[getNbVertices](#polyhedronmeshgetnbvertices)() number
* PolyhedronMesh:[getVertex](#polyhedronmeshgetvertexindex)(index) (vector3)
* PolyhedronMesh:[getNbFaces](#polyhedronmeshgetnbfaces)() number
* PolyhedronMesh:[getFaceNormal](#polyhedronmeshgetfacenormalfaceindex)(faceIndex) vector3
* PolyhedronMesh:[getCentroid](#polyhedronmeshgetcentroid)() vector3
* PolyhedronMesh:[getVolume](#polyhedronmeshgetvolume)() number

---
### PolyhedronMesh:getNbVertices()
Return the number of vertices.

**RETURN**
* (number)

---
### PolyhedronMesh:getVertex(index)
Return a vertex.

**PARAMETERS**
* `index` (number)

**RETURN**
* (vector3)

---
### PolyhedronMesh:getNbFaces()
Return the number of faces.

**RETURN**
* (number)

---
### PolyhedronMesh:getFaceNormal(faceIndex)
Return a face normal.

**PARAMETERS**
* `faceIndex` (number)

**RETURN**
* (vector3)

---
### PolyhedronMesh:getCentroid()
Return the centroid of the polyhedron.

**RETURN**
* (vector3)

---
### PolyhedronMesh:getVolume()
Compute and return the volume of the polyhedron.

**RETURN**
* (number)

