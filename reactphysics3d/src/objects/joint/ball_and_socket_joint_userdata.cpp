#include "reactphysics3d/reactphysics3d.h"
#include "objects/joint/joint_userdata.h"
#include "objects/joint/ball_and_socket_joint_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static BallAndSocketJoint* BallAndSocketJointCheck(lua_State* L, int index){
    JointUserdata *joint = JointUserdataCheck(L,index);
    if (joint->joint->getType() == JointType::BALLSOCKETJOINT){
        return (BallAndSocketJoint*)joint->joint;
    }else{
        luaL_error(L, "joint not BallAndSocketJoint");
    }
}

static int EnableConeLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    BallAndSocketJoint *joint = BallAndSocketJointCheck(L,1);
    joint->enableConeLimit(lua_toboolean(L,2));
    return 0;
}
static int IsConeLimitEnabled(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    BallAndSocketJoint *joint = BallAndSocketJointCheck(L,1);
    lua_pushboolean(L, joint->isConeLimitEnabled());
    return 1;
}

static int SetConeLimitHalfAngle(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    BallAndSocketJoint *joint = BallAndSocketJointCheck(L,1);
    joint->setConeLimitHalfAngle(luaL_checknumber(L,2));
    return 0;
}

static int GetConeLimitHalfAngle(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    BallAndSocketJoint *joint = BallAndSocketJointCheck(L,1);
    lua_pushnumber(L, joint->getConeLimitHalfAngle());
    return 1;
}

static int GetConeHalfAngle(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    BallAndSocketJoint *joint = BallAndSocketJointCheck(L,1);
    lua_pushnumber(L, joint->getConeHalfAngle());
    return 1;
}

void BallAndSocketJointUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_JOINT_META_FUNCTIONS,
            {"enableConeLimit", EnableConeLimit},
            {"isConeLimitEnabled", IsConeLimitEnabled},
            {"setConeLimitHalfAngle", SetConeLimitHalfAngle},
            {"getConeLimitHalfAngle", GetConeLimitHalfAngle},
            {"getConeHalfAngle", GetConeHalfAngle},
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