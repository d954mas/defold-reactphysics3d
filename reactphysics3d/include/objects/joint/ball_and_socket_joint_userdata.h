#ifndef ball_and_socket_joint_userdata_h
#define ball_and_socket_joint_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

#define RP3D_BALL_AND_SOCKET_META_FUNCTIONS


namespace rp3dDefold {

    void BallAndSocketJointUserdataInitMetaTable(lua_State *L);
}
#endif