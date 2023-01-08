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


PhysicsWorld::WorldSettings WorldSettings_from_table(lua_State *L, int index){
    PhysicsWorld::WorldSettings settings;
    if (lua_istable(L, index)) {
        lua_pushvalue(L,index);
         lua_pushnil(L);  /* first key */
         while (lua_next(L, -2) != 0) {
           /* uses 'key' (at index -2) and 'value' (at index -1) */
            //printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
            const char* key = lua_tostring(L, -2);
            switch (hash_string(key)){
                case HASH_worldName:
                    settings.worldName = lua_tostring(L,-1);break;
                case HASH_gravity:
                    break;
                case HASH_persistentContactDistanceThreshold:
                    settings.persistentContactDistanceThreshold = luaL_checknumber(L,-1);break;
                case HASH_defaultFrictionCoefficient:
                    settings.defaultFrictionCoefficient = luaL_checknumber(L,-1);break;
                case HASH_defaultBounciness:
                    settings.defaultBounciness = luaL_checknumber(L,-1);break;
                case HASH_restitutionVelocityThreshold:
                    settings.restitutionVelocityThreshold = luaL_checknumber(L,-1);break;
                case HASH_isSleepingEnabled:
                    settings.restitutionVelocityThreshold = lua_toboolean(L,-1);break;
                case HASH_defaultVelocitySolverNbIterations:
                    settings.defaultVelocitySolverNbIterations = luaL_checknumber(L,-1);break;
                case HASH_defaultPositionSolverNbIterations:
                    settings.defaultPositionSolverNbIterations = luaL_checknumber(L,-1);break;
                case HASH_defaultTimeBeforeSleep:
                    settings.defaultTimeBeforeSleep = luaL_checknumber(L,-1);break;
                case HASH_defaultSleepLinearVelocity:
                    settings.defaultSleepLinearVelocity = luaL_checknumber(L,-1);break;
                case HASH_defaultSleepAngularVelocity:
                    settings.defaultSleepAngularVelocity = luaL_checknumber(L,-1);break;
                case HASH_cosAngleSimilarContactManifold:
                    settings.cosAngleSimilarContactManifold = luaL_checknumber(L,-1);break;
                default:
                    luaL_error(L, "unknown key:%s", key);
                    break;
            }
           /* removes 'value'; keeps 'key' for next iteration */
           lua_pop(L, 1);
        }
        lua_pop(L,1); //remove table
    }else{
        luaL_error(L,"WorldSettings should be table");
    }
    return settings;
}

}