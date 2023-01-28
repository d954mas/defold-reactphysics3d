#ifndef convex_shape_h
#define convex_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"

#define RP3D_CONVEX_SHAPE_META_FUNCTIONS \
{"getMargin", ConvexShape_GetMargin}\

namespace rp3dDefold {

int ConvexShape_GetMargin(lua_State *L);

}
#endif