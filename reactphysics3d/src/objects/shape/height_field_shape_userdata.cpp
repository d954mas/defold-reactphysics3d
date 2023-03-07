#include "objects/base_userdata.h"
#include "static_hash.h"

#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/concave_shape_userdata.h"
#include "objects/shape/height_field_shape_userdata.h"
#include "utils.h"



using namespace reactphysics3d;

namespace rp3dDefold {

CollisionShapeUserdata* HeightFieldShapeCheckUserdata(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::HEIGHTFIELD){
        return shape;
    }else{
        luaL_error(L, "shape not HeightFieldShape");
    }
}

static HeightFieldShape* HeightFieldShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::HEIGHTFIELD){
        return (HeightFieldShape*)shape->shape;
    }else{
        luaL_error(L, "shape not HeightFieldShape");
    }
}

int HeightFieldShape_getNbRows(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HeightFieldShape* shape = HeightFieldShapeCheck(L,1);
    lua_pushnumber(L,shape->getNbRows());
    return 1;
}

int HeightFieldShape_getNbColumns(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HeightFieldShape* shape = HeightFieldShapeCheck(L,1);
    lua_pushnumber(L,shape->getNbColumns());
    return 1;
}
int HeightFieldShape_getVertexAt(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);
    HeightFieldShape* shape = HeightFieldShapeCheck(L,1);
    int x = luaL_checknumber(L,2);
    if(x<0 || x>= shape->getNbColumns()){
        luaL_error(L, "Bad x:%d. Columns:%d.", x, shape->getNbColumns());
    }
    int y = luaL_checknumber(L,3);
    if(y<0 || y>= shape->getNbRows()){
        luaL_error(L, "Bad y:%d. Rows:%d.", y, shape->getNbRows());
    }

    Vector3 v3 = shape->getVertexAt(x,y);
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}

int HeightFieldShape_getHeightAt(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);
    HeightFieldShape* shape = HeightFieldShapeCheck(L,1);
    int x = luaL_checknumber(L,2);
    if(x<0 || x>= shape->getNbColumns()){
        luaL_error(L, "Bad x:%d. Columns:%d.", x, shape->getNbColumns());
    }
    int y = luaL_checknumber(L,3);
    if(y<0 || y>= shape->getNbRows()){
        luaL_error(L, "Bad y:%d. Rows:%d.", y, shape->getNbRows());
    }

    lua_pushnumber(L,shape->getHeightAt(x,y));
    return 1;
}

int HeightFieldShape_getHeightDataType(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HeightFieldShape* shape = HeightFieldShapeCheck(L,1);
    HeightFieldShape::HeightDataType type = shape->getHeightDataType();
    switch (type){
        case HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE:
            lua_pushstring(L,"HEIGHT_FLOAT_TYPE");
            break;
        case HeightFieldShape::HeightDataType::HEIGHT_DOUBLE_TYPE:
            lua_pushstring(L,"HEIGHT_DOUBLE_TYPE");
            break;
        case HeightFieldShape::HeightDataType::HEIGHT_INT_TYPE:
            lua_pushstring(L,"HEIGHT_INT_TYPE");
            break;
        default:
            assert("can't be here");
            break;
    }
    return 1;
}


void HeightFieldShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_COLLISION_SHAPE_META_FUNCTIONS,
            RP3D_CONCAVE_SHAPE_META_FUNCTIONS,
            RP3D_HEIGHTFIELD_SHAPE_META_FUNCTIONS,
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_HEIGHTFIELD_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

}
