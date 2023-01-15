#include "static_hash.h"
#include "objects/debug_renderer_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::DebugRenderer"
#define USERDATA_TYPE "rp3d::DebugRenderer"


using namespace reactphysics3d;

namespace rp3dDefold {

DebugRendererUserdata::DebugRendererUserdata(DebugRenderer* renderer): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    this->renderer = renderer;
    this->obj = renderer;
    this->renderer->setUserData(this);
}

DebugRendererUserdata::~DebugRendererUserdata() {

}


DebugRendererUserdata* DebugRendererUserdataCheck(lua_State *L, int index) {
    DebugRendererUserdata *userdata = (DebugRendererUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::DebugRenderer[%p]",(void *) userdata->renderer);
	return 1;
}

void DebugRendererUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"__tostring",ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));
}


void DebugRendererUserdata::Destroy(lua_State *L){
    renderer->setUserData(NULL);
    renderer = NULL;
    BaseUserData::Destroy(L);
}

void DebugRendererPush(lua_State *L, DebugRenderer* renderer){
    if(renderer->getUserData()!=NULL){
        DebugRendererUserdata* userdata =(DebugRendererUserdata*) renderer->getUserData();
        userdata->Push(L);
    }else{
        DebugRendererUserdata* userdata = new DebugRendererUserdata(renderer);
        userdata->Push(L);
    }
}

}