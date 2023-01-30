#include "static_hash.h"
#include "objects/polyhedron_mesh_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::PolyhedronMesh"
#define USERDATA_TYPE "rp3d::PolyhedronMesh"



using namespace reactphysics3d;

namespace rp3dDefold {

PolyhedronMeshUserdata::PolyhedronMeshUserdata(): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
}

PolyhedronMeshUserdata::~PolyhedronMeshUserdata() {

}


PolyhedronMeshUserdata* PolyhedronMeshUserdataCheck(lua_State *L, int index) {
    PolyhedronMeshUserdata *userdata = (PolyhedronMeshUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}


static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    PolyhedronMeshUserdata *userdata = PolyhedronMeshUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::PolyhedronMesh[%p]",(void *) userdata->obj);
	return 1;
}

void PolyhedronMeshUserdataInitMetaTable(lua_State *L){
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


void PolyhedronMeshUserdata::Destroy(lua_State *L){
    mesh = NULL;
    BaseUserData::Destroy(L);
}


}