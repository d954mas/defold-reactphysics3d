#include "static_hash.h"
#include "objects/triangle_mesh_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::TriangleMesh"
#define USERDATA_TYPE "rp3d::TriangleMesh"

using namespace reactphysics3d;

namespace rp3dDefold {

TriangleMeshUserdata::TriangleMeshUserdata(): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
}

TriangleMeshUserdata::~TriangleMeshUserdata() {

}


TriangleMeshUserdata* TriangleMeshUserdataCheck(lua_State *L, int index) {
    TriangleMeshUserdata *userdata = (TriangleMeshUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    TriangleMeshUserdata *userdata = TriangleMeshUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::TriangleMesh[%p]",(void *) userdata->obj);
	return 1;
}


void TriangleMeshUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] = {
        {"__tostring", ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));
}


void TriangleMeshUserdata::Destroy(lua_State *L){
    triangleMesh = NULL;
    BaseUserData::Destroy(L);
}



}