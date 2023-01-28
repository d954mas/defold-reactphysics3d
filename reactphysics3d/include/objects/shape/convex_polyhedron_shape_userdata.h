#ifndef convex_polyshape_h
#define convex_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"

#define RP3D_CONVEX_POLYHEDRON_SHAPE_META_FUNCTIONS \
{"getNbFaces", ConvexPolyhedronShape_GetNbFaces},\
{"getFace", ConvexPolyhedronShape_GetFace},\
{"getNbVertices", ConvexPolyhedronShape_GetNbVertices},\
{"getVertex", ConvexPolyhedronShape_GetVertex}\


namespace rp3dDefold {

int ConvexPolyhedronShape_GetNbFaces(lua_State *L);
int ConvexPolyhedronShape_GetFace(lua_State *L);

int ConvexPolyhedronShape_GetNbVertices(lua_State *L);
int ConvexPolyhedronShape_GetVertex(lua_State *L);

}
#endif