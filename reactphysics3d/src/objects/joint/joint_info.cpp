#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/joint/joint_info.h"
#include "objects/collision_body_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "utils.h"
#include "static_hash.h"

using namespace reactphysics3d;

namespace rp3dDefold {
   // BallAndSocketJointInfo BallAndSocketJointInfoCheck(lua_State *L, int index);
   // JointInfo JointInfoCheck(lua_State *L, int index);

static JointType JointTypeStringToEnum(lua_State *L,const char* str){
    switch (hash_string(str)){
        case HASH_BALLSOCKETJOINT:
            return JointType::BALLSOCKETJOINT;
        case HASH_SLIDERJOINT:
            return JointType::SLIDERJOINT;
        case HASH_HINGEJOINT:
            return JointType::HINGEJOINT;
        case HASH_FIXEDJOINT:
            return JointType::FIXEDJOINT;
        default:
            luaL_error(L, "unknown JointType:%s", str);
            break;
    }
}
static const char * JointTypeEnumToString(JointType type){
    switch(type){
        case JointType::BALLSOCKETJOINT:
            return "BALLSOCKETJOINT";
        case JointType::SLIDERJOINT:
            return "SLIDERJOINT";
        case JointType::HINGEJOINT:
            return "HINGEJOINT";
        case JointType::FIXEDJOINT:
            return "FIXEDJOINT";
        default:
            assert(false);
    }
}

static JointsPositionCorrectionTechnique JointsPositionCorrectionTechniqueStringToEnum(lua_State *L,const char* str){
    switch (hash_string(str)){
        case HASH_BAUMGARTE_JOINTS:
            return JointsPositionCorrectionTechnique::BAUMGARTE_JOINTS;
        case HASH_NON_LINEAR_GAUSS_SEIDEL:
            return JointsPositionCorrectionTechnique::NON_LINEAR_GAUSS_SEIDEL;
        default:
            luaL_error(L, "unknown JointType:%s", str);
            break;
    }
}
static const char * JointsPositionCorrectionTechniqueEnumToString(JointsPositionCorrectionTechnique correction){
    switch(correction){
        case JointsPositionCorrectionTechnique::BAUMGARTE_JOINTS:
            return "BAUMGARTE_JOINTS";
        case JointsPositionCorrectionTechnique::NON_LINEAR_GAUSS_SEIDEL:
            return "NON_LINEAR_GAUSS_SEIDEL";
        default:
            assert(false);
    }
}



void JointInfoPush(lua_State *L,  JointInfo *info){
    lua_newtable(L);
    CollisionBodyPush(L,info->body1);
    lua_setfield(L, -2, "body1");
    CollisionBodyPush(L,info->body2);
    lua_setfield(L, -2, "body2");
    lua_pushstring(L,JointTypeEnumToString(info->type));
    lua_setfield(L, -2, "type");
    lua_pushstring(L,JointsPositionCorrectionTechniqueEnumToString(info->positionCorrectionTechnique));
    lua_setfield(L, -2, "positionCorrectionTechnique");
    lua_pushboolean(L,info->isCollisionEnabled);
    lua_setfield(L, -2, "isCollisionEnabled");


    switch(info->type){
        case JointType::BALLSOCKETJOINT:{
            const BallAndSocketJointInfo  *ballInfo =(BallAndSocketJointInfo*) info;
            lua_pushboolean(L,ballInfo->isUsingLocalSpaceAnchors);
            lua_setfield(L, -2, "isUsingLocalSpaceAnchors");
            pushRp3dVector3(L,ballInfo->anchorPointWorldSpace);
            lua_setfield(L, -2, "anchorPointWorldSpace");
            pushRp3dVector3(L,ballInfo->anchorPointBody1LocalSpace);
            lua_setfield(L, -2, "anchorPointBody1LocalSpace");
            pushRp3dVector3(L,ballInfo->anchorPointBody2LocalSpace);
            lua_setfield(L, -2, "anchorPointBody2LocalSpace");
            break;
        }
        case JointType::SLIDERJOINT:{
            break;
        }
        case JointType::HINGEJOINT:{
            break;
        }
        case JointType::FIXEDJOINT:
            break;
        default:
            assert(false);
    }
}

}