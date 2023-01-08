#define EXTENSION_NAME reactphysics3dDefold
#define LIB_NAME "reactphysics3d"
#define MODULE_NAME "rp3d"

#include <dmsdk/sdk.h>
#include "utils.h"
#include "objects/objects.h"
#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;
using namespace rp3dDefold;

static PhysicsCommon physicsCommon;


static int createPhysicsWorldLua(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 0,1);
    PhysicsWorld* world = NULL;
    if (lua_gettop(L) == 1) {
        PhysicsWorld::WorldSettings settings = WorldSettings_from_table(L,1);
        world = physicsCommon.createPhysicsWorld(settings);
    }else{
        world = physicsCommon.createPhysicsWorld();
    }
    WorldUserdata *data = new WorldUserdata(world);
    data->Push(L);
    return 1;
}
static int destroyPhysicsWorldLua(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L,1);
    physicsCommon.destroyPhysicsWorld(data->world);
    data->Destroy(L);
    delete data;
    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] ={
	 {"createPhysicsWorld", createPhysicsWorldLua},
	 {"destroyPhysicsWorld", destroyPhysicsWorldLua},
	{0, 0}
};

static void LuaInit(lua_State* L){
	int top = lua_gettop(L);
	// Register lua names
	luaL_register(L, MODULE_NAME, Module_methods);

	 lua_newtable(L);
        lua_pushnumber(L, 0);
        lua_setfield(L, -2, "BAUMGARTE_CONTACTS");
        lua_pushnumber(L, 1);
        lua_setfield(L, -2, "SPLIT_IMPULSES");
     lua_setfield(L, -2, "ContactsPositionCorrectionTechnique");


	lua_pop(L, 1);
	assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}
static dmExtension::Result InitializeMyExtension(dmExtension::Params* params){
    WorldUserdataInitMetaTable(params->m_L);
	LuaInit(params->m_L);
	printf("Registered %s Extension\n", MODULE_NAME);
	return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params){return dmExtension::RESULT_OK;}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeMyExtension, AppFinalizeMyExtension, InitializeMyExtension, 0, 0, FinalizeMyExtension)