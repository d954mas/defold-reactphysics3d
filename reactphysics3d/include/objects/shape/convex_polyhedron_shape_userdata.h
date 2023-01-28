#ifndef convex_polyshape_h
#define convex_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"

#define RP3D_CONVEX_POLYHEDRON_SHAPE_META_FUNCTIONS \
{"getNbFaces", ConvexPolyhedronShape_GetNbFaces}\


namespace rp3dDefold {

int ConvexPolyhedronShape_GetNbFaces(lua_State *L);

}
#endif