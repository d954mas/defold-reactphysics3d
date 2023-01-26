#ifndef box_shape_h
#define box_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "static_hash.h"
#include "objects/shape/collision_shape_userdata.h"



using namespace reactphysics3d;

namespace rp3dDefold {
    CollisionShapeUserdata* BoxShapeCheck(lua_State *L, int index);
    void BoxShapeShapeUserdataInitMetaTable(lua_State *L);
}
#endif