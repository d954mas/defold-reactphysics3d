#include "objects/base_userdata.h"
#include "static_hash.h"
#include "objects/joint/joint_userdata.h"
#include "objects/joint/ball_and_socket_joint_userdata.h"
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
            assert(false);
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

int Joint_ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    JointUserdata* joint = JointUserdataCheck(L,1);
    push_std_string(L,joint->joint->to_string());
    return 1;
}

void JointUserdataInitMetaTable(lua_State *L){
    BallAndSocketJointUserdataInitMetaTable(L);
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