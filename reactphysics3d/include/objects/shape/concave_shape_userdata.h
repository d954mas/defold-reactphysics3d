#ifndef concave_shape_h
#define concave_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

#define RP3D_CONCAVE_SHAPE_META_FUNCTIONS \
{"getRaycastTestType", ConcaveShape_GetRaycastTestType},\
{"setRaycastTestType", ConcaveShape_SetRaycastTestType},\
{"getScale", ConcaveShape_GetScale},\
{"setScale", ConcaveShape_SetScale}\

namespace rp3dDefold {
    int ConcaveShape_GetRaycastTestType(lua_State *L);
    int ConcaveShape_SetRaycastTestType(lua_State *L);
    int ConcaveShape_GetScale(lua_State *L);
    int ConcaveShape_SetScale(lua_State *L);
}
#endif