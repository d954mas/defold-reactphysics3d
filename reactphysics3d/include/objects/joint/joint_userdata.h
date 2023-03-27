#ifndef joint_userdata_h
#define joint_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

#define META_BALL_AND_SOCKET_JOINT "rp3d::BallAndSocketJointClass"
#define META_HINGE_JOINT "rp3d::HingeJointClass"
#define META_SLIDER_JOINT "rp3d::SliderJointClass"
#define META_FIXED_JOINT "rp3d::FixedJointClass"


#define RP3D_JOINT_META_FUNCTIONS \
{"__tostring", Joint_ToString},\
{"getType", Joint_GetType}\


namespace rp3dDefold {

//use same for all Joint
//use diff meta tables
class JointUserdata : public BaseUserData {
    public:
        reactphysics3d::Joint* joint = NULL;
        JointUserdata(reactphysics3d::Joint* joint);
        ~JointUserdata();

        virtual void Destroy(lua_State *L);
};


   // int Joint_GetBody1(lua_State *L);
   // int Joint_GetBody2(lua_State *L);
    int Joint_GetType(lua_State *L);
   // int Joint_GetReactionForce(lua_State *L);
  //  int Joint_GetReactionTorque(lua_State *L);
  //  int Joint_IsCollisionEnabled(lua_State *L);
  //  int Joint_GetEntityId(lua_State *L);
    int Joint_ToString(lua_State *L);


    void JointUserdataInitMetaTable(lua_State *L);
    void JointUserdataPush(lua_State *L, reactphysics3d::Joint* joint);
    JointUserdata* JointUserdataCheck(lua_State *L, int index);
}
#endif