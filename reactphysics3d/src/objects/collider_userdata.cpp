#include "objects/collision_body_userdata.h"
#include "static_hash.h"
#include "objects/collider_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::Collider"
#define USERDATA_TYPE "rp3d::Collider"


using namespace reactphysics3d;

namespace rp3dDefold {

ColliderUserdata::ColliderUserdata(Collider* collider): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    this->collider = collider;
}

ColliderUserdata::~ColliderUserdata() {

}


ColliderUserdata* ColliderUserdataCheck(lua_State *L, int index) {
    ColliderUserdata *userdata = (ColliderUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

static int GetEntityId(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ColliderUserdata *userdata = ColliderUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->collider->getEntity().id);
	return 1;
}

static int GetUserData(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ColliderUserdata *userdata = ColliderUserdataCheck(L, 1);
    lua_rawgeti(L,LUA_REGISTRYINDEX,userdata->user_data_ref);
	return 1;
}
static int SetUserData(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    ColliderUserdata *userdata = ColliderUserdataCheck(L, 1);
    if (lua_istable(L, 2)) {
        luaL_unref(L, LUA_REGISTRYINDEX, userdata->user_data_ref);
        lua_pushvalue(L,2);
        userdata->user_data_ref = luaL_ref(L,LUA_REGISTRYINDEX);
    }else if (lua_isnil(L, 2)){
        luaL_unref(L, LUA_REGISTRYINDEX, userdata->user_data_ref);
        userdata->user_data_ref = LUA_REFNIL;
    }else {
       luaL_error(L,"userdata can be only table or nil");
    }
	return 0;
}

static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ColliderUserdata *userdata = ColliderUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::Collider[%p]",(void *) userdata->collider);
	return 1;
}

void ColliderUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"getEntityId",GetEntityId},
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


void ColliderUserdata::Destroy(lua_State *L){
    collider->setUserData(NULL);
    collider = NULL;
    luaL_unref(L, LUA_REGISTRYINDEX, user_data_ref);
    user_data_ref = LUA_REFNIL;
    BaseUserData::Destroy(L);
}

}