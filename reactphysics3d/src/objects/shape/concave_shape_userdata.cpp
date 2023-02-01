#include "objects/base_userdata.h"
#include "static_hash.h"

#include "objects/shape/collision_shape_userdata.h"
#include "utils.h"




using namespace reactphysics3d;

namespace rp3dDefold {

static ConcaveShape* ConcaveShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (!shape->shape->isConvex()){
        return (ConcaveShape*)shape->shape;
    }else{
        luaL_error(L, "shape not ConcaveShape");
    }
}

int ConcaveShape_GetScale(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConcaveShape* shape = ConcaveShapeCheck(L,1);
    Vector3 v3 = shape->getScale();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}
int ConcaveShape_SetScale(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    ConcaveShape* shape = ConcaveShapeCheck(L,1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    shape->setScale(v3);
    return 0;
}

TriangleRaycastSide TriangleRaycastSideStringToEnum(lua_State *L,const char* str){
    switch (hash_string(str)){
        case HASH_FRONT:
            return TriangleRaycastSide::FRONT;
        case HASH_BACK:
            return TriangleRaycastSide::BACK;
        case HASH_FRONT_AND_BACK:
            return TriangleRaycastSide::FRONT_AND_BACK;
        default:
            luaL_error(L, "unknown TriangleRaycastSide:%s", str);
            break;
    }
}
const char * TriangleRaycastSideEnumToString(TriangleRaycastSide side){
    switch(side){
        case TriangleRaycastSide::FRONT:
            return "FRONT";
        case TriangleRaycastSide::BACK:
            return "BACK";
        case TriangleRaycastSide::FRONT_AND_BACK:
            return "FRONT_AND_BACK";
        default:
            assert(false);
    }
}

int ConcaveShape_SetRaycastTestType(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    ConcaveShape* shape = ConcaveShapeCheck(L,1);
    shape->setRaycastTestType(TriangleRaycastSideStringToEnum(L,luaL_checkstring(L,2)));
    return 0;
}

int ConcaveShape_GetRaycastTestType(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConcaveShape* shape = ConcaveShapeCheck(L,1);
    lua_pushstring(L,TriangleRaycastSideEnumToString(shape->getRaycastTestType()));
    return 1;
}


}
