#ifndef collision_shape_h
#define collision_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "reactphysics3d/reactphysics3d.h"
#include "objects/aabb.h"
#include "utils.h"

#define META_NAME_AABB "rp3d::AABBClass"



using namespace reactphysics3d;

namespace rp3dDefold {
    AABBLua::AABBLua(AABB aabb): aabb(aabb){}
    AABBLua::AABBLua(){

    }

    AABBLua::~AABBLua() {
    }

int AABB_GetCenter(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    AABBLua *aabb = AABBCheck(L, 1);

    Vector3 v3 = aabb->aabb.getCenter();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}
int AABB_GetMin(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    AABBLua *aabb = AABBCheck(L, 1);

    Vector3 v3 = aabb->aabb.getMin();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}
int AABB_SetMin(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    aabb->aabb.setMin(v3);
   	return 0;
}
int AABB_GetMax(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    AABBLua *aabb = AABBCheck(L, 1);

    Vector3 v3 = aabb->aabb.getMax();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}
int AABB_SetMax(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    aabb->aabb.setMax(v3);
   	return 0;
}
int AABB_GetExtent(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    AABBLua *aabb = AABBCheck(L, 1);

    Vector3 v3 = aabb->aabb.getExtent();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}

int AABB_Inflate(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 4);
    AABBLua *aabb = AABBCheck(L, 1);
    aabb->aabb.inflate(luaL_checknumber(L,2),luaL_checknumber(L,3),luaL_checknumber(L,4));
    return 0;
}

int AABB_TestCollision(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    AABBLua *aabb2 = AABBCheck(L, 2);
    lua_pushboolean(L, aabb->aabb.testCollision(aabb2->aabb));
    return 1;
}

int AABB_GetVolume(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    AABBLua *aabb = AABBCheck(L, 1);

    lua_pushnumber(L, aabb->aabb.getVolume());
    return 1;
}

int AABB_MergeWithAABB(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    AABBLua *aabb2 = AABBCheck(L, 2);
    aabb->aabb.mergeWithAABB(aabb2->aabb);
    return 0;
}

int AABB_MergeTwoAABBs(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3);
    AABBLua *aabb = AABBCheck(L, 1);
    AABBLua *aabb2 = AABBCheck(L, 2);
    AABBLua *aabb3 = AABBCheck(L, 3);
    aabb->aabb.mergeTwoAABBs(aabb2->aabb,aabb3->aabb);
    return 0;
}

int AABB_Contains(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    AABBLua *aabb2 = AABBCheck(L, 2);
    lua_pushboolean(L,aabb->aabb.contains(aabb2->aabb));
    return 1;
}

int AABB_ContainsPoint(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    lua_pushboolean(L,aabb->aabb.contains(v3));
    return 1;
}

int AABB_TestCollisionTriangleAABB(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 4);
    AABBLua *aabb = AABBCheck(L, 1);
    Vector3 trianglePoints[3];
    for (int i=1; i<=3; i++) {
        Vectormath::Aos::Vector3 *point = dmScript::CheckVector3(L, i+1);
        trianglePoints[i-1].x = point->getX();
        trianglePoints[i-1].y = point->getY();
        trianglePoints[i-1].z = point->getZ();
    }
    lua_pushboolean(L,aabb->aabb.testCollisionTriangleAABB(trianglePoints));
    return 1;
}

int AABB_TestRayIntersect(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 4);
    AABBLua *aabb = AABBCheck(L, 1);
    dmVMath::Vector3* dmRayOrigin = dmScript::CheckVector3(L, 2);
    Vector3 rayOrigin(dmRayOrigin->getX(),dmRayOrigin->getY(),dmRayOrigin->getZ());
    dmVMath::Vector3* dmRayDirectionInv = dmScript::CheckVector3(L, 3);
    Vector3 rayDirectionInv(dmRayDirectionInv->getX(),dmRayDirectionInv->getY(),dmRayDirectionInv->getZ());
    float rayMaxFraction = luaL_checknumber(L,4);

    lua_pushboolean(L,aabb->aabb.testRayIntersect(rayOrigin,rayDirectionInv,rayMaxFraction));
    return 1;
}

int AABB_ApplyScale(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    dmVMath::Vector3* dmScale = dmScript::CheckVector3(L, 2);
    Vector3 scale(dmScale->getX(),dmScale->getY(),dmScale->getZ());
    aabb->aabb.applyScale(scale);
    return 0;
}

int AABB_Raycast(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    AABBLua *aabb = AABBCheck(L, 1);
    Ray ray = CheckRay(L,2);
    Vector3 hitPoint;
    bool result =  aabb->aabb.raycast(ray,hitPoint);

    if(result){
        dmVMath::Vector3 dmHitPoint(hitPoint.x,hitPoint.y,hitPoint.z);
        dmScript::PushVector3(L, dmHitPoint);
    }else{
        lua_pushnil(L);
    }
    return 1;
}



    
int AABB_ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    AABBLua* aabb = AABBCheck(L,1);
    lua_pushfstring( L, "rp3d::AABB[%p]",(void *) &aabb->aabb);
    return 1;
}

int AABB_GC(lua_State *L){
    AABBLua **aabb = reinterpret_cast<AABBLua **>(lua_touserdata(L, 1));
    delete *aabb;
    return 0;
}

AABBLua* AABBCheck(lua_State* L, int index){
    AABBLua *shape = NULL;

    if(luaL_checkudata(L, index, META_NAME_AABB)){
        return  *static_cast<AABBLua**>(luaL_checkudata(L, index, META_NAME_AABB));
    }else{
        luaL_error(L, "Not aabb");
    }
}


void AABBPush(lua_State *L, AABB aabb){
    AABBLua *aabbLua = new AABBLua(aabb);
    *static_cast<AABBLua**>(lua_newuserdata(L, sizeof(AABBLua*))) = aabbLua;
    if(luaL_newmetatable(L, META_NAME_AABB)){
        static const luaL_Reg functions[] ={
            {"getCenter", AABB_GetCenter},
            {"getMin", AABB_GetMin},
            {"setMin", AABB_SetMin},
            {"getMax", AABB_GetMax},
            {"setMax", AABB_SetMax},
            {"getExtent", AABB_GetExtent},
            {"inflate", AABB_Inflate},
            {"testCollision", AABB_TestCollision},
            {"getVolume", AABB_GetVolume},
            {"mergeWithAABB", AABB_MergeWithAABB},
            {"mergeTwoAABBs", AABB_MergeTwoAABBs},
            {"contains", AABB_Contains},
            {"containsPoint", AABB_ContainsPoint},
            {"testCollisionTriangleAABB", AABB_TestCollisionTriangleAABB},
            {"testRayIntersect", AABB_TestRayIntersect},
            {"raycast", AABB_Raycast},
            {"applyScale", AABB_ApplyScale},
            {"__tostring", AABB_ToString},
            {"__gc", AABB_GC},
            {0, 0}
        };
        luaL_register(L, NULL,functions);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
    }
    lua_setmetatable(L, -2);
}
}
#endif