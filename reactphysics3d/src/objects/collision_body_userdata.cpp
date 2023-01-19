#include "objects/collision_body_userdata.h"
#include "static_hash.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/collider_userdata.h"
#include "objects/aabb.h"
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
    body->setUserData(userdata);
}

CollisionBodyUserdata::CollisionBodyUserdata(CollisionBody* body): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    isRigidBody = body->isRigidBody();
    if(isRigidBody){
         this->metatable_name = META_NAME_RIGID;
    }
    init(this,body);
}



CollisionBodyUserdata::~CollisionBodyUserdata() {
}


CollisionBodyUserdata* CollisionBodyUserdataCheck(lua_State *L, int index) {
    CollisionBodyUserdata *userdata = (CollisionBodyUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

RigidBody* CollisionBodyUserdata::GetRigidBodyOrError(lua_State *L){
    if(!isRigidBody){
        luaL_error(L,"Need RigidBody.Get CollisionBody");
    }else{
        return (RigidBody*)body;
    }
}

static int GetEntityId(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->body->getEntity().id);
	return 1;
}

static int IsRigidBody(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushboolean(L,userdata->isRigidBody);
	return 1;
}

static int IsActive(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushboolean(L,userdata->body->isActive());
	return 1;
}
static int SetIsActive(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->body->setIsActive(lua_toboolean(L,2));
	return 0;
}

static int GetUserData(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_rawgeti(L,LUA_REGISTRYINDEX,userdata->user_data_ref);
	return 1;
}
static int SetUserData(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
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

static int GetTransform(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    pushRp3dTransform(L,userdata->body->getTransform());
	return 1;
}
static int SetTransform(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->body->setTransform(checkRp3dTransform(L,2));
	return 0;
}

static int AddCollider(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    CollisionShapeUserdata* shapeLua = CollisionShapeCheck(L,2);
    Transform transform = checkRp3dTransform(L,3);
    //dmLogInfo("shape[%p]",(void *) shapeLua->shape);
    Collider* collider = userdata->body->addCollider(shapeLua->shape,transform);
  //  dmLogInfo("Collider shape[%p]",(void *) collider->getCollisionShape());
    ColliderPush(L,collider);
	return 1;
}

static int GetNbColliders(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->body->getNbColliders());
	return 1;
}

static int GetCollider(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    int idx = luaL_checknumber(L,2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    if(idx<0 || idx >= userdata->body->getNbColliders() ){
        luaL_error(L,"bad idx:%d. Size:%d",idx,userdata->body->getNbColliders());
    }
    Collider *collider = userdata->body->getCollider(idx);
    ColliderPush(L,collider);
	return 1;
}

static int RemoveCollider(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    ColliderUserdata *colliderUserdata = ColliderUserdataCheck(L,2);
    Collider* collider = colliderUserdata->collider;
    colliderUserdata->Destroy(L);
    delete colliderUserdata;
    body->body->removeCollider(collider);

	return 0;
}

static int TestPointInside(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmPoint = dmScript::CheckVector3(L, 2);
    Vector3 point(dmPoint->getX(),dmPoint->getY(),dmPoint->getZ());
    lua_pushboolean(L,body->body->testPointInside(point));
	return 1;
}
static int TestAABBOverlap(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    AABBLua *aabb = AABBCheck(L,2);
    lua_pushboolean(L,body->body->testAABBOverlap(aabb->aabb));
	return 1;
}

static int GetAABB(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    AABBPush(L,body->body->getAABB());
	return 1;
}

static int GetWorldPoint(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    Vector3 result = body->body->getWorldPoint(v3);

    dmVMath::Vector3 dmResult(result.x,result.y,result.z);
    dmScript::PushVector3(L, dmResult);
	return 1;
}

static int GetLocalPoint(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    Vector3 result = body->body->getLocalPoint(v3);

    dmVMath::Vector3 dmResult(result.x,result.y,result.z);
    dmScript::PushVector3(L, dmResult);
	return 1;
}

static int GetWorldVector(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    Vector3 result = body->body->getWorldVector(v3);

    dmVMath::Vector3 dmResult(result.x,result.y,result.z);
    dmScript::PushVector3(L, dmResult);
	return 1;
}

static int GetLocalVector(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    Vector3 result = body->body->getLocalVector(v3);

    dmVMath::Vector3 dmResult(result.x,result.y,result.z);
    dmScript::PushVector3(L, dmResult);
	return 1;
}

static int Raycast(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    CollisionBodyUserdata *body = CollisionBodyUserdataCheck(L, 1);
    Ray ray = CheckRay(L,2);
    RaycastInfo info;
    bool result =  body->body->raycast(ray,info);

    if(result){
         pushRp3dRaycastInfo(L,info);
    }else{
        lua_pushnil(L);
    }
    return 1;
}


static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    if(userdata->isRigidBody){
         lua_pushfstring( L, "rp3d::RigidBody[%p]",(void *) userdata->body);
    }else{
         lua_pushfstring( L, "rp3d::CollisionBody[%p]",(void *) userdata->body);
    }
	return 1;
}

static int RigidBodyUpdateLocalCenterOfMassFromColliders(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->updateLocalCenterOfMassFromColliders();
    return 0;
}

static int RigidBodyUpdateLocalInertiaTensorFromColliders(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->updateLocalInertiaTensorFromColliders();
    return 0;
}

static int RigidBodyUpdateMassFromColliders(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->updateMassFromColliders();
    return 0;
}

static int RigidBodyUpdateMassPropertiesFromColliders(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->updateMassPropertiesFromColliders();
    return 0;
}

static int RigidBodyGetType(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushstring(L,BodyTypeEnumToString(userdata->GetRigidBodyOrError(L)->getType()));
    return 1;
}

static int RigidBodySetType(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->setType(BodyTypeStringToEnum(L,luaL_checkstring(L,2)));
    return 0;
}

static int RigidBodyGetMass(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->GetRigidBodyOrError(L)->getMass());
    return 1;
}

static int RigidBodySetMass(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->setMass(luaL_checknumber(L,2));
    return 0;
}

static int RigidBodySetLinearVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->setLinearVelocity(v3);
    return 0;
}

static int RigidBodyGetLinearVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    Vector3 v3 = userdata->GetRigidBodyOrError(L)->getLinearVelocity();
    dmVMath::Vector3 result(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, result);
    return 1;
}

static int RigidBodySetAngularVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->setAngularVelocity(v3);
    return 0;
}

static int RigidBodyGetAngularVelocity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    Vector3 v3 = userdata->GetRigidBodyOrError(L)->getAngularVelocity();
    dmVMath::Vector3 result(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, result);
    return 1;
}

static int RigidBodySetLocalInertiaTensor(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->setLocalInertiaTensor(v3);
    return 0;
}

static int RigidBodyGetLocalInertiaTensor(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    Vector3 v3 = userdata->GetRigidBodyOrError(L)->getLocalInertiaTensor();
    dmVMath::Vector3 result(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, result);
    return 1;
}

static int RigidBodySetLocalCenterOfMass(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->setLocalCenterOfMass(v3);
    return 0;
}

static int RigidBodyGetLocalCenterOfMass(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    Vector3 v3 = userdata->GetRigidBodyOrError(L)->getLocalCenterOfMass();
    dmVMath::Vector3 result(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, result);
    return 1;
}

static int RigidBodyIsGravityEnabled(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushboolean(L,userdata->GetRigidBodyOrError(L)->isGravityEnabled());
	return 1;
}

static int RigidBodyEnableGravity(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->enableGravity(lua_toboolean(L,2));
	return 0;
}

static int RigidBodyIsSleeping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushboolean(L,userdata->GetRigidBodyOrError(L)->isSleeping());
	return 1;
}

static int RigidBodySetIsSleeping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->setIsSleeping(lua_toboolean(L,2));
	return 0;
}

static int RigidBodyGetLinearDamping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->GetRigidBodyOrError(L)->getLinearDamping());
    return 1;
}

static int RigidBodySetLinearDamping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->setLinearDamping(luaL_checknumber(L,2));
    return 0;
}

static int RigidBodyGetAngularDamping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->GetRigidBodyOrError(L)->getAngularDamping());
    return 1;
}

static int RigidBodySetAngularDamping(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    userdata->GetRigidBodyOrError(L)->setAngularDamping(luaL_checknumber(L,2));
    return 0;
}


static int RigidBodySetLinearLockAxisFactor(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->setLinearLockAxisFactor(v3);
    return 0;
}

static int RigidBodyGetLinearLockAxisFactor(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    Vector3 v3 = userdata->GetRigidBodyOrError(L)->getLinearLockAxisFactor();
    dmVMath::Vector3 result(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, result);
    return 1;
}

static int RigidBodySetAngularLockAxisFactor(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->setAngularLockAxisFactor(v3);
    return 0;
}

static int RigidBodyApplyLocalForceAtCenterOfMass(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->applyLocalForceAtCenterOfMass(v3);
    return 0;
}

static int RigidBodyApplyWorldForceAtCenterOfMass(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);

    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    userdata->GetRigidBodyOrError(L)->applyWorldForceAtCenterOfMass(v3);
    return 0;
}

static int RigidBodyApplyLocalForceAtLocalPosition(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmForce = dmScript::CheckVector3(L, 2);
    Vector3 force(dmForce->getX(),dmForce->getY(),dmForce->getZ());

    dmVMath::Vector3* dmPos = dmScript::CheckVector3(L, 3);
    Vector3 pos(dmPos->getX(),dmPos->getY(),dmPos->getZ());

    userdata->GetRigidBodyOrError(L)->applyLocalForceAtLocalPosition(force,pos);
    return 0;
}

static int RigidBodyApplyWorldForceAtLocalPosition(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmForce = dmScript::CheckVector3(L, 2);
    Vector3 force(dmForce->getX(),dmForce->getY(),dmForce->getZ());

    dmVMath::Vector3* dmPos = dmScript::CheckVector3(L, 3);
    Vector3 pos(dmPos->getX(),dmPos->getY(),dmPos->getZ());

    userdata->GetRigidBodyOrError(L)->applyWorldForceAtLocalPosition(force,pos);
    return 0;
}

static int RigidBodyApplyLocalForceAtWorldPosition(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmForce = dmScript::CheckVector3(L, 2);
    Vector3 force(dmForce->getX(),dmForce->getY(),dmForce->getZ());

    dmVMath::Vector3* dmPos = dmScript::CheckVector3(L, 3);
    Vector3 pos(dmPos->getX(),dmPos->getY(),dmPos->getZ());

    userdata->GetRigidBodyOrError(L)->applyLocalForceAtWorldPosition(force,pos);
    return 0;
}

static int RigidBodyApplyWorldForceAtWorldPosition(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    dmVMath::Vector3* dmForce = dmScript::CheckVector3(L, 2);
    Vector3 force(dmForce->getX(),dmForce->getY(),dmForce->getZ());

    dmVMath::Vector3* dmPos = dmScript::CheckVector3(L, 3);
    Vector3 pos(dmPos->getX(),dmPos->getY(),dmPos->getZ());

    userdata->GetRigidBodyOrError(L)->applyWorldForceAtWorldPosition(force,pos);
    return 0;
}

static int RigidBodyGetAngularLockAxisFactor(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionBodyUserdata *userdata = CollisionBodyUserdataCheck(L, 1);
    Vector3 v3 = userdata->GetRigidBodyOrError(L)->getAngularLockAxisFactor();
    dmVMath::Vector3 result(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, result);
    return 1;
}



const char * BodyTypeEnumToString(BodyType name){
    switch(name){
        case BodyType::STATIC:
            return "STATIC";
        case BodyType::KINEMATIC:
            return "KINEMATIC";
        case BodyType::DYNAMIC:
            return "DYNAMIC";
        default:
            assert(false);
    }
}

BodyType BodyTypeStringToEnum(lua_State *L,const char* str){
    switch (hash_string(str)){
        case HASH_STATIC:
            return BodyType::STATIC;
        case HASH_KINEMATIC:
          return BodyType::KINEMATIC;
        case HASH_DYNAMIC:
            return BodyType::DYNAMIC;
        default:
            luaL_error(L, "unknown BodyType:%s", str);
            break;
    }
}

static void CollisionBodyUserdataRigidInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"getEntityId",GetEntityId},
        {"isRigidBody",IsRigidBody},
        {"isActive",IsActive},
        {"setIsActive",SetIsActive},
        {"getUserData",GetUserData},
        {"setUserData",SetUserData},
        {"getTransform",GetTransform},
        {"setTransform",SetTransform},
        {"addCollider",AddCollider},
        {"removeCollider",RemoveCollider},
        {"testPointInside",TestPointInside},
        {"raycast",Raycast},
        {"getCollider",	GetCollider},
        {"getNbColliders",GetNbColliders},
        {"removeCollider",RemoveCollider},
        {"testAABBOverlap",TestAABBOverlap},
        {"getAABB",GetAABB},
        {"getWorldPoint",GetWorldPoint},
        {"getWorldVector",GetWorldVector},
        {"getLocalPoint",GetLocalPoint},
        {"getLocalVector",GetLocalVector},
        {"updateLocalCenterOfMassFromColliders",RigidBodyUpdateLocalCenterOfMassFromColliders},
        {"updateLocalInertiaTensorFromColliders",RigidBodyUpdateLocalInertiaTensorFromColliders},
        {"updateMassFromColliders",RigidBodyUpdateMassFromColliders},
        {"updateMassPropertiesFromColliders",RigidBodyUpdateMassPropertiesFromColliders},
        {"getType",RigidBodyGetType},
        {"setType",RigidBodySetType},
        {"getMass",RigidBodyGetMass},
        {"setMass",RigidBodySetMass},
        {"setLinearVelocity",RigidBodySetLinearVelocity},
        {"getLinearVelocity",RigidBodyGetLinearVelocity},
        {"getAngularVelocity",RigidBodyGetAngularVelocity},
        {"setAngularVelocity",RigidBodySetAngularVelocity},
        {"getLocalInertiaTensor",RigidBodyGetLocalInertiaTensor},
        {"setLocalInertiaTensor",RigidBodySetLocalInertiaTensor},
        {"getLocalCenterOfMass",RigidBodyGetLocalCenterOfMass},
        {"setLocalCenterOfMass",RigidBodySetLocalCenterOfMass},
        {"isGravityEnabled",RigidBodyIsGravityEnabled },
        {"enableGravity",RigidBodyEnableGravity},
        {"setIsSleeping",RigidBodySetIsSleeping },
        {"isSleeping",RigidBodyIsSleeping },
        {"getLinearDamping",RigidBodyGetLinearDamping },
        {"setLinearDamping",RigidBodySetLinearDamping },
        {"getAngularDamping",RigidBodyGetAngularDamping },
        {"setAngularDamping",RigidBodySetAngularDamping },
        {"getLinearLockAxisFactor",RigidBodyGetLinearLockAxisFactor },
        {"setLinearLockAxisFactor",RigidBodySetLinearLockAxisFactor },
        {"getAngularLockAxisFactor",RigidBodyGetAngularLockAxisFactor },
        {"setAngularLockAxisFactor",RigidBodySetAngularLockAxisFactor },
        {"applyLocalForceAtCenterOfMass",RigidBodyApplyLocalForceAtCenterOfMass },
        {"applyWorldForceAtCenterOfMass",RigidBodyApplyWorldForceAtCenterOfMass },
        {"applyLocalForceAtLocalPosition",RigidBodyApplyLocalForceAtLocalPosition },
        {"applyWorldForceAtLocalPosition",RigidBodyApplyWorldForceAtLocalPosition },
        {"applyLocalForceAtWorldPosition",RigidBodyApplyLocalForceAtWorldPosition },
        {"applyWorldForceAtWorldPosition",RigidBodyApplyWorldForceAtWorldPosition },
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

void CollisionBodyUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"getEntityId",GetEntityId},
        {"isRigidBody",IsRigidBody},
        {"isActive",IsActive},
        {"setIsActive",SetIsActive},
        {"getUserData",GetUserData},
        {"setUserData",SetUserData},
        {"getTransform",GetTransform},
        {"setTransform",SetTransform},
        {"addCollider",AddCollider},
        {"removeCollider ",RemoveCollider},
        {"testPointInside",TestPointInside},
        {"raycast",Raycast},
        {"getCollider",	GetCollider},
        {"getNbColliders",GetNbColliders},
        {"removeCollider",RemoveCollider},
        {"testAABBOverlap",TestAABBOverlap},
        {"getAABB",GetAABB},
        {"getWorldPoint",GetWorldPoint},
        {"getWorldVector",GetWorldVector},
        {"getLocalPoint",GetLocalPoint},
        {"getLocalVector",GetLocalVector},
        {"__tostring",ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));

    CollisionBodyUserdataRigidInitMetaTable(L);
}





void CollisionBodyUserdata::Destroy(lua_State *L){
    for(int i =0;i<body->getNbColliders();i++){
        Collider* collider = body->getCollider(i);
        ColliderUserdata* userdata = (ColliderUserdata*)collider->getUserData();
        if(userdata!=NULL){
            userdata->Destroy(L);
            delete userdata;
        }
    }
    body->setUserData(NULL);
    body = NULL;
    luaL_unref(L, LUA_REGISTRYINDEX, user_data_ref);
    user_data_ref = LUA_REFNIL;
    BaseUserData::Destroy(L);
}

void CollisionBodyPush(lua_State *L, CollisionBody *body){

    if(body->getUserData()!=NULL){
        CollisionBodyUserdata* userdata =(CollisionBodyUserdata*) body->getUserData();
         userdata->Push(L);
    }else{
        CollisionBodyUserdata* userdata = new CollisionBodyUserdata(body);
        userdata->Push(L);
    }
}


}