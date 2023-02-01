#ifndef collision_shape_h
#define collision_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

#define META_NAME_BOX_SHAPE "rp3d::BoxShapeClass"
#define META_NAME_SPHERE_SHAPE "rp3d::SphereShapeClass"
#define META_NAME_CAPSULE_SHAPE "rp3d::CapsuleShapeClass"
#define META_NAME_CONVEX_MESH_SHAPE "rp3d::ConvexMeshShapeClass"
#define META_NAME_CONCAVE_MESH_SHAPE "rp3d::ConcaveMeshShapeClass"


#define RP3D_COLLISION_SHAPE_META_FUNCTIONS \
{"getName", CollisionShape_GetName},\
{"getType", CollisionShape_GetType},\
{"isPolyhedron", CollisionShape_IsPolyhedron},\
{"isConvex", CollisionShape_IsConvex},\
{"getLocalBounds", CollisionShape_GetLocalBounds},\
{"getId", CollisionShape_GetId},\
{"getLocalInertiaTensor", CollisionShape_GetLocalInertiaTensor},\
{"getVolume", CollisionShape_GetVolume},\
{"computeAABB", CollisionShape_ComputeAABB},\
{"__tostring", CollisionShape_ToString}\


namespace rp3dDefold {

//use same for all Shaped
//use diff meta tables
class CollisionShapeUserdata : public BaseUserData {
    public:
        reactphysics3d::CollisionShape* shape;
        CollisionShapeUserdata(reactphysics3d::CollisionShape* shape);
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
    void CollisionShapePush(lua_State *L, reactphysics3d::CollisionShape* shape);
    CollisionShapeUserdata* CollisionShapeCheck(lua_State *L, int index);
}
#endif