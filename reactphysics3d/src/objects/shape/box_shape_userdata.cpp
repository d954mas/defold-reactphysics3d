#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/convex_shape_userdata.h"
#include "objects/shape/convex_polyhedron_shape_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static BoxShape* BoxShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::BOX){
        return (BoxShape*)shape->shape;
    }else{
        luaL_error(L, "shape not BoxShape");
    }
}

CollisionShapeUserdata* BoxShapeCheckUserdata(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::BOX){
        return shape;
    }else{
        luaL_error(L, "shape not BoxShape");
    }
}

void BoxShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_COLLISION_SHAPE_META_FUNCTIONS,
            RP3D_CONVEX_SHAPE_META_FUNCTIONS,
            RP3D_CONVEX_POLYHEDRON_SHAPE_META_FUNCTIONS,
            RP3D_BOX_SHAPE_META_FUNCTIONS,
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_BOX_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

int BoxShape_GetHalfExtents(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    BoxShape* shape = BoxShapeCheck(L,1);
    Vector3 v3 = shape->getHalfExtents();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}
int BoxShape_SetHalfExtents(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    BoxShape* shape = BoxShapeCheck(L,1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    shape->setHalfExtents(v3);
    return 0;
}



}