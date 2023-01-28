#ifndef convex_polyshape_h
#define convex_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"

#define RP3D_CONVEX_POLYHEDRON_SHAPE_META_FUNCTIONS \
{"getNbFaces", ConvexPolyhedronShape_GetNbFaces},\
{"getFace", ConvexPolyhedronShape_GetFace},\
{"getNbVertices", ConvexPolyhedronShape_GetNbVertices},\
{"getVertex", ConvexPolyhedronShape_GetVertex},\
{"getVertexPosition", ConvexPolyhedronShape_GetVertexPosition},\
{"getFaceNormal", ConvexPolyhedronShape_GetFaceNormal},\
{"getNbHalfEdges", ConvexPolyhedronShape_GetNbHalfEdges},\
{"getHalfEdge", ConvexPolyhedronShape_GetHalfEdge},\
{"getCentroid", ConvexPolyhedronShape_GetCentroid},\
{"findMostAntiParallelFace", ConvexPolyhedronShape_FindMostAntiParallelFace}\


namespace rp3dDefold {

int ConvexPolyhedronShape_GetNbFaces(lua_State *L);
int ConvexPolyhedronShape_GetFace(lua_State *L);
int ConvexPolyhedronShape_GetNbVertices(lua_State *L);
int ConvexPolyhedronShape_GetVertex(lua_State *L);
int ConvexPolyhedronShape_GetVertexPosition(lua_State *L);
int ConvexPolyhedronShape_GetFaceNormal(lua_State *L);
int ConvexPolyhedronShape_GetNbHalfEdges(lua_State *L);
int ConvexPolyhedronShape_GetHalfEdge(lua_State *L);
int ConvexPolyhedronShape_GetCentroid(lua_State *L);
int ConvexPolyhedronShape_FindMostAntiParallelFace(lua_State *L);

}
#endif