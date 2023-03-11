#ConvexPolyhedronShape
ConvexPolyhedronShape extends [ConvexShape](convex_shape.md)

This abstract class represents a convex polyhedron collision shape associated with a body that is used during the narrow-phase collision detection.

Inheritance diagram for ConvexPolyhedronShape.

<img src="https://github.com/d954mas/defold-reactphysics3d/blob/master/docs/collision_shape_classes.png">


## Create
You can't create ConvexPolyhedronShape class.

## Methods

* ConvexPolyhedronShape:[getNbFaces](#convexpolyhedronshapegetnbfaces)() number
* ConvexPolyhedronShape:[getFace](#convexpolyhedronshapegetgetfacefaceindex)(faceIndex) HalfEdgeStructureFace
* ConvexPolyhedronShape:[getNbVertices](#convexpolyhedronshapegetnbvertices)() number
* ConvexPolyhedronShape:[getVertex](#convexpolyhedronshapegetvertexvertexindex)(vertexIndex) HalfEdgeStructureVertex 
* ConvexPolyhedronShape:[getVertexPosition](#convexpolyhedronshapegetvertexpositionvertexindex)(vertexIndex) vector3 
* ConvexPolyhedronShape:[getFaceNormal](#convexpolyhedronshapegetfacenormalfaceindex)(faceIndex) vector3
* ConvexPolyhedronShape:[getNbHalfEdges](#convexpolyhedronshapegetnbhalfedges)() number
* ConvexPolyhedronShape:[getHalfEdge](#convexpolyhedronshapegethalfedgeedgeindex)(edgeIndex) HalfEdgeStructureEdge
* ConvexPolyhedronShape:[getCentroid](#convexpolyhedronshapegetcentroid)() vector3
* ConvexPolyhedronShape:[findMostAntiParallelFace](#convexpolyhedronshapefindmostantiparallelface)() number
