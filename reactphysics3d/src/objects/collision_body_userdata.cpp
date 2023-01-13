#include "objects/collision_body_userdata.h"
#include "static_hash.h"
#include "utils.h"

#define META_NAME "rp3d::CollisionBody"
#define USERDATA_TYPE "rp3d::CollisionBody"

#define META_NAME_RIGID "rp3d::RigidBody"


using namespace reactphysics3d;

namespace rp3dDefold {

static void init(CollisionBodyUserdata* userdata,CollisionBody* body){
    assert(body->getUserData()==NULL);
    userdata->body = body;
    userdata->obj = body;
    userdata->user_data_ref = LUA_REFNIL;
}

CollisionBodyUserdata::CollisionBodyUserdata(CollisionBody* body): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    isRigidBody = false;
    init(this,body);
}

CollisionBodyUserdata::CollisionBodyUserdata(RigidBody* body): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME_RIGID;
    isRigidBody = true;
    init(this,body);
}



CollisionBodyUserdata::~CollisionBodyUserdata() {
}


CollisionBodyUserdata* CollisionBodyUserdataCheck(lua_State *L, int index) {
    CollisionBodyUserdata *userdata = (CollisionBodyUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

static int GetEntityId(lua_State *L){
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->body->getEntity().id);
	return 1;
}


static int ToString(lua_State *L){
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    if(userdata->isRigidBody){
         lua_pushfstring( L, "rp3d::RigidBody[%p]",(void *) userdata->body);
    }else{
         lua_pushfstring( L, "rp3d::CollisionBody[%p]",(void *) userdata->body);
    }
	return 1;
}

static int ToStringRigid(lua_State *L){
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::RigidBody[%p]",(void *) userdata->body);
	return 1;
}

void CollisionBodyUserdataInitMetaTable(lua_State *L){
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


void CollisionBodyUserdataRigidInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"getEntityId",GetEntityId},
        {"__tostring",ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME_RIGID);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));
}


void CollisionBodyUserdata::Destroy(lua_State *L){
    body = NULL;
    BaseUserData::Destroy(L);
}

}