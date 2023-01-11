#ifndef collision_shape_h
#define collision_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "reactphysics3d/reactphysics3d.h"
#include "objects/aabb.h"
#include "utils.h"

#define META_NAME_AABB "rp3d::AABBClass"



using namespace reactphysics3d;

namespace rp3dDefold {
    AABBLua::AABBLua(AABB aabb): aabb{aabb}{}
    AABBLua::AABBLua(){

    }

    AABBLua::~AABBLua() {
    }
    
    
int AABB_ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    AABBLua* aabb = AABBCheck(L,1);
    lua_pushfstring( L, "rp3d::AABB[%p]",(void *) &aabb->aabb);
    return 1;
}

int AABB_GC(lua_State *L){
    AABBLua **aabb = reinterpret_cast<AABBLua **>(lua_touserdata(L, 1));
    delete *aabb;
    return 0;
}

AABBLua* AABBCheck(lua_State* L, int index){
    AABBLua *shape = NULL;

    if(luaL_checkudata(L, index, META_NAME_AABB)){
        return  *static_cast<AABBLua**>(luaL_checkudata(L, index, META_NAME_AABB));
    }else{
        luaL_error(L, "Not aabb");
    }
}


void AABBPush(lua_State *L, AABB aabb){
    AABBLua *aabbLua = new AABBLua(aabb);
    *static_cast<AABBLua**>(lua_newuserdata(L, sizeof(AABBLua*))) = aabbLua;
    if(luaL_newmetatable(L, META_NAME_AABB)){
        static const luaL_Reg functions[] ={
            {"__tostring", AABB_ToString},
            {"__gc", AABB_GC},
            {0, 0}
        };
        luaL_register(L, NULL,functions);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
    }
    lua_setmetatable(L, -2);
}
}
#endif