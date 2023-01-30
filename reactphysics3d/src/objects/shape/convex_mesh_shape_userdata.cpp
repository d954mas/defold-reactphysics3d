#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/convex_mesh_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/convex_shape_userdata.h"
#include "objects/shape/convex_polyhedron_shape_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static ConvexMeshShape* ConvexMeshShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::CONVEX_MESH){
        return (ConvexMeshShape*)shape->shape;
    }else{
        luaL_error(L, "shape not ConvexMeshShape");
    }
}

CollisionShapeUserdata* ConvexMeshShapeCheckUserdata(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::CONVEX_MESH){
        return shape;
    }else{
        luaL_error(L, "shape not ConvexMeshShape");
    }
}

int ConvexMeshShape_GetScale(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConvexMeshShape* shape = ConvexMeshShapeCheck(L,1);
    Vector3 v3 = shape->getScale();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}
int ConvexMeshShape_SetScale(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    ConvexMeshShape* shape = ConvexMeshShapeCheck(L,1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    shape->setScale(v3);
    return 0;
}


void ConvexMeshShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_COLLISION_SHAPE_META_FUNCTIONS,
            RP3D_CONVEX_SHAPE_META_FUNCTIONS,
            RP3D_CONVEX_POLYHEDRON_SHAPE_META_FUNCTIONS,
            RP3D_CONVEX_MESH_SHAPE_META_FUNCTIONS,
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_CONVEX_MESH_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}




}