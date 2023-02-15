#include "static_hash.h"
#include "objects/triangle_mesh_userdata.h"
#include "objects/triangle_vertex_array_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::TriangleMesh"
#define USERDATA_TYPE "rp3d::TriangleMesh"

using namespace reactphysics3d;

namespace rp3dDefold {

TriangleMeshUserdata::TriangleMeshUserdata(TriangleMesh *triangleMesh): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    this->obj = triangleMesh;
    this->mesh = triangleMesh;
}

TriangleMeshUserdata::~TriangleMeshUserdata() {

}


TriangleMeshUserdata* TriangleMeshUserdataCheck(lua_State *L, int index) {
    TriangleMeshUserdata *userdata = (TriangleMeshUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

static int AddSubpart(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    TriangleMeshUserdata *userdata = TriangleMeshUserdataCheck(L, 1);
    TriangleVertexArrayUserdata *userdataArray = TriangleVertexArrayUserdataCheck(L, 2);
    userdata->mesh->addSubpart(userdataArray->triangleVertexArray);
	return 0;
}

static int GetSubpart(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    TriangleMeshUserdata *userdata = TriangleMeshUserdataCheck(L, 1);
    int idx = luaL_checknumber(L,2);
    if(idx<0 || idx >=userdata->mesh->getNbSubparts()){
           luaL_error(L,"bad idx:%d. Size:%d",idx,userdata->mesh->getNbSubparts());
    }
    lua_pushnil(L);
	return 1;
}

static int GetNbSubparts(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    TriangleMeshUserdata *userdata = TriangleMeshUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->mesh->getNbSubparts());
	return 1;
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
        {"addSubpart", AddSubpart},
        {"getSubpart", GetSubpart},
        {"getNbSubparts", GetNbSubparts},
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
    mesh = NULL;
    BaseUserData::Destroy(L);
}



}