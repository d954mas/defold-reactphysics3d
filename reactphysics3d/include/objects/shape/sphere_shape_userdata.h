#ifndef sphere_shape_h
#define sphere_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

#define RP3D_SPHERE_SHAPE_META_FUNCTIONS \
{"getRadius", SphereShape_GetRadius},\
{"setRadius", SphereShape_SetRadius}

namespace rp3dDefold {

    int SphereShape_GetRadius(lua_State *L);
    int SphereShape_SetRadius(lua_State *L);

    CollisionShapeUserdata* SphereShapeCheckUserdata(lua_State *L, int index);
    void SphereShapeUserdataInitMetaTable(lua_State *L);
}
#endif