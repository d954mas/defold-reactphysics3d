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

//use same for all Shaped
//use diff meta tables
class CollisionShapeUserdata : public BaseUserData {
    public:
        CollisionShape* shape;
        CollisionShapeUserdata(CollisionShape* shape);
        ~CollisionShapeUserdata();

        virtual void Destroy(lua_State *L);
};


    int CollisionShape_GetName(lua_State *L);
    int CollisionShape_GetType(lua_State *L);
    int CollisionShape_IsConvex(lua_State *L);
    int CollisionShape_IsPolyhedron(lua_State *L);
    int CollisionShape_GetLocalBounds(lua_State *L);
    int CollisionShape_GetId(lua_State *L);
    int CollisionShape_GetLocalInertiaTensor(lua_State *L);
    int CollisionShape_GetVolume(lua_State *L);
    int CollisionShape_ComputeAABB(lua_State *L);

    int CollisionShape_ToString(lua_State *L);


    void CollisionShapeUserdataInitMetaTable(lua_State *L);
    void CollisionShapePush(lua_State *L, CollisionShape* shape);
    CollisionShapeUserdata* CollisionShapeCheck(lua_State *L, int index);
}
#endif