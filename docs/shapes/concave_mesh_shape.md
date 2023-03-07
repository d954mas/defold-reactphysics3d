# ConcaveMeshShape
ConcaveMeshShape extends [ConcaveShape](concave_shape.md)

This class represents a static concave mesh shape.

Note that collision detection with a concave mesh shape can be very expensive. You should only use this shape for a static mesh.


<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/concave_mesh_shape_classes.png">


## Create

You need TriangleMesh to create ConvexMeshShape

1. Create triangle mesh
```lua
local mesh = rp3d.createTriangleMesh()
```
2. Create triangle array to add in mesh

    2.1 Create from lua table.(normals can be nil)
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
    
    local array = rp3d.createTriangleVertexArray(vertices, indices, normals)
    ```
    2.2 Create from mesh vertices
    ```lua
    local res = go.get("/meshes#concave", "vertices")
    local buf = resource.get_buffer(res)
    local array = rp3d.createTriangleVertexArrayFromMeshVerticesCopy(buf)
    ```

3. Add array in triangle mesh
```lua
mesh:addSubpart(array)
```

4. Create shape
```lua
local shape = rp3d.createConcaveMeshShape(mesh) 
```

## Methods

* ConcaveMeshShape:[getNbSubparts](#concavemeshshapegetnbsubparts)() number
* ConcaveMeshShape:[getNbTriangles](#concavemeshshapegetnbtrianglessubpart)(subPart) number
* ConcaveMeshShape:[getTriangleVerticesIndices](#concavemeshshapegettriangleverticesindicessubparttriangleindex)(subPart,triangleIndex) number[3]

---
### ConcaveMeshShape:getNbSubparts()
Return the number of sub parts contained in this mesh.

**RETURN**
* (number)

---
### ConcaveMeshShape:getNbTriangles(subPart)
Return the number of triangles in a sub part of the mesh. 

**PARAMETERS**
* `subPart` (number)

---
### ConcaveMeshShape:getTriangleVerticesIndices(subPart,triangleIndex)
Return the indices of the three vertices of a given triangle in the array.

**PARAMETERS**
* `subPart` (number)
* `triangleIndex` (number)

**RETURN**
* (vector3[])