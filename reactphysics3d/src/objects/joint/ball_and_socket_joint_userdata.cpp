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

void BallAndSocketJointUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_JOINT_META_FUNCTIONS,
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