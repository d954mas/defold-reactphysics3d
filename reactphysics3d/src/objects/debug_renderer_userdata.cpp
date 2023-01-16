#include "static_hash.h"
#include "objects/debug_renderer_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::DebugRenderer"
#define USERDATA_TYPE "rp3d::DebugRenderer"


using namespace reactphysics3d;

namespace rp3dDefold {

DebugRendererUserdata::DebugRendererUserdata(DebugRenderer* renderer): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    this->renderer = renderer;
    this->obj = renderer;
    this->renderer->setUserData(this);
}

DebugRendererUserdata::~DebugRendererUserdata() {

}


DebugRendererUserdata* DebugRendererUserdataCheck(lua_State *L, int index) {
    DebugRendererUserdata *userdata = (DebugRendererUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

static int SetIsDebugItemDisplayed(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    DebugRenderer::DebugItem item = DebugRendererDebugItemStringToEnum(L,lua_tostring(L,2));
    bool isDisplayed = lua_toboolean(L,3);
    userdata->renderer->setIsDebugItemDisplayed(item,isDisplayed);
    return 0;
}

static int GetIsDebugItemDisplayed(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    DebugRenderer::DebugItem item = DebugRendererDebugItemStringToEnum(L,lua_tostring(L,2));
    lua_pushboolean(L,userdata->renderer->getIsDebugItemDisplayed(item));
    return 1;
}

static int SetContactPointSphereRadius (lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    float radius = luaL_checknumber(L,2);
    userdata->renderer->setContactPointSphereRadius(radius);
    return 0;
}

static int GetContactPointSphereRadius(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->renderer->getContactPointSphereRadius());
    return 1;
}

static int SetContactNormalLength (lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    float radius = luaL_checknumber(L,2);
    userdata->renderer->setContactNormalLength(radius);
    return 0;
}

static int GetContactNormalLength(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->renderer->getContactNormalLength());
    return 1;
}

static int Draw(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
	return 0;
}

static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::DebugRenderer[%p]",(void *) userdata->renderer);
	return 1;
}

void DebugRendererUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"setIsDebugItemDisplayed",SetIsDebugItemDisplayed},
        {"getIsDebugItemDisplayed",GetIsDebugItemDisplayed},
        {"getContactPointSphereRadius",GetContactPointSphereRadius},
        {"setContactPointSphereRadius",SetContactPointSphereRadius},
        {"getContactNormalLength",GetContactNormalLength},
        {"setContactNormalLength",SetContactNormalLength},
        {"draw",Draw},
        {"__tostring",ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));
}


void DebugRendererUserdata::Destroy(lua_State *L){
    renderer->setUserData(NULL);
    renderer = NULL;
    BaseUserData::Destroy(L);
}

void DebugRendererPush(lua_State *L, DebugRenderer* renderer){
    if(renderer->getUserData()!=NULL){
        DebugRendererUserdata* userdata =(DebugRendererUserdata*) renderer->getUserData();
        userdata->Push(L);
    }else{
        DebugRendererUserdata* userdata = new DebugRendererUserdata(renderer);
        userdata->Push(L);
    }
}

DebugRenderer::DebugItem DebugRendererDebugItemStringToEnum(lua_State *L,const char* str){
    switch (hash_string(str)){
        case HASH_COLLIDER_AABB:
            return DebugRenderer::DebugItem::COLLIDER_AABB;
        case HASH_COLLIDER_BROADPHASE_AABB:
            return DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB;
        case HASH_COLLISION_SHAPE:
            return DebugRenderer::DebugItem::COLLISION_SHAPE;
        case HASH_CONTACT_POINT:
            return DebugRenderer::DebugItem::CONTACT_POINT;
        case HASH_CONTACT_NORMAL:
            return DebugRenderer::DebugItem::CONTACT_NORMAL;
        default:
            luaL_error(L, "unknown DebugRenderer::DebugItem:%s", str);
            break;
    }
}
const char * DebugRendererDebugItemEnumToString(DebugRenderer::DebugItem name){
    switch(name){
        case DebugRenderer::DebugItem::COLLIDER_AABB:
            return "COLLIDER_AABB";
        case DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB:
            return "COLLIDER_BROADPHASE_AABB";
        case DebugRenderer::DebugItem::COLLISION_SHAPE:
            return "COLLISION_SHAPE";
        case DebugRenderer::DebugItem::CONTACT_POINT:
            return "CONTACT_POINT";
        case DebugRenderer::DebugItem::CONTACT_NORMAL:
            return "CONTACT_NORMAL";
        default:
            assert(false);
    }
}

}