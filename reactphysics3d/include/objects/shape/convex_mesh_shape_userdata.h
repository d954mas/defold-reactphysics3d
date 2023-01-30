#ifndef convex_mesh_shape_h
#define convex_mesh_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

#define RP3D_CONVEX_MESH_SHAPE_META_FUNCTIONS \

namespace rp3dDefold {


    CollisionShapeUserdata* ConvexMeshShapeCheckUserdata(lua_State *L, int index);
    void ConvexMeshShapeUserdataInitMetaTable(lua_State *L);
}
#endif