#ifndef capsule_shape_h
#define capsule_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

#define RP3D_CAPSULE_SHAPE_META_FUNCTIONS \
{"getRadius", CapsuleShape_GetRadius},\
{"setRadius", CapsuleShape_SetRadius},\
{"setHeight", CapsuleShape_SetHeight},\
{"getHeight", CapsuleShape_GetHeight}

namespace rp3dDefold {

    int CapsuleShape_GetRadius(lua_State *L);
    int CapsuleShape_SetRadius(lua_State *L);
    int CapsuleShape_SetHeight(lua_State *L);
    int CapsuleShape_GetHeight(lua_State *L);

    CollisionShapeUserdata* CapsuleShapeCheckUserdata(lua_State *L, int index);
    void CapsuleShapeUserdataInitMetaTable(lua_State *L);
}
#endif