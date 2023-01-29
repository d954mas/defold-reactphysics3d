#define EXTENSION_NAME reactphysics3dDefold
#define LIB_NAME "reactphysics3d"
#define MODULE_NAME "rp3d"

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "utils.h"
#include "objects/collider_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/sphere_shape_userdata.h"
#include "objects/shape/capsule_shape_userdata.h"
#include "objects/debug_renderer_userdata.h"
#include "objects/base_userdata.h"
#include "objects/world_userdata.h"
#include "objects/collision_body_userdata.h"



using namespace reactphysics3d;
using namespace rp3dDefold;

static PhysicsCommon physicsCommon;


static int CreatePhysicsWorldLua(lua_State* L){
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
static int DestroyPhysicsWorldLua(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    WorldUserdata *data = WorldUserdataCheck(L,1);
    //free all
    //destroy collisionBodyUserdata
    for(int i=0;i<data->world->getNbCollisionBodies();++i){
        CollisionBody* body = data->world->getCollisionBody(i);
        CollisionBodyUserdata* userdata = (CollisionBodyUserdata*) body->getUserData();
        if(userdata!=NULL){
            userdata->Destroy(L);
            delete userdata;
        }
    }
    //destroy rigidBodyUserdata
    for(int i=0;i<data->world->getNbRigidBodies();++i){
        CollisionBody* body = data->world->getRigidBody(i);
        CollisionBodyUserdata* userdata = (CollisionBodyUserdata*) body->getUserData();
        if(userdata!=NULL){
            userdata->Destroy(L);
            delete userdata;
        }
    }
    //destroy joints


    DebugRendererUserdata* drUserdata = (DebugRendererUserdata*)data->world->getDebugRenderer().getUserData();
    if(drUserdata!=NULL){
        drUserdata->Destroy(L);
        delete drUserdata;
    }


    physicsCommon.destroyPhysicsWorld(data->world);
    data->Destroy(L);
    delete data;
    return 0;
}

static int CreateBoxShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    dmVMath::Vector3* v3 = dmScript::CheckVector3(L, 1);
    Vector3 v3rp3d(v3->getX(),v3->getY(),v3->getZ());
    BoxShape * shape = physicsCommon.createBoxShape(v3rp3d);
    CollisionShapePush(L,shape);
    return 1;
}

static int DestroyBoxShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionShapeUserdata * shapeUserdata = BoxShapeCheckUserdata(L,1);
    BoxShape* shape = static_cast<BoxShape*>(shapeUserdata->shape);
    shapeUserdata->Destroy(L);
    delete shapeUserdata;
    physicsCommon.destroyBoxShape(shape);
    return 0;
}

static int CreateSphereShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SphereShape * shape = physicsCommon.createSphereShape(luaL_checknumber(L,1));
    CollisionShapePush(L,shape);
    return 1;
}

static int DestroySphereShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionShapeUserdata * shapeUserdata = SphereShapeCheckUserdata(L,1);
    SphereShape* shape = static_cast<SphereShape*>(shapeUserdata->shape);
    shapeUserdata->Destroy(L);
    delete shapeUserdata;
    physicsCommon.destroySphereShape(shape);
    return 0;
}

static int CreateCapsuleShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CapsuleShape * shape = physicsCommon.createCapsuleShape(luaL_checknumber(L,1),luaL_checknumber(L,2));
    CollisionShapePush(L,shape);
    return 1;
}

static int DestroyCapsuleShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionShapeUserdata * shapeUserdata = CapsuleShapeCheckUserdata(L,1);
    CapsuleShape* shape = static_cast<CapsuleShape*>(shapeUserdata->shape);
    shapeUserdata->Destroy(L);
    delete shapeUserdata;
    physicsCommon.destroyCapsuleShape(shape);
    return 0;
}


// Functions exposed to Lua
static const luaL_reg Module_methods[] ={
	 {"createPhysicsWorld", CreatePhysicsWorldLua},
	 {"destroyPhysicsWorld", DestroyPhysicsWorldLua},
	 {"createBoxShape", CreateBoxShape},
	 {"destroyBoxShape", DestroyBoxShape},
	 {"createSphereShape", CreateSphereShape},
	 {"destroySphereShape", DestroySphereShape},
	 {"createCapsuleShape", CreateCapsuleShape},
	 {"destroyCapsuleShape", DestroyCapsuleShape},
	{0, 0}
};

static void LuaInit(lua_State* L){
	int top = lua_gettop(L);
	// Register lua names
	luaL_register(L, MODULE_NAME, Module_methods);

	 lua_newtable(L);
        lua_pushstring(L, "BAUMGARTE_CONTACTS");
        lua_setfield(L, -2, "BAUMGARTE_CONTACTS");
        lua_pushstring(L, "SPLIT_IMPULSES");
        lua_setfield(L, -2, "SPLIT_IMPULSES");
     lua_setfield(L, -2, "ContactsPositionCorrectionTechnique");

    lua_newtable(L);
        lua_pushstring(L, "TRIANGLE");
        lua_setfield(L, -2, "TRIANGLE");
        lua_pushstring(L, "SPHERE");
        lua_setfield(L, -2, "SPHERE");
        lua_pushstring(L, "CAPSULE");
        lua_setfield(L, -2, "CAPSULE");
        lua_pushstring(L, "BOX");
        lua_setfield(L, -2, "BOX");
        lua_pushstring(L, "CONVEX_MESH");
        lua_setfield(L, -2, "CONVEX_MESH");
        lua_pushstring(L, "TRIANGLE_MESH");
        lua_setfield(L, -2, "TRIANGLE_MESH");
        lua_pushstring(L, "HEIGHTFIELD");
        lua_setfield(L, -2, "HEIGHTFIELD");
     lua_setfield(L, -2, "CollisionShapeName");

    lua_newtable(L);
        lua_pushstring(L, "SPHERE");
        lua_setfield(L, -2, "SPHERE");
        lua_pushstring(L, "CAPSULE");
        lua_setfield(L, -2, "CAPSULE");
        lua_pushstring(L, "CONVEX_POLYHEDRON");
        lua_setfield(L, -2, "CONVEX_POLYHEDRON");
        lua_pushstring(L, "CONCAVE_SHAPE");
        lua_setfield(L, -2, "CONCAVE_SHAPE");
    lua_setfield(L, -2, "CollisionShapeType");

    lua_newtable(L);
        lua_pushstring(L, "STATIC");
        lua_setfield(L, -2, "STATIC");
        lua_pushstring(L, "KINEMATIC");
        lua_setfield(L, -2, "KINEMATIC");
        lua_pushstring(L, "DYNAMIC");
        lua_setfield(L, -2, "DYNAMIC");
    lua_setfield(L, -2, "BodyType");

    lua_newtable(L);
        lua_newtable(L);
            lua_pushstring(L, "COLLIDER_AABB");
            lua_setfield(L, -2, "COLLIDER_AABB");
            lua_pushstring(L, "COLLIDER_BROADPHASE_AABB");
            lua_setfield(L, -2, "COLLIDER_BROADPHASE_AABB");
            lua_pushstring(L, "COLLISION_SHAPE");
            lua_setfield(L, -2, "COLLISION_SHAPE");
            lua_pushstring(L, "CONTACT_POINT");
            lua_setfield(L, -2, "CONTACT_POINT");
            lua_pushstring(L, "CONTACT_NORMAL");
            lua_setfield(L, -2, "CONTACT_NORMAL");
        lua_setfield(L, -2, "DebugItem");
    lua_setfield(L, -2, "DebugRenderer");

    lua_newtable(L);
        lua_newtable(L);
            lua_pushstring(L, "OverlapStart");
            lua_setfield(L, -2, "OverlapStart");
            lua_pushstring(L, "OverlapStay");
            lua_setfield(L, -2, "OverlapStay");
            lua_pushstring(L, "OverlapExit");
            lua_setfield(L, -2, "OverlapExit");
        lua_setfield(L, -2, "EventType");
    lua_setfield(L, -2, "OverlapPair");

    lua_newtable(L);
        lua_newtable(L);
            lua_pushstring(L, "ContactStart");
            lua_setfield(L, -2, "ContactStart");
            lua_pushstring(L, "ContactStay");
            lua_setfield(L, -2, "ContactStay");
            lua_pushstring(L, "ContactExit");
            lua_setfield(L, -2, "ContactExit");
        lua_setfield(L, -2, "EventType");
    lua_setfield(L, -2, "ContactPair");

	lua_pop(L, 1);
	assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}
static dmExtension::Result InitializeMyExtension(dmExtension::Params* params){
    WorldUserdataInitMetaTable(params->m_L);
    CollisionBodyUserdataInitMetaTable(params->m_L);
    CollisionShapeUserdataInitMetaTable(params->m_L);
    ColliderUserdataInitMetaTable(params->m_L);
    DebugRendererUserdataInitMetaTable(params->m_L);
	LuaInit(params->m_L);
	printf("Registered %s Extension\n", MODULE_NAME);
	return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params){return dmExtension::RESULT_OK;}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeMyExtension, AppFinalizeMyExtension, InitializeMyExtension, 0, 0, FinalizeMyExtension)