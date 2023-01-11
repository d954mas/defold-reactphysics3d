#ifndef collision_shape_h
#define collision_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "static_hash.h"

#define META_NAME_BOX_SHAPE "rp3d::BoxShapeClass"


using namespace reactphysics3d;

namespace rp3dDefold {
    class CollisionShapeLua {
    public:
        CollisionShape* shape;
        CollisionShapeLua(CollisionShape* shape);
        ~CollisionShapeLua();
    };


    int CollisionShape_GetName(lua_State *L);
    int CollisionShape_GetType(lua_State *L);
    int CollisionShape_GC(lua_State *L);
    int CollisionShape_ToString(lua_State *L);
    int CollisionShape_IsConvex(lua_State *L);
    int CollisionShape_IsPolyhedron(lua_State *L);
    int CollisionShape_GetLocalBounds(lua_State *L);
    int CollisionShape_GetId(lua_State *L);
    int CollisionShape_GetLocalInertiaTensor(lua_State *L);
    int CollisionShape_GetVolume(lua_State *L);
    int CollisionShape_ComputeAABB(lua_State *L);

   // const char* CollisionShapeNameEnumToString(CollisionShapeName name);

    //CollisionShapeName CollisionShapeNameStringToEnum(lua_State *L,const char* str);




    void CollisionShapePush(lua_State *L, CollisionShape* shape);
    CollisionShapeLua* CollisionShapeCheck(lua_State *L, int index);
}
#endif