#include "reactphysics3d/reactphysics3d.h"
#include "objects/joint/joint_userdata.h"
#include "objects/joint/ball_and_socket_joint_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static HingeJoint* HingeJointCheck(lua_State* L, int index){
    JointUserdata *joint = JointUserdataCheck(L,index);
    if (joint->joint->getType() == JointType::HINGEJOINT){
        return (HingeJoint*)joint->joint;
    }else{
        luaL_error(L, "joint not HingeJoint");
    }
}

static int IsLimitEnabled(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushboolean(L, joint->isLimitEnabled());
    return 1;
}


static int EnableLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    HingeJoint *joint = HingeJointCheck(L,1);
    joint->enableLimit(lua_toboolean(L,2));
    return 0;
}

static int IsMotorEnabled(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushboolean(L, joint->isMotorEnabled());
    return 1;
}


static int EnableMotor(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    HingeJoint *joint = HingeJointCheck(L,1);
    joint->enableMotor(lua_toboolean(L,2));
    return 0;
}

static int GetMinAngleLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushnumber(L, joint->getMinAngleLimit());
    return 1;
}

static int SetMinAngleLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    HingeJoint *joint = HingeJointCheck(L,1);
    joint->setMinAngleLimit(luaL_checknumber(L,2));
    return 0;
}

static int GetMaxAngleLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushnumber(L, joint->getMaxAngleLimit());
    return 1;
}

static int SetMaxAngleLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    HingeJoint *joint = HingeJointCheck(L,1);
    joint->setMaxAngleLimit(luaL_checknumber(L,2));
    return 0;
}

static int GetMotorSpeed(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushnumber(L, joint->getMotorSpeed());
    return 1;
}

static int SetMotorSpeed(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    HingeJoint *joint = HingeJointCheck(L,1);
    joint->setMotorSpeed(luaL_checknumber(L,2));
    return 0;
}

static int GetMaxMotorTorque(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushnumber(L, joint->getMaxMotorTorque());
    return 1;
}

static int SetMaxMotorTorque(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    HingeJoint *joint = HingeJointCheck(L,1);
    joint->setMaxMotorTorque(luaL_checknumber(L,2));
    return 0;
}

static int GetMotorTorque(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushnumber(L, joint->getMotorTorque(luaL_checknumber(L,2)));
    return 1;
}

static int GetAngle(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    HingeJoint *joint = HingeJointCheck(L,1);
    lua_pushnumber(L, joint->getAngle());
    return 1;
}


void HingeJointUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_JOINT_META_FUNCTIONS,
            {"isLimitEnabled", IsLimitEnabled},
            {"isMotorEnabled", IsMotorEnabled},
            {"enableLimit", EnableLimit},
            {"enableMotor", EnableMotor},
            {"getMinAngleLimit", GetMinAngleLimit},
            {"setMinAngleLimit", SetMinAngleLimit},
            {"getMaxAngleLimit", GetMaxAngleLimit},
            {"setMaxAngleLimit", SetMaxAngleLimit},
            {"getMotorSpeed", GetMotorSpeed},
            {"setMotorSpeed", SetMotorSpeed},
            {"getMaxMotorTorque", GetMaxMotorTorque},
            {"setMaxMotorTorque", SetMaxMotorTorque},
            {"getMotorTorque", GetMotorTorque},
            {"getAngle", GetAngle},
            {0, 0}
        };
    luaL_newmetatable(L, META_BALL_AND_SOCKET_JOINT);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}



}