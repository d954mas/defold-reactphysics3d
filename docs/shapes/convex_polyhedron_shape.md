# ConvexPolyhedronShape
ConvexPolyhedronShape extends [ConvexShape](convex_shape.md)

This abstract class represents a convex polyhedron collision shape associated with a body that is used during the narrow-phase collision detection.


Subclasses:
1. [BoxShape](box_shape.md)
2. [ConvexMeshShape](convex_mesh_shape.md)

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/shapes/img/convex_polyhedron_shape_classes.png">


## Create
Abstract class.You can't create ConvexPolyhedronShape class.

## Methods

* ConvexPolyhedronShape:[getNbFaces](#convexpolyhedronshapegetnbfaces)() number
* ConvexPolyhedronShape:[getFace](#convexpolyhedronshapegetfacefaceindex)(faceIndex) [HalfEdgeStructureFace](half_edge_structure.md)
* ConvexPolyhedronShape:[getNbVertices](#convexpolyhedronshapegetnbvertices)() number
* ConvexPolyhedronShape:[getVertex](#convexpolyhedronshapegetvertexvertexindex)(vertexIndex) [HalfEdgeStructureVertex](half_edge_structure.md) 
* ConvexPolyhedronShape:[getVertexPosition](#convexpolyhedronshapegetvertexpositionvertexindex)(vertexIndex) vector3 
* ConvexPolyhedronShape:[getFaceNormal](#convexpolyhedronshapegetfacenormalfaceindex)(faceIndex) vector3
* ConvexPolyhedronShape:[getNbHalfEdges](#convexpolyhedronshapegetnbhalfedges)() number
* ConvexPolyhedronShape:[getHalfEdge](#convexpolyhedronshapegethalfedgeedgeindex)(edgeIndex) [HalfEdgeStructureEdgetes](half_edge_structure.md)
* ConvexPolyhedronShape:[getCentroid](#convexpolyhedronshapegetcentroid)() vector3
* ConvexPolyhedronShape:[findMostAntiParallelFace](#convexpolyhedronshapefindmostantiparallelfacedirection)(direction) number


---
### ConvexPolyhedronShape:getNbFaces()
Return the number of faces of the polyhedron.

**RETURN**
* (number)

---
### ConvexPolyhedronShape:getFace(faceIndex)
Return a given face of the polyhedron.

**PARAMETERS**
* `faceIndex` (number)

**RETURN**
* [(HalfEdgeStructureFace)](half_edge_structure.md)

---
### ConvexPolyhedronShape:getNbVertices()
Return the number of vertices of the polyhedron.

**RETURN**
* (number)

---
### ConvexPolyhedronShape:getVertex(vertexIndex)
Return a given vertex of the polyhedron.

**PARAMETERS**
* `vertexIndex` (number)

**RETURN**
* [(HalfEdgeStructureVertex)](half_edge_structure.md)

---
### ConvexPolyhedronShape:getVertexPosition(vertexIndex)
Return the position of a given vertex. 

**PARAMETERS**
* `vertexIndex` (number)

**RETURN**
* (vector3)

---
### ConvexPolyhedronShape:getFaceNormal(faceIndex)
Return the normal vector of a given face of the polyhedron.

**PARAMETERS**
* `faceIndex` (number)

**RETURN**
* (vector3)

---
### ConvexPolyhedronShape:getNbHalfEdges()
Return the number of half-edges of the polyhedron.

**RETURN**
* (number)

---
### ConvexPolyhedronShape:getHalfEdge(edgeIndex)
Return a given half-edge of the polyhedron.

**PARAMETERS**
* `edgeIndex` (number)

**RETURN**
* [(HalfEdgeStructureEdge)](half_edge_structure.md)

---
### ConvexPolyhedronShape:getCentroid()
Return the centroid of the polyhedron.

**RETURN**
* (vector3)

---
### ConvexPolyhedronShape:findMostAntiParallelFace(direction)
Find and return the index of the polyhedron face with the most anti-parallel face normal given a direction vector. 

**PARAMETERS**
* `direction` (vector3)

**RETURN**
* (number)

