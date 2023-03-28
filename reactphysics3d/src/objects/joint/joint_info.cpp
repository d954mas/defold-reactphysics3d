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
const char * JointTypeEnumToString(JointType type){
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
            luaL_error(L, "unknown JointsPositionCorrectionTechnique:%s", str);
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

static BallAndSocketJointInfo* BallAndSocketJointInfoCheck(lua_State *L, int index){
    //check Joint class
    lua_getfield(L, index, "type");
    JointType type = JointTypeStringToEnum(L,luaL_checkstring(L,-1));
    lua_pop(L,1);
    if(type != JointType::BALLSOCKETJOINT){
        luaL_error(L, "need BallAndSocketJointInfo get:%s", JointTypeEnumToString(type));
    }

    lua_getfield(L, index, "body1");
    RigidBody* body1 = (RigidBody*)CollisionBodyRigidUserdataCheck(L,-1)->body;
    lua_pop(L,1);

    lua_getfield(L, index, "body2");
    RigidBody* body2 = (RigidBody*)CollisionBodyRigidUserdataCheck(L,-1)->body;
    lua_pop(L,1);

    BallAndSocketJointInfo* info = new BallAndSocketJointInfo(body1,body2,Vector3(0,0,0));

    /* table is in the stack at index 't' */
    lua_pushnil(L);  /* first key */
    while (lua_next(L, -2) != 0) {
        /* uses 'key' (at index -2) and 'value' (at index -1) */
        // printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
        const char* key = lua_tostring(L, -2);
        switch (hash_string(key)) {
            case HASH_body1:break;
            case HASH_body2:break;
            case HASH_type:break;
            case HASH_positionCorrectionTechnique:
                info->positionCorrectionTechnique = JointsPositionCorrectionTechniqueStringToEnum(L,luaL_checkstring(L,-1));
                break;
            case HASH_isCollisionEnabled:
                info->isCollisionEnabled = lua_toboolean(L,-1);
                break;
            case HASH_isUsingLocalSpaceAnchors:
                info->isUsingLocalSpaceAnchors = lua_toboolean(L,-1);
                break;
            case HASH_anchorPointBody1LocalSpace:
                info->anchorPointBody1LocalSpace = checkRp3dVector3(L,-1);
                break;
            case HASH_anchorPointBody2LocalSpace:
                info->anchorPointBody2LocalSpace = checkRp3dVector3(L,-1);
                break;
            case HASH_anchorPointWorldSpace:
                info->anchorPointWorldSpace = checkRp3dVector3(L,-1);
                break;
           default:
               luaL_error(L, "unknown key:%s", key);
               break;
       }
      /* removes 'value'; keeps 'key' for next iteration */
      lua_pop(L, 1);
    }

    return info;

}

//YOU NEED DELETE JointInfo after use.
JointInfo* JointInfoCheck(lua_State *L, int index){
    if (!lua_istable(L, index))  luaL_error(L,"JointInfo should be table");

    //check Joint class
    lua_getfield(L, index, "type");
    JointType type = JointTypeStringToEnum(L,luaL_checkstring(L,-1));
    lua_pop(L,1);
    JointInfo *info = NULL;
    switch(type){
        case JointType::BALLSOCKETJOINT:
            info = BallAndSocketJointInfoCheck(L, index);
            break;
        case JointType::SLIDERJOINT:{
            assert(false);
            break;
        }
        case JointType::HINGEJOINT:{
            assert(false);
            break;
        }
        case JointType::FIXEDJOINT:
            assert(false);
            break;
        default:
            assert(false);
    }
    assert(info != NULL);
    return info;
}

}