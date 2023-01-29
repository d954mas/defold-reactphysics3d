#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/capsule_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/convex_shape_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static CapsuleShape* CapsuleShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::CAPSULE){
        return (CapsuleShape*)shape->shape;
    }else{
        luaL_error(L, "shape not CapsuleShape");
    }
}

CollisionShapeUserdata* CapsuleShapeCheckUserdata(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::CAPSULE){
        return shape;
    }else{
        luaL_error(L, "shape not CapsuleShape");
    }
}

int CapsuleShape_GetRadius(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CapsuleShape* shape = CapsuleShapeCheck(L,1);
    lua_pushnumber(L,shape->getRadius());
    return 1;
}
int CapsuleShape_SetRadius(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CapsuleShape* shape = CapsuleShapeCheck(L,1);
    shape->setRadius(luaL_checknumber(L,2));
    return 0;
}

int CapsuleShape_GetHeight(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CapsuleShape* shape = CapsuleShapeCheck(L,1);
    lua_pushnumber(L,shape->getHeight());
    return 1;
}
int CapsuleShape_SetHeight(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CapsuleShape* shape = CapsuleShapeCheck(L,1);
    shape->setHeight(luaL_checknumber(L,2));
    return 0;
}



void CapsuleShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_COLLISION_SHAPE_META_FUNCTIONS,
            RP3D_CONVEX_SHAPE_META_FUNCTIONS,
            RP3D_CAPSULE_SHAPE_META_FUNCTIONS,
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_CAPSULE_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}



}