#include "objects/world_userdata.h"
#include "objects/collision_body_userdata.h"
#include "objects/debug_renderer_userdata.h"
#include "objects/collider_userdata.h"
#include "static_hash.h"
#include "utils.h"


#define META_NAME "rp3d::World"
#define USERDATA_TYPE "rp3d::World"


using namespace reactphysics3d;

namespace rp3dDefold {

class LuaRayCastCallback : public RaycastCallback  {
    public:
        lua_State *L;
        bool error;
        const char *error_message;

        LuaRayCastCallback(lua_State *L){  // This is the constructor
            this->L = L;
            error = false;
            error_message = NULL;
        }

        float notifyRaycastHit(const RaycastInfo &raycastInfo) {
            lua_pushvalue(L,-1);
            pushRp3dRaycastInfo(L,raycastInfo);
            if (lua_pcall(L, 1, 1, 0) == 0){
                float result = lua_tonumber(L,-1);
                lua_pop(L,1);
                return result;
            }else{
                error = true;
                error_message = lua_tostring(L,-1);
                lua_pop(L,1);
                return 0;
            }
        }
};

class NewTableOverlapCallback : public OverlapCallback  {
    public:
        lua_State *L;
        NewTableOverlapCallback(lua_State *L) : L(L){}

       void begin(){
            lua_newtable(L);
       }
       void onOverlap(OverlapCallback::CallbackData &callbackData){
            for(int i=0;i<callbackData.getNbOverlappingPairs();i++){
                OverlapPair pair = callbackData.getOverlappingPair(i);
                lua_newtable(L);
                ColliderPush(L,pair.getCollider1());
                lua_setfield(L, -2, "collider1");
                ColliderPush(L,pair.getCollider2());
                lua_setfield(L, -2, "collider2");

                CollisionBodyPush(L,pair.getBody1());
                lua_setfield(L, -2, "body1");
                CollisionBodyPush(L,pair.getBody2());
                lua_setfield(L, -2, "body2");

                lua_pushstring(L,OverlapPairEventTypeEnumToString(pair.getEventType()));
                lua_setfield(L, -2, "eventType");

                lua_rawseti(L, -2, i+1);

            }
        }
};

class NewTableCollisionCallback  : public CollisionCallback   {
    public:
        lua_State *L;
        NewTableCollisionCallback(lua_State *L) : L(L){}

        void begin(){
            lua_newtable(L);
        }
        void onContact(const CollisionCallback::CallbackData &callbackData){
            for(int i=0;i<callbackData.getNbContactPairs();i++){
                ContactPair pair = callbackData.getContactPair(i);
                lua_newtable(L);
                    ColliderPush(L,pair.getCollider1());
                    lua_setfield(L, -2, "collider1");
                    ColliderPush(L,pair.getCollider2());
                    lua_setfield(L, -2, "collider2");

                    CollisionBodyPush(L,pair.getBody1());
                    lua_setfield(L, -2, "body1");
                    CollisionBodyPush(L,pair.getBody2());
                    lua_setfield(L, -2, "body2");

                    lua_pushstring(L,ContactPairEventTypeEnumToString(pair.getEventType()));
                    lua_setfield(L, -2, "eventType");

                    lua_newtable(L);
                    for(int j=0;j<pair.getNbContactPoints();j++){
                        ContactPoint point = pair.getContactPoint(j);
                        dmVMath::Vector3 dmWorldNormal;
                        dmVMath::Vector3 dmLocalPointOnCollider1;
                        dmVMath::Vector3 dmLocalPointOnCollider2;

                        dmWorldNormal.setX(point.getWorldNormal().x);
                        dmWorldNormal.setY(point.getWorldNormal().y);
                        dmWorldNormal.setZ(point.getWorldNormal().z);

                        dmLocalPointOnCollider1.setX(point.getLocalPointOnCollider1().x);
                        dmLocalPointOnCollider1.setY(point.getLocalPointOnCollider1().y);
                        dmLocalPointOnCollider1.setZ(point.getLocalPointOnCollider1().z);

                        dmLocalPointOnCollider2.setX(point.getLocalPointOnCollider2().x);
                        dmLocalPointOnCollider2.setY(point.getLocalPointOnCollider2().y);
                        dmLocalPointOnCollider2.setZ(point.getLocalPointOnCollider2().z);

                        lua_newtable(L);
                            dmScript::PushVector3(L, dmWorldNormal);
                            lua_setfield(L, -2, "worldNormal");
                            dmScript::PushVector3(L, dmLocalPointOnCollider1);
                            lua_setfield(L, -2, "localPointOnCollider1");
                            dmScript::PushVector3(L, dmLocalPointOnCollider2);
                            lua_setfield(L, -2, "localPointOnCollider2");
                            lua_pushnumber(L,point.getPenetrationDepth());
                            lua_setfield(L, -2, "penetrationDepth");
                        lua_rawseti(L, -2, j+1);
                    }
                    lua_setfield(L, -2, "contacts");

                    lua_rawseti(L, -2, i+1);
            }
        }
};


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
    //reset or renderer will have prev frame data
    data->world->getDebugRenderer().reset();
	return 0;
}

static int EnableSleeping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    data->world->enableSleeping(lua_toboolean(L,2));
	return 0;
}

static int CreateCollisionBody(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    Transform transform = checkRp3dTransform(L,2);
    CollisionBody* body = data->world->createCollisionBody(transform);
    CollisionBodyPush(L,body);
	return 1;
}

static int CreateRigidBody(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    Transform transform = checkRp3dTransform(L,2);
    RigidBody* body = data->world->createRigidBody(transform);
    CollisionBodyPush(L,body);
	return 1;
}

static int DestroyCollisionBody(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    CollisionBodyUserdata* body = CollisionBodyUserdataCheck(L,2);
    if(body->isRigidBody){
        luaL_error(L,"can't destroy RigidBody.Need CollisionBody");
    }
    CollisionBody* collisionBody = body->body;
    body->Destroy(L);
    delete body;
    data->world->destroyCollisionBody(collisionBody);
   	return 0;
}

static int DestroyRigidBody(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    CollisionBodyUserdata* body = CollisionBodyUserdataCheck(L,2);
    if(!body->isRigidBody){
        luaL_error(L,"can't destroy CollisionBody.Need RigidBody");
    }
    RigidBody* rigidBody = static_cast<RigidBody*>(body->body);
    body->Destroy(L);
    delete body;
    //TODO DESTROY JOINS USERDATA

    data->world->destroyRigidBody(rigidBody);
   	return 0;
}

static int GetDebugRenderer(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    DebugRenderer& renderer = data->world->getDebugRenderer();
    DebugRendererPush(L,&renderer);
	return 1;
}

static int Raycast(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3,4);
    WorldUserdata *world = WorldUserdataCheck(L, 1);
    Ray ray = CheckRay(L,2);

    if (!lua_isfunction(L, 3)){
        luaL_error(L,"callback is not function");
        return 0;
    }

    LuaRayCastCallback* cb = new LuaRayCastCallback(L);

    //cb function on top
    if (lua_gettop(L) == 4){
        lua_pushvalue(L,3);
        world->world->raycast(ray, cb, luaL_checknumber(L,4));
     }else{
        lua_pushvalue(L,3);
        world->world->raycast(ray, cb);
     }

    lua_pop(L,1);
    if(cb->error){
        const char *error_message = cb->error_message;
        delete cb;
        luaL_error(L,"%s",error_message);
    }else{
        delete cb;
    }


    return 0;
}

static int TestOverlap2Bodies(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    CollisionBodyUserdata* body1 = CollisionBodyUserdataCheck(L,2);
    CollisionBodyUserdata* body2 = CollisionBodyUserdataCheck(L,3);
    lua_pushboolean(L,data->world->testOverlap(body1->body,body2->body));
	return 1;
}

static int TestOverlapBodyList(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    CollisionBodyUserdata* body1 = CollisionBodyUserdataCheck(L,2);
    NewTableOverlapCallback cb(L);
    cb.begin();
    data->world->testOverlap(body1->body,cb);
	return 1;
}

static int TestOverlapList(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    NewTableOverlapCallback cb(L);
    cb.begin();
    data->world->testOverlap(cb);
	return 1;
}

static int TestCollision2Bodies(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);
    WorldUserdata *data = WorldUserdataCheck(L, 1);
    CollisionBodyUserdata* body1 = CollisionBodyUserdataCheck(L,2);
    CollisionBodyUserdata* body2 = CollisionBodyUserdataCheck(L,3);
    NewTableCollisionCallback cb(L);
    cb.begin();
    data->world->testCollision(body1->body,body2->body,cb);
    int len = lua_objlen(L,-1);
    if(len == 0){
        lua_pop(L,1);
        lua_pushnil(L);
    }else if(len == 1){
        lua_rawgeti(L,-1,1);
        lua_remove(L,-2);
    }else{
        luaL_error(L,"Should be 1 or 0 collisions. Get:%d",len);
    }
	return 1;
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
        {"createCollisionBody",CreateCollisionBody},
        {"destroyCollisionBody",DestroyCollisionBody},
        {"createRigidBody",CreateRigidBody},
        {"destroyRigidBody",DestroyRigidBody},
        {"getDebugRenderer",GetDebugRenderer},
        {"raycast",Raycast},
        {"testOverlap2Bodies",TestOverlap2Bodies},
        {"testOverlapBodyList",TestOverlapBodyList},
        {"testOverlapList",TestOverlapList},
        {"testCollision2Bodies",TestCollision2Bodies},
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

const char * ContactPairEventTypeEnumToString(CollisionCallback::ContactPair::EventType name){
    switch(name){
        case CollisionCallback::ContactPair::EventType::ContactStart:
            return "ContactStart";
        case CollisionCallback::ContactPair::EventType::ContactStay:
            return "ContactStay";
        case CollisionCallback::ContactPair::EventType::ContactExit:
            return "ContactExit";
        default:
            assert(false);
    }
}


const char * OverlapPairEventTypeEnumToString(OverlapCallback::OverlapPair::EventType name){
    switch(name){
        case OverlapCallback::OverlapPair::EventType::OverlapStart:
            return "OverlapStart";
        case OverlapCallback::OverlapPair::EventType::OverlapStay:
            return "OverlapStay";
        case OverlapCallback::OverlapPair::EventType::OverlapExit:
            return "OverlapExit";
        default:
            assert(false);
    }
}

}