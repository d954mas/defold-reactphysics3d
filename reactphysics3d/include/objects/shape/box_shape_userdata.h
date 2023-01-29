#ifndef box_shape_h
#define box_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

#define RP3D_BOX_SHAPE_META_FUNCTIONS \
{"getHalfExtents", BoxShape_GetHalfExtents},\
{"setHalfExtents", BoxShape_SetHalfExtents}\


namespace rp3dDefold {

    int BoxShape_GetHalfExtents(lua_State *L);
    int BoxShape_SetHalfExtents(lua_State *L);

    CollisionShapeUserdata* BoxShapeCheckUserdata(lua_State *L, int index);
    void BoxShapeUserdataInitMetaTable(lua_State *L);
}
#endif