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
    this->metatable_name = META_NAME;
}


WorldUserdata::~WorldUserdata() {
}


WorldUserdata* WorldUserdataCheck(lua_State *L, int index) {
    WorldUserdata *lua_world = (WorldUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return lua_world;
}

static int GetName(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    push_std_string(L,data->world->getName());
	return 1;
}

static int GetNbIterationsVelocitySolver(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushnumber(L, data->world->getNbIterationsVelocitySolver());
	return 1;
}

static int GetNbIterationsPositionSolver(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushnumber(L, data->world->getNbIterationsPositionSolver());
	return 1;
}

static int GetTimeBeforeSleep(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushnumber(L, data->world->getTimeBeforeSleep());
	return 1;
}

static int GetSleepAngularVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushnumber(L, data->world->getSleepAngularVelocity());
	return 1;
}

static int GetSleepLinearVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushnumber(L, data->world->getSleepLinearVelocity());
	return 1;
}

static int GetNbCollisionBodies(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushnumber(L, data->world->getNbCollisionBodies());
	return 1;
}

static int GetNbRigidBodies(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushnumber(L, data->world->getNbRigidBodies());
	return 1;
}

static int IsSleepingEnabled(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushboolean(L, data->world->isSleepingEnabled());
	return 1;
}

static int GetGravity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);

    Vector3 gravity = data->world->getGravity();

    dmVMath::Vector3 result(gravity.x,gravity.y,gravity.z);
    dmScript::PushVector3(L, result);
	return 1;
}

static int SetGravity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    dmVMath::Vector3* dmGravity = dmScript::CheckVector3(L, 2);

    Vector3 gravity(dmGravity->getX(),dmGravity->getY(),dmGravity->getZ());
    data->world->setGravity(gravity);
	return 0;
}

static int Update(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->update(lua_tonumber(L,2));
	return 0;
}

static int SetNbIterationsVelocitySolver(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->setNbIterationsVelocitySolver(luaL_checknumber(L,2));
	return 0;
}

static int SetNbIterationsPositionSolver(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->setNbIterationsPositionSolver(luaL_checknumber(L,2));
	return 0;
}

static int SetSleepAngularVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->setSleepAngularVelocity(luaL_checknumber(L,2));
	return 0;
}

static int SetSleepLinearVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->setSleepLinearVelocity(luaL_checknumber(L,2));
	return 0;
}

static int SetTimeBeforeSleep(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->setTimeBeforeSleep(luaL_checknumber(L,2));
	return 0;
}


static int SetContactsPositionCorrectionTechnique(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    const char* str = lua_tostring(L,2);
    switch (hash_string(str)){
        case HASH_BAUMGARTE_CONTACTS:
             data->world->setContactsPositionCorrectionTechnique(ContactsPositionCorrectionTechnique::BAUMGARTE_CONTACTS);
            break;
        case HASH_SPLIT_IMPULSES:
            data->world->setContactsPositionCorrectionTechnique(ContactsPositionCorrectionTechnique::SPLIT_IMPULSES);
            break;
        default:
             luaL_error(L, "unknown ContactsPositionCorrectionTechnique");
             break;
    }

	return 0;
}

static int EnableDisableJoints(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->enableDisableJoints();
	return 0;
}

static int IsGravityEnabled(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushboolean(L,data->world->isGravityEnabled());
	return 1;
}

static int SetIsGravityEnabled(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->setIsGravityEnabled(lua_toboolean(L,2));
	return 0;
}

static int GetIsDebugRenderingEnabled(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    lua_pushboolean(L,data->world->getIsDebugRenderingEnabled());
	return 1;
}

static int SetIsDebugRenderingEnabled(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->setIsDebugRenderingEnabled(lua_toboolean(L,2));
	return 0;
}

static int EnableSleeping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->enableSleeping(lua_toboolean(L,2));
	return 0;
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
        {"getName",GetName},
        {"getGravity",GetGravity},
        {"setGravity",SetGravity},
        {"getNbIterationsVelocitySolver",GetNbIterationsVelocitySolver},
        {"getNbIterationsPositionSolver",GetNbIterationsPositionSolver},
        {"isSleepingEnabled",IsSleepingEnabled},
        {"enableSleeping",EnableSleeping},
        {"getTimeBeforeSleep",GetTimeBeforeSleep},
        {"setTimeBeforeSleep",SetTimeBeforeSleep},
        {"getSleepLinearVelocity",GetSleepLinearVelocity},
        {"setSleepLinearVelocity",SetSleepLinearVelocity},
        {"getSleepAngularVelocity",GetSleepAngularVelocity},
        {"setSleepAngularVelocity",SetSleepAngularVelocity},
        {"update",Update},
        {"setNbIterationsVelocitySolver",SetNbIterationsVelocitySolver},
        {"setNbIterationsPositionSolver",SetNbIterationsPositionSolver},
        {"setContactsPositionCorrectionTechnique",SetContactsPositionCorrectionTechnique},
        {"enableDisableJoints",EnableDisableJoints},
        {"isGravityEnabled",IsGravityEnabled},
        {"setIsGravityEnabled",SetIsGravityEnabled},
        {"getNbCollisionBodies",GetNbCollisionBodies},
        {"getNbRigidBodies",GetNbRigidBodies},
        {"getIsDebugRenderingEnabled",GetIsDebugRenderingEnabled},
        {"setIsDebugRenderingEnabled",SetIsDebugRenderingEnabled},
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
                case HASH_gravity:{
                    dmVMath::Vector3* value = dmScript::CheckVector3(L, -1);
                    settings.gravity.x = value->getX();
                    settings.gravity.y = value->getY();
                    settings.gravity.z = value->getZ();
                    break;
                }
                case HASH_persistentContactDistanceThreshold:
                    settings.persistentContactDistanceThreshold = luaL_checknumber(L,-1);break;
                case HASH_defaultFrictionCoefficient:
                    settings.defaultFrictionCoefficient = luaL_checknumber(L,-1);break;
                case HASH_defaultBounciness:
                    settings.defaultBounciness = luaL_checknumber(L,-1);break;
                case HASH_restitutionVelocityThreshold:
                    settings.restitutionVelocityThreshold = luaL_checknumber(L,-1);break;
                case HASH_isSleepingEnabled:
                    settings.isSleepingEnabled = lua_toboolean(L,-1);break;
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