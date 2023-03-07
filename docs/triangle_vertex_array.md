# TriangleVertexArray

This class is used to describe the vertices and faces of a triangular mesh.

A TriangleVertexArray represents a continuous array of vertices and indexes of a triangular mesh. 

## Create
1.1 Create from lua table
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

local indices = {}
indices[0] = 0;
indices[1] = 1;
indices[2] = 2;

local array = rp3d.createTriangleVertexArray(vertices, indices)

local normals = {}
normals[0] = 1;
normals[1] = 0;
normals[2] = 0;
normals[3] = 1;
normals[4] = 0;
normals[5] = 0;
normals[6] = 1
normals[7] = 0;
normals[8] = 0;

local array_normals = rp3d.createTriangleVertexArray(vertices, indices, normals)
```

1.2 Create from mesh vertices
```lua
local res = go.get("/meshes#convex", "vertices")
local buf = resource.get_buffer(res)
local array = rp3d.createTriangleVertexArrayFromMeshVerticesCopy(buf)
```

## Methods

* TriangleVertexArray:[getNbVertices](#trianglevertexarraygetnbvertices)() number
* TriangleVertexArray:[getNbTriangles](#trianglevertexarraygetnbtriangles)() number
* TriangleVertexArray:[getTriangleVertices](#trianglevertexarraygettriangleverticestriangleindex)(triangleIndex) vector3[3]
* TriangleVertexArray:[getTriangleVerticesNormals](#trianglevertexarraygettriangleverticesnormalstriangleindex)(triangleIndex) vector3[3]
* TriangleVertexArray:[getTriangleVerticesIndices](#trianglevertexarraygettriangleverticesindicestriangleindex)(triangleIndex) number[3]
* TriangleVertexArray:[getVertex](#trianglevertexarraygetvertexvertexindex)(vertexIndex) vector3
* TriangleVertexArray:[getNormal](#trianglevertexarraygetnormalvertexindex)(vertexIndex) vector3

---
### TriangleVertexArray:getNbVertices()
Return the number of vertices.

**RETURN**
* (number)

---
### TriangleVertexArray:getNbTriangles()
Return the number of triangles.

**RETURN**
* (number)

---
### TriangleVertexArray:getTriangleVertices(triangleIndex)
Return the vertices coordinates of a triangle.

**PARAMETERS**
* `triangleIndex` (number)

**RETURN**
* (vector3[3])

---
### TriangleVertexArray:getTriangleVerticesNormals(triangleIndex)
Return the three vertices normals of a triangle.

**PARAMETERS**
* `triangleIndex` (number)

**RETURN**
* (vector3[3])

---
### TriangleVertexArray:getTriangleVerticesIndices(triangleIndex)
Return the indices of the three vertices of a given triangle in the array. 

**PARAMETERS**
* `triangleIndex` (number)

**RETURN**
* (number[3])

---
### TriangleVertexArray:getVertex(vertexIndex)
Return a vertex of the array.

**PARAMETERS**
* `vertexIndex` (number)

**RETURN**
* (vector3)

---
### TriangleVertexArray:getNormal(vertexIndex)
Return a vertex normal of the array.

**PARAMETERS**
* `vertexIndex` (number)

**RETURN**
* (vector3)

