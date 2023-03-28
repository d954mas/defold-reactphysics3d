#define EXTENSION_NAME reactphysics3dDefold
#define LIB_NAME "reactphysics3d"
#define MODULE_NAME "rp3d"

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "utils.h"
#include "objects/collider_userdata.h"
#include "objects/aabb.h"
#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/sphere_shape_userdata.h"
#include "objects/shape/capsule_shape_userdata.h"
#include "objects/shape/convex_mesh_shape_userdata.h"
#include "objects/shape/concave_mesh_shape_userdata.h"
#include "objects/shape/height_field_shape_userdata.h"
#include "objects/debug_renderer_userdata.h"
#include "objects/base_userdata.h"
#include "objects/world_userdata.h"
#include "objects/collision_body_userdata.h"
#include "objects/polyhedron_mesh_userdata.h"
#include "objects/triangle_vertex_array_userdata.h"
#include "objects/triangle_mesh_userdata.h"
#include "objects/joint/joint_info.h"
#include "objects/joint/joint_userdata.h"


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
        RigidBody* body = data->world->getRigidBody(i);
        CollisionBodyUserdata* userdata = (CollisionBodyUserdata*) body->getUserData();
        if(userdata!=NULL){
            userdata->Destroy(L);
            delete userdata;
        }
        data->world->rigidBodyRemoveJointsUserdata(L,body);
    }

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

static int CreatePolyhedronMesh(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataFromLua(&physicsCommon,L);
    mesh->Push(L);
    return 1;
}

static int CreatePolyhedronMeshFromMeshVerticesCopy(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataFromBufferClone(&physicsCommon,L);
    mesh->Push(L);
    return 1;
}

static int CreateTriangleVertexArrayFromMeshVerticesCopy(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    TriangleVertexArrayUserdata *array = TriangleVertexArrayUserdataFromBufferClone(&physicsCommon,L);
    array->Push(L);
    return 1;
}


static int DestroyPolyhedronMesh(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    PolyhedronMeshUserdata * userdata = PolyhedronMeshUserdataCheck(L,1);
    PolyhedronMesh* mesh = userdata->mesh;
    userdata->Destroy(L);
    delete userdata;
    physicsCommon.destroyPolyhedronMesh(mesh);
    return 0;
}

static int CreateConvexMeshShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1,2);
    PolyhedronMeshUserdata * mesh = PolyhedronMeshUserdataCheck(L,1);
    Vector3 scalingV3(1,1,1);
    if(lua_gettop(L) == 2){
        dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
        scalingV3.x = dmV3->getX();
        scalingV3.y = dmV3->getY();
        scalingV3.z = dmV3->getZ();
    }
    ConvexMeshShape * shape = physicsCommon.createConvexMeshShape(mesh->mesh,scalingV3);
    CollisionShapePush(L,shape);
    return 1;
}

static int DestroyConvexMeshShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionShapeUserdata * shapeUserdata = ConvexMeshShapeCheckUserdata(L,1);
    ConvexMeshShape* shape = static_cast<ConvexMeshShape*>(shapeUserdata->shape);
    shapeUserdata->Destroy(L);
    delete shapeUserdata;
    physicsCommon.destroyConvexMeshShape(shape);
    return 0;
}

static int CreateConcaveMeshShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1,2);
    TriangleMeshUserdata * mesh = TriangleMeshUserdataCheck(L,1);
    Vector3 scalingV3(1,1,1);
    if(lua_gettop(L) == 2){
        dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
        scalingV3.x = dmV3->getX();
        scalingV3.y = dmV3->getY();
        scalingV3.z = dmV3->getZ();
    }
    ConcaveMeshShape * shape = physicsCommon.createConcaveMeshShape(mesh->mesh,scalingV3);
    CollisionShapePush(L,shape);
    return 1;
}

static int DestroyConcaveMeshShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionShapeUserdata * shapeUserdata = ConcaveMeshShapeCheckUserdata(L,1);
    ConcaveMeshShape* shape = static_cast<ConcaveMeshShape*>(shapeUserdata->shape);
    shapeUserdata->Destroy(L);
    delete shapeUserdata;
    physicsCommon.destroyConcaveMeshShape(shape);
    return 0;
}


static int CreateTriangleVertexArray(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2,3);
    TriangleVertexArrayUserdata *array = TriangleVertexArrayUserdataFromLua(L);
    array->Push(L);
    return 1;
}

static int DestroyTriangleVertexArray(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    TriangleVertexArrayUserdata * array = TriangleVertexArrayUserdataCheck(L,1);
    array->Destroy(L);
    delete array;
    return 0;
}

static int CreateTriangleMesh(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 0);
    TriangleMesh * mesh = physicsCommon.createTriangleMesh();
    TriangleMeshUserdata *data = new TriangleMeshUserdata(mesh);
    data->Push(L);
    return 1;
}

static int DestroyTriangleMesh(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    TriangleMeshUserdata * data = TriangleMeshUserdataCheck(L,1);
    TriangleMesh * mesh = data->mesh;
    data->Destroy(L);
    delete data;
    physicsCommon.destroyTriangleMesh(mesh);
    return 0;
}



static int CreateHeightFieldShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 6,9);
    int count = lua_gettop(L);
    int nbGridColumns = luaL_checknumber(L,1);
    if(nbGridColumns<=0) luaL_error(L, "nbGridColumns should be positive");
    int nbGridRows = luaL_checknumber(L,2);
    if(nbGridRows<=0) luaL_error(L, "nbGridRows should be positive");
    decimal minHeight = luaL_checknumber(L,3);
    decimal maxHeight = luaL_checknumber(L,4);

    if (!lua_istable(L, 5)) luaL_error(L,"data should be table");
    int dataSize = luaL_getn(L, 5)+1;
    if(dataSize!= nbGridRows*nbGridColumns) luaL_error(L,"bad data size.Need:%d. Get:%d",nbGridRows*nbGridColumns,dataSize);

    HeightFieldShape::HeightDataType dataType =  HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE;
    const char * str = luaL_checkstring(L,6);
    switch (hash_string(str)){
        case HASH_HEIGHT_FLOAT_TYPE:
            dataType = HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE;
            break;
        case HASH_HEIGHT_DOUBLE_TYPE:
            dataType = HeightFieldShape::HeightDataType::HEIGHT_DOUBLE_TYPE;
            break;
        case HASH_HEIGHT_INT_TYPE:
            dataType = HeightFieldShape::HeightDataType::HEIGHT_INT_TYPE;
            break;
        default:
            luaL_error(L, "unknown HeightDataType:%s", str);
            break;
    }

    int upAxis = 1;
    if(count>=7){
        upAxis = luaL_checknumber(L,7);
        if(upAxis<0 || upAxis>2)  luaL_error(L, "bad upAxis:%d", upAxis);
    }

    decimal integerHeightScale = 1;
    if(count>=8){
        integerHeightScale = luaL_checknumber(L,8);
    }
    Vector3 scaling(1,1,1);
    if(count>=9){
        dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 9);
        scaling = Vector3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    }
    void* data;
    switch(dataType){
        case HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE:{
            float *dataFloat = new float[dataSize];
            for(int i=0;i<dataSize;++i){
                lua_rawgeti(L,5,i);
                dataFloat[i] = luaL_checknumber(L,-1);
                lua_pop(L,1);
            }
            data = dataFloat;
            break;
        }
        case HeightFieldShape::HeightDataType::HEIGHT_DOUBLE_TYPE:{
            double *dataDouble = new double[dataSize];
            for(int i=0;i<dataSize;++i){
                lua_rawgeti(L,5,i+1);
                dataDouble[i] = luaL_checknumber(L,-1);
                lua_pop(L,1);
            }
            data = dataDouble;
            break;
        }
        case HeightFieldShape::HeightDataType::HEIGHT_INT_TYPE:{
            int *dataInt = new int[dataSize];
            for(int i=0;i<dataSize;++i){
                lua_rawgeti(L,5,i+1);
                dataInt[i] = luaL_checknumber(L,-1);
                lua_pop(L,1);
            }
            data = dataInt;
            break;
        }
        default:
            assert(false);
    }
    HeightFieldShape * shape = physicsCommon.createHeightFieldShape(nbGridColumns,nbGridRows,
        minHeight,maxHeight,data,dataType,upAxis,integerHeightScale,scaling);


    CollisionShapeUserdata* userdata = CollisionShapePush(L,shape);
    userdata->heightData = data;

    return 1;
}

static int DestroyHeightFieldShape(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionShapeUserdata * shapeUserdata = HeightFieldShapeCheckUserdata(L,1);
    HeightFieldShape* shape = static_cast<HeightFieldShape*>(shapeUserdata->shape);
    shapeUserdata->Destroy(L);
    delete shapeUserdata;
    physicsCommon.destroyHeightFieldShape(shape);
    return 0;
}

static int CreateAABB(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    dmVMath::Vector3* dmVMin= dmScript::CheckVector3(L, 1);
    dmVMath::Vector3* dmVMax= dmScript::CheckVector3(L, 2);

    Vector3 vMin(dmVMin->getX(),dmVMin->getY(),dmVMin->getZ());
    Vector3 vMax(dmVMax->getX(),dmVMax->getY(),dmVMax->getZ());
    AABB aabb(vMin,vMax);
    AABBPush(L,aabb);
    return 1;
}
static int CreateBallAndSocketJointInfoLocalSpace(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 4);

    CollisionBodyUserdata* body1 = CollisionBodyRigidUserdataCheck(L,1);
    CollisionBodyUserdata* body2 = CollisionBodyRigidUserdataCheck(L,2);
    Vector3 anchorPointBody1LocalSpace = checkRp3dVector3(L,3);
    Vector3 anchorPointBody2LocalSpace = checkRp3dVector3(L,4);

    BallAndSocketJointInfo jointInfo = BallAndSocketJointInfo((RigidBody*)body1->body,(RigidBody*)body2->body,
        anchorPointBody1LocalSpace,anchorPointBody2LocalSpace) ;

    JointInfoPush(L,&jointInfo);
    return 1;
}

static int CreateBallAndSocketJointInfoWorldSpace(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);

    CollisionBodyUserdata* body1 = CollisionBodyRigidUserdataCheck(L,1);
    CollisionBodyUserdata* body2 = CollisionBodyRigidUserdataCheck(L,2);
    Vector3 initAnchorPointWorldSpace = checkRp3dVector3(L,3);

    BallAndSocketJointInfo jointInfo = BallAndSocketJointInfo((RigidBody*)body1->body,(RigidBody*)body2->body,
       initAnchorPointWorldSpace);

    JointInfoPush(L,&jointInfo);
    return 1;
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
    {"createPolyhedronMesh", CreatePolyhedronMesh},
    {"createPolyhedronMeshFromMeshVerticesCopy", CreatePolyhedronMeshFromMeshVerticesCopy},
    {"destroyPolyhedronMesh", DestroyPolyhedronMesh},
    {"createConvexMeshShape", CreateConvexMeshShape},
    {"destroyConvexMeshShape", DestroyConvexMeshShape},
    {"createConcaveMeshShape", CreateConcaveMeshShape},
    {"destroyConcaveMeshShape", DestroyConcaveMeshShape},
    {"createTriangleVertexArray", CreateTriangleVertexArray},
    {"createTriangleVertexArrayFromMeshVerticesCopy", CreateTriangleVertexArrayFromMeshVerticesCopy},
    {"destroyTriangleVertexArray", DestroyTriangleVertexArray},
    {"createTriangleMesh", CreateTriangleMesh},
    {"destroyTriangleMesh", DestroyTriangleMesh},
    {"createHeightFieldShape", CreateHeightFieldShape},
    {"destroyHeightFieldShape", DestroyHeightFieldShape},
    {"createAABB", CreateAABB},
    {"createBallAndSocketJointInfoLocalSpace", CreateBallAndSocketJointInfoLocalSpace},
    {"createBallAndSocketJointInfoWorldSpace", CreateBallAndSocketJointInfoWorldSpace},
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
        lua_pushstring(L, "FRONT");
        lua_setfield(L, -2, "FRONT");
        lua_pushstring(L, "BACK");
        lua_setfield(L, -2, "BACK");
        lua_pushstring(L, "FRONT_AND_BACK");
        lua_setfield(L, -2, "FRONT_AND_BACK");
    lua_setfield(L, -2, "TriangleRaycastSide");

    lua_newtable(L);
        lua_pushstring(L, "HEIGHT_FLOAT_TYPE");
        lua_setfield(L, -2, "HEIGHT_FLOAT_TYPE");
        lua_pushstring(L, "HEIGHT_DOUBLE_TYPE");
        lua_setfield(L, -2, "HEIGHT_DOUBLE_TYPE");
        lua_pushstring(L, "HEIGHT_INT_TYPE");
        lua_setfield(L, -2, "HEIGHT_INT_TYPE");
    lua_setfield(L, -2, "HeightDataType");

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

    lua_newtable(L);
        lua_pushstring(L, "BALLSOCKETJOINT");
        lua_setfield(L, -2, "BALLSOCKETJOINT");
        lua_pushstring(L, "SLIDERJOINT");
        lua_setfield(L, -2, "SLIDERJOINT");
        lua_pushstring(L, "HINGEJOINT");
        lua_setfield(L, -2, "HINGEJOINT");
        lua_pushstring(L, "FIXEDJOINT");
        lua_setfield(L, -2, "FIXEDJOINT");
    lua_setfield(L, -2, "JointType");

     lua_newtable(L);
        lua_pushstring(L, "BAUMGARTE_JOINTS");
        lua_setfield(L, -2, "BAUMGARTE_JOINTS");
        lua_pushstring(L, "NON_LINEAR_GAUSS_SEIDEL");
        lua_setfield(L, -2, "NON_LINEAR_GAUSS_SEIDEL");
    lua_setfield(L, -2, "JointsPositionCorrectionTechnique");


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
    PolyhedronMeshUserdataInitMetaTable(params->m_L);
    TriangleVertexArrayUserdataInitMetaTable(params->m_L);
    TriangleMeshUserdataInitMetaTable(params->m_L);
    JointUserdataInitMetaTable(params->m_L);
	LuaInit(params->m_L);
	printf("Registered %s Extension\n", MODULE_NAME);
	return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params){return dmExtension::RESULT_OK;}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeMyExtension, AppFinalizeMyExtension, InitializeMyExtension, 0, 0, FinalizeMyExtension)