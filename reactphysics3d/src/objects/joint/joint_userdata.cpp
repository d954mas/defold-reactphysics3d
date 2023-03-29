#include "objects/base_userdata.h"
#include "static_hash.h"
#include "objects/joint/joint_info.h"
#include "objects/joint/joint_userdata.h"
#include "objects/joint/ball_and_socket_joint_userdata.h"
#include "objects/joint/hinge_joint_userdata.h"
#include "objects/collision_body_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "utils.h"

#define USERDATA_TYPE "rp3d::Joint"

using namespace reactphysics3d;

namespace rp3dDefold {

JointUserdata::JointUserdata(Joint* joint):BaseUserData(USERDATA_TYPE){
    this->joint = joint;
    this->obj = joint;
    joint->setUserData(this);

     switch(this->joint->getType()){
        case JointType::BALLSOCKETJOINT:
            this->metatable_name = META_BALL_AND_SOCKET_JOINT;
            break;
        case JointType::SLIDERJOINT:
            this->metatable_name = META_SLIDER_JOINT;
            assert(false);
            break;
        case JointType::HINGEJOINT:
            this->metatable_name = META_HINGE_JOINT;
            break;
        case JointType::FIXEDJOINT:
            this->metatable_name = META_FIXED_JOINT;
            assert(false);
            break;
        default:{
            assert(false);
        }
    }
}

JointUserdata::~JointUserdata() {

}

JointUserdata* JointUserdataCheck(lua_State* L, int index){
    JointUserdata *userdata = (JointUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
    return userdata;
}

int Joint_GetBody1(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    JointUserdata* joint = JointUserdataCheck(L,1);
    CollisionBodyPush(L, joint->joint->getBody1());
    return 1;
}

int Joint_GetBody2(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    JointUserdata* joint = JointUserdataCheck(L,1);
    CollisionBodyPush(L, joint->joint->getBody2());
    return 1;
}

int Joint_GetType(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    JointUserdata* joint = JointUserdataCheck(L,1);
    lua_pushstring(L,JointTypeEnumToString(joint->joint->getType()));
    return 1;
}

int Joint_GetReactionForce(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    JointUserdata* joint = JointUserdataCheck(L,1);
    double timestamp = luaL_checknumber(L,2);
    if(timestamp < MACHINE_EPSILON)  luaL_error(L, "timestamp < MACHINE_EPSILON");

    pushRp3dVector3(L,joint->joint->getReactionForce(timestamp));
    return 1;
}

int Joint_GetReactionTorque(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    JointUserdata* joint = JointUserdataCheck(L,1);
    double timestamp = luaL_checknumber(L,2);
    if(timestamp < MACHINE_EPSILON)  luaL_error(L, "timestamp < MACHINE_EPSILON");
    pushRp3dVector3(L,joint->joint->getReactionTorque(timestamp));
    return 1;
}

int Joint_IsCollisionEnabled(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    JointUserdata* joint = JointUserdataCheck(L,1);
    lua_pushboolean(L,joint->joint->isCollisionEnabled());
    return 1;
}

int Joint_GetEntityId(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    JointUserdata* joint = JointUserdataCheck(L,1);
    lua_pushnumber(L,joint->joint->getEntity().id);
    return 1;
}

int Joint_ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    JointUserdata* joint = JointUserdataCheck(L,1);
    push_std_string(L,joint->joint->to_string());
    return 1;
}

void JointUserdataInitMetaTable(lua_State *L){
    BallAndSocketJointUserdataInitMetaTable(L);
    HingeJointUserdataInitMetaTable(L);
}





void JointUserdataPush(lua_State *L, Joint* joint){
    if(joint->getUserData()!=NULL){
         JointUserdata* userdata =(JointUserdata*) joint->getUserData();
         userdata->Push(L);
    }else{
        JointUserdata* userdata = new JointUserdata(joint);
        userdata->Push(L);
    }
}

void JointUserdata::Destroy(lua_State *L){
    joint->setUserData(NULL);
    obj = NULL;
    joint = NULL;
    BaseUserData::Destroy(L);
}

}