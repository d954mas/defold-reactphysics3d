# TriangleMesh

This class represents a mesh made of triangles.

A TriangleMesh contains one or several parts. Each part is a set of triangles represented in a [TriangleVertexArray](triangle_vertex_array.md) object describing all the triangles vertices of the part. A TriangleMesh object can be used to create a [ConcaveMeshShape](shapes/concave_mesh_shape.md) from a triangle mesh for instance.

## Create

```lua
local mesh = rp3d.createTriangleMesh();
```

## Methods

* TriangleMesh:[addSubpart](#trianglemeshaddsubparttrianglevertexarray)(triangleVertexArray)
* TriangleMesh:[getSubpart](#trianglemeshgetsubpartindexsubpart)(indexSubpart) [TriangleVertexArray](triangle_vertex_array.md)
* TriangleMesh:[getNbSubparts](#trianglemeshgetnbsubparts)() number
---
### TriangleMesh:addSubpart(triangleVertexArray)
Add a subpart of the mesh.

**PARAMETERS**
* `triangleVertexArray` ([TriangleVertexArray](triangle_vertex_array.md))

---
### TriangleMesh:getSubpart(indexSubpart)
Return a subpart (triangle vertex array) of the mesh. 

**PARAMETERS**
* `indexSubpart` (number)

**RETURN**
* ([TriangleVertexArray](triangle_vertex_array.md))

---
### TriangleMesh:getNbSubparts()
Return the number of subparts of the mesh.

**RETURN**
* (number)