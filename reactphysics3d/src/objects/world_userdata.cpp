#include "objects/world_userdata.h"
#include "static_hash.h"
#include "utils.h"

#define META_NAME "rp3d::World"
#define USERDATA_TYPE "rp3d::World"


using namespace reactphysics3d;

namespace rp3dDefold {


WorldUserdata::WorldUserdata(PhysicsWorld* world): BaseUserData(USERDATA_TYPE){
    this->world = world;
    this->obj = world;
}


WorldUserdata::~WorldUserdata() {
}


WorldUserdata* WorldUserdataCheck(lua_State *L, int index) {
    WorldUserdata *lua_world = (WorldUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return lua_world;
}

static int ToString(lua_State *L){
    check_arg_count(L, 1);

    WorldUserdata *lua_world = WorldUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::World[%p]",(void *) lua_world->world);
	return 1;
}

void WorldUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
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

void WorldUserdata::Destroy(lua_State *L){
    world = NULL;
    BaseUserData::Destroy(L);
}

}