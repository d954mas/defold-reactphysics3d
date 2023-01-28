#include <string>
#include <queue>

#include "utils.h"
#include "static_hash.h"
#include "objects/collider_userdata.h"
#include "objects/collision_body_userdata.h"

namespace rp3dDefold {
	void check_arg_count(lua_State *L, int count_exact) {
		int count = lua_gettop(L);
		if (count != count_exact) {
			luaL_error(L, "This function requires %d arguments. Got %d.", count_exact, count);
		}
	}

	void check_arg_count(lua_State *L, int count_from, int count_to) {
		int count = lua_gettop(L);
		if (count < count_from || count > count_to) {
			luaL_error(L, "This function requires from %d to %d arguments. Got %d.", count_from, count_to, count);
		}
	}

	void push_std_string(lua_State *L, std::string str){
        lua_pushlstring(L, str.c_str(), str.length());
	}



    void pushRp3dTransform(lua_State *L, reactphysics3d::Transform transform){
        dmVMath::Vector3 dmPosition;
        dmVMath::Quat dmQuat;

       const reactphysics3d::Vector3& position = transform.getPosition();
       const reactphysics3d::Quaternion& quat = transform.getOrientation();

        dmPosition.setX(position.x);
        dmPosition.setY(position.y);
        dmPosition.setZ(position.z);

        dmQuat.setX(quat.x);
        dmQuat.setY(quat.y);
        dmQuat.setZ(quat.z);
        dmQuat.setW(quat.w);

        lua_newtable(L);
            dmScript::PushVector3(L, dmPosition);
            lua_setfield(L, -2, "position");
            dmScript::PushQuat(L,dmQuat);
            lua_setfield(L, -2, "quat");

    }

    void pushRp3dRaycastInfo(lua_State *L, const reactphysics3d::RaycastInfo &info){
        dmVMath::Vector3 dmWorldPoint;
        dmVMath::Vector3 dmWorldNormal;

        dmWorldPoint.setX(info.worldPoint.x);
        dmWorldPoint.setY(info.worldPoint.y);
        dmWorldPoint.setZ(info.worldPoint.z);

        dmWorldNormal.setX(info.worldNormal.x);
        dmWorldNormal.setY(info.worldNormal.y);
        dmWorldNormal.setZ(info.worldNormal.z);


        lua_newtable(L);
            dmScript::PushVector3(L, dmWorldPoint);
            lua_setfield(L, -2, "worldPoint");
            dmScript::PushVector3(L, dmWorldNormal);
            lua_setfield(L, -2, "worldNormal");
            lua_pushnumber(L,info.hitFraction);
            lua_setfield(L, -2, "hitFraction");
            lua_pushnumber(L,info.meshSubpart);
            lua_setfield(L, -2, "meshSubpart");
            lua_pushnumber(L,info.triangleIndex);
            lua_setfield(L, -2, "triangleIndex");
            CollisionBodyPush(L,info.body);
            lua_setfield(L, -2, "body");
            ColliderPush(L,info.collider);
            lua_setfield(L, -2, "collider");
    }

    void pushRp3dMaterial(lua_State *L, reactphysics3d::Material &material){
        lua_newtable(L);
            lua_pushnumber(L,material.getBounciness());
            lua_setfield(L, -2, "bounciness");
            lua_pushnumber(L, material.getFrictionCoefficient());
            lua_setfield(L, -2, "frictionCoefficient");
            lua_pushnumber(L,material.getMassDensity());
            lua_setfield(L, -2, "massDensity");
    }

    reactphysics3d::Transform checkRp3dTransform(lua_State *L, int index){
            if (lua_istable(L, index)) {
                reactphysics3d::Vector3 position;
                bool positionExist = false;
                reactphysics3d::Quaternion quat;
                bool quatExist = false;

                lua_pushvalue(L,index);
                lua_pushnil(L);  /* first key */
                while (lua_next(L, -2) != 0) {
                    /* uses 'key' (at index -2) and 'value' (at index -1) */
                    //printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
                    const char* key = lua_tostring(L, -2);
                    switch (hash_string(key)){
                        case HASH_position:{
                            dmVMath::Vector3* value = dmScript::CheckVector3(L, -1);
                            position.x = value->getX();
                            position.y = value->getY();
                            position.z = value->getZ();
                            positionExist = true;
                            break;
                        }
                       case HASH_quat:{
                            dmVMath::Quat* value =  dmScript::CheckQuat(L, -1);
                            quat.x = value->getX();
                            quat.y = value->getY();
                            quat.z = value->getZ();
                            quat.w = value->getW();
                            quatExist = true;
                            break;
                       }
                       default:
                           luaL_error(L, "unknown key:%s", key);
                           break;
                   }
                  /* removes 'value'; keeps 'key' for next iteration */
                  lua_pop(L, 1);
                }
                lua_pop(L,1);
                if(!positionExist){
                    luaL_error(L,"transform need position");
                }
                if(!quatExist){
                    luaL_error(L,"transform need quat");
                }
                return reactphysics3d::Transform(position,quat);
            }else{
                luaL_error(L,"transform should be table");
            }
    	}

    reactphysics3d::Ray CheckRay(lua_State *L, int index){
        if (lua_istable(L, index)) {
            reactphysics3d::Vector3 point1;
            bool point1Exist = false;
            reactphysics3d::Vector3 point2;
            bool point2Exist = false;
            float maxFrac = 1;
            
            lua_pushvalue(L,index);
            lua_pushnil(L);  /* first key */
            while (lua_next(L, -2) != 0) {
                /* uses 'key' (at index -2) and 'value' (at index -1) */
                //printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
                const char* key = lua_tostring(L, -2);
                switch (hash_string(key)){
                    case HASH_point1:{
                        dmVMath::Vector3* value = dmScript::CheckVector3(L, -1);
                        point1.x = value->getX();
                        point1.y = value->getY();
                        point1.z = value->getZ();
                        point1Exist = true;
                        break;
                    }
                   case HASH_point2:{
                        dmVMath::Vector3* value = dmScript::CheckVector3(L, -1);
                        point2.x = value->getX();
                        point2.y = value->getY();
                        point2.z = value->getZ();
                        point2Exist = true;
                        break;
                   }
                   case HASH_maxFraction:
                        maxFrac = luaL_checknumber(L,-1);
                        break;
                   default:
                       luaL_error(L, "unknown key:%s", key);
                       break;
               }
              /* removes 'value'; keeps 'key' for next iteration */
              lua_pop(L, 1);
            }
            lua_pop(L,1);
            if(!point1Exist){
                luaL_error(L,"ray need point1");
            }
            if(!point2Exist){
                luaL_error(L,"ray need point2");
            }
            return reactphysics3d::Ray(point1,point2,maxFrac);
        }else{
            luaL_error(L,"ray should be table");
        }
    }

    void checkRp3dMaterial(lua_State *L, int index, reactphysics3d::Material &material){
            if (lua_istable(L, index)) {
                bool bouncinessExist = false;
                bool frictionCoefficientExist = false;
                bool massDensityExist = false;

                lua_pushvalue(L,index);
                lua_pushnil(L);  /* first key */
                while (lua_next(L, -2) != 0) {
                    /* uses 'key' (at index -2) and 'value' (at index -1) */
                    //printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
                    const char* key = lua_tostring(L, -2);
                    switch (hash_string(key)){
                        case HASH_bounciness:{
                            material.setBounciness(luaL_checknumber(L,-1));
                            bouncinessExist = true;
                            break;
                        }
                       case HASH_frictionCoefficient:{
                            material.setFrictionCoefficient(luaL_checknumber(L,-1));
                            frictionCoefficientExist = true;
                            break;
                        }
                       case HASH_massDensity:{
                            material.setMassDensity(luaL_checknumber(L,-1));
                            massDensityExist = true;
                            break;
                       }
                       default:
                           luaL_error(L, "unknown key:%s", key);
                           break;
                   }
                  /* removes 'value'; keeps 'key' for next iteration */
                  lua_pop(L, 1);
                }
                lua_pop(L,1);
                if(!bouncinessExist){
                    luaL_error(L,"material need bounciness");
                }
                if(!frictionCoefficientExist){
                    luaL_error(L,"material need frictionCoefficient");
                }
                if(!massDensityExist){
                    luaL_error(L,"material need massDensity");
                }
                return;
            }else{
                luaL_error(L,"material should be table");
            }
        }

        void pushRp3dHalfEdgeStructureFace(lua_State *L,const reactphysics3d::HalfEdgeStructure::Face &face){
            lua_newtable(L);
            lua_pushnumber(L,face.edgeIndex);
            lua_setfield(L, -2, "edgeIndex");
            lua_newtable(L);
                const Array<uint32>& faceVertices = face.faceVertices;
                for(int i=0;i<faceVertices.size();i++){
                    lua_pushnumber(L,faceVertices[i]);
                    lua_rawseti(L, -2, i+1);
                }
            lua_setfield(L, -2, "faceVertices");
        }
}