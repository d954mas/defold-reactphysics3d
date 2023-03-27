#ifndef joint_info_h
#define joint_info_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "reactphysics3d/reactphysics3d.h"


namespace rp3dDefold {
    void JointInfoPush(lua_State *L, reactphysics3d::JointInfo *);
    reactphysics3d::JointInfo* JointInfoCheck(lua_State *L, int index);
    const char * JointTypeEnumToString(reactphysics3d::JointType type);
}
#endif