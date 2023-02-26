#ifndef height_field_shape_h
#define height_field_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

namespace rp3dDefold {
    CollisionShapeUserdata* HeightFieldShapeCheckUserdata(lua_State *L, int index);
    void HeightFieldShapeUserdataInitMetaTable(lua_State *L);
}
#endif