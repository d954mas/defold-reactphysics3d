#include "reactphysics3d/reactphysics3d.h"
#include "objects/joint/joint_userdata.h"
#include "objects/joint/slider_joint_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static SliderJoint* SliderJointCheck(lua_State* L, int index){
    JointUserdata *joint = JointUserdataCheck(L,index);
    if (joint->joint->getType() == JointType::SLIDERJOINT){
        return (SliderJoint*)joint->joint;
    }else{
        luaL_error(L, "joint not SliderJoint");
    }
}

static int IsLimitEnabled(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushboolean(L, joint->isLimitEnabled());
    return 1;
}


static int EnableLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    SliderJoint *joint = SliderJointCheck(L,1);
    joint->enableLimit(lua_toboolean(L,2));
    return 0;
}

static int IsMotorEnabled(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushboolean(L, joint->isMotorEnabled());
    return 1;
}


static int EnableMotor(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    SliderJoint *joint = SliderJointCheck(L,1);
    joint->enableMotor(lua_toboolean(L,2));
    return 0;
}

static int GetTranslation(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushnumber(L, joint->getTranslation());
    return 1;
}

static int GetMinTranslationLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushnumber(L, joint->getMinTranslationLimit());
    return 1;
}

static int SetMinTranslationLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    SliderJoint *joint = SliderJointCheck(L,1);
    double limit = luaL_checknumber(L,2);
    if(limit <= joint->getMaxTranslationLimit()){
        joint->setMinTranslationLimit(limit);
    }else{
        luaL_error(L,"limit must be lower then upper");
    }

    return 0;
}

static int GetMaxTranslationLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushnumber(L, joint->getMaxTranslationLimit());
    return 1;
}

static int SetMaxTranslationLimit(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    SliderJoint *joint = SliderJointCheck(L,1);
    double limit = luaL_checknumber(L,2);
    if(limit >= joint->getMinTranslationLimit()){
        joint->setMaxTranslationLimit(limit);
    }else{
        luaL_error(L,"limit must be upper then lower");
    }

    return 0;
}

static int GetMotorSpeed(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushnumber(L, joint->getMotorSpeed());
    return 1;
}

static int SetMotorSpeed(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    SliderJoint *joint = SliderJointCheck(L,1);
    joint->setMotorSpeed(luaL_checknumber(L,2));
    return 0;
}

static int GetMaxMotorForce(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushnumber(L, joint->getMaxMotorForce());
    return 1;
}

static int SetMaxMotorForce(lua_State* L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    SliderJoint *joint = SliderJointCheck(L,1);
    double force = luaL_checknumber(L,2);
    joint->setMaxMotorForce(force);
    return 0;
}

static int GetMotorForce(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    SliderJoint *joint = SliderJointCheck(L,1);
    lua_pushnumber(L, joint->getMotorForce(luaL_checknumber(L,2)));
    return 1;
}


void SliderJointUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_JOINT_META_FUNCTIONS,
            {"isLimitEnabled", IsLimitEnabled},
            {"isMotorEnabled", IsMotorEnabled},
            {"enableLimit", EnableLimit},
            {"enableMotor", EnableMotor},
            {"getTranslation", GetTranslation},
            {"getMinTranslationLimit", GetMinTranslationLimit},
            {"setMinTranslationLimit", SetMinTranslationLimit },
            {"getMaxTranslationLimit", GetMaxTranslationLimit},
            {"setMaxTranslationLimit", SetMaxTranslationLimit },
            {"getMotorSpeed", GetMotorSpeed},
            {"setMotorSpeed", SetMotorSpeed},
            {"getMaxMotorForce", GetMaxMotorForce},
            {"setMaxMotorForce", SetMaxMotorForce},
            {"getMotorForce", GetMotorForce},
            {0, 0}
        };
    luaL_newmetatable(L, META_SLIDER_JOINT);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}



}