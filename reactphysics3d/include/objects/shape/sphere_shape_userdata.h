#ifndef sphere_shape_h
#define sphere_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"

#define RP3D_SPHERE_SHAPE_META_FUNCTIONS \

namespace rp3dDefold {

    CollisionShapeUserdata* SphereShapeCheckUserdata(lua_State *L, int index);
    void SphereShapeUserdataInitMetaTable(lua_State *L);
}
#endif