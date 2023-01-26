#ifndef world_userdata_h
#define world_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "static_hash.h"

using namespace reactphysics3d;

namespace rp3dDefold {

class LuaEventListener : public EventListener {
public:
    int fun_onContact_ref=LUA_REFNIL;
    int fun_onTrigger_ref=LUA_REFNIL;
    int defold_script_instance_ref=LUA_REFNIL;
    lua_State *L=NULL;
    bool error=false;
    bool needResetScriptInstance = false;
    const char* error_message=NULL;
    LuaEventListener(){};
    ~LuaEventListener(){};
    inline void InitFromTable(lua_State *L, int index){
       if (lua_istable(L, index)) {
           lua_pushvalue(L,index);
           /* table is in the stack at index 't' */
           lua_pushnil(L);  /* first key */
           while (lua_next(L, -2) != 0) {
               /* uses 'key' (at index -2) and 'value' (at index -1) */
              // printf("%s - %s\n",lua_tostring(L, -2),lua_tostring(L, -1));
               const char* key = lua_tostring(L, -2);
               switch (hash_string(key)) {
                   case HASH_onContact:{
                       if(lua_isfunction(L,-1)){
                           lua_pushvalue(L,-1);
                           fun_onContact_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                       }else{
                           luaL_error(L,"onContact must be function");
                       }
                       break;
                   }
                   case HASH_onTrigger:{
                       if(lua_isfunction(L,-1)){
                           lua_pushvalue(L,-1);
                           fun_onTrigger_ref = luaL_ref(L,LUA_REGISTRYINDEX);
                       }else{
                           luaL_error(L,"onTrigger must be function");
                       }
                       break;
                   }
                   default:
                       luaL_error(L, "unknown key:%s", key);
                       break;
               }
              /* removes 'value'; keeps 'key' for next iteration */
              lua_pop(L, 1);
           }
           if(fun_onContact_ref == LUA_REFNIL && fun_onTrigger_ref == LUA_REFNIL){
                dmLogWarning("No functions in eventListener");
           }
           lua_pop(L,1); //remove table

           dmScript::GetInstance(L);
           defold_script_instance_ref = dmScript::Ref(L, LUA_REGISTRYINDEX);

       }else{
        luaL_error(L,"eventListener should be table");
       }
   }

    inline void BeforeUpdate(lua_State *L){
        int top = lua_gettop(L);
        this->L = L;
        error = false;
        error_message = NULL;
        //save current instance in stack
        dmScript::GetInstance(L);
        if(defold_script_instance_ref != LUA_REFNIL){
            lua_rawgeti(L, LUA_REGISTRYINDEX, defold_script_instance_ref);
            dmScript::SetInstance(L);
            if (!dmScript::IsInstanceValid(L)){
                error = true;
                error_message = "EventListener script instance not valid";
            }
        }
        assert(lua_gettop(L) == top + 1);
    }

    inline void AfterUpdate(lua_State *L){
        dmScript::SetInstance(L);
    }

    inline void onContact(const CollisionCallback::CallbackData &callbackData){

    }

    inline void onTrigger(const OverlapCallback::CallbackData &callbackData){

    }

    inline void Destroy(lua_State *L){

    }
};


class WorldUserdata : public BaseUserData {
private:

public:
    PhysicsWorld *world=NULL;
    LuaEventListener *eventListener=NULL;

    WorldUserdata(PhysicsWorld* world);
	~WorldUserdata();

	virtual void Destroy(lua_State *L);
};

void WorldUserdataInitMetaTable(lua_State *L);
WorldUserdata* WorldUserdataCheck(lua_State *L, int index);

PhysicsWorld::WorldSettings WorldSettings_from_table(lua_State *L, int index);

const char * OverlapPairEventTypeEnumToString(OverlapCallback::OverlapPair::EventType name);
const char * ContactPairEventTypeEnumToString(CollisionCallback::ContactPair::EventType name);



}
#endif