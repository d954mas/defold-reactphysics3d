#include "objects/collision_body_userdata.h"
#include "static_hash.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/collider_userdata.h"
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
        {"getCollider",	GetCollider},
        {"getNbColliders",GetNbColliders},
        {"removeCollider",RemoveCollider},
        {"updateMassPropertiesFromColliders",RigidBodyUpdateMassPropertiesFromColliders},
        {"getType",RigidBodyGetType},
        {"setType",RigidBodySetType},
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
        {"getCollider",	GetCollider},
        {"getNbColliders",GetNbColliders},
        {"removeCollider",RemoveCollider},
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
            collider->setUserData(NULL);
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