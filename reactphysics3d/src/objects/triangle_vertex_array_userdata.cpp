#include "static_hash.h"
#include "objects/triangle_vertex_array_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::TriangleVertexArray"
#define USERDATA_TYPE "rp3d::TriangleVertexArray"

static const dmhash_t HASH_POSITION  = dmHashString64("position");


using namespace reactphysics3d;

namespace rp3dDefold {

TriangleVertexArrayUserdata::TriangleVertexArrayUserdata(): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
}

TriangleVertexArrayUserdata::~TriangleVertexArrayUserdata() {

}


TriangleVertexArrayUserdata* TriangleVertexArrayUserdataCheck(lua_State *L, int index) {
    TriangleVertexArrayUserdata *userdata = (TriangleVertexArrayUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}


void TriangleVertexArrayUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));
}


void TriangleVertexArrayUserdata::Destroy(lua_State *L){
    triangleVertexArray = NULL;
    delete[] vertices;
    delete[] indices;
    delete[] normals;
    BaseUserData::Destroy(L);
}

TriangleVertexArrayUserdata* TriangleVertexArrayUserdataFromLua(PhysicsCommon *physicsCommon,lua_State *L){
    int top = lua_gettop(L);
    check_arg_count(L, 2,3);

    //parse vertices
    if (!lua_istable(L, 1)) luaL_error(L,"vertices is not table");
    int verticesSize = lua_objlen(L,1)+1; //start from 0
    float *vertices = new float[verticesSize];
    for(int i=0;i<verticesSize;i++){
        lua_pushnumber(L, i);
        lua_gettable(L, 1);
        if(!lua_isnumber(L, -1)){
            delete[] vertices;
            luaL_error(L,"vertices[%d] is not number",i);
        }
        vertices[i] = lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    assert(top == lua_gettop(L));

    //parse indices
    if (!lua_istable(L, 2)) {
        delete[] vertices;
        luaL_error(L,"indices is not table");
    }
    int indicesSize = lua_objlen(L,2)+1; //start from 0
    int *indices = new int[indicesSize];
    for(int i=0;i<indicesSize;i++){
        lua_pushnumber(L, i);
        lua_gettable(L, 2);
        if(!lua_isnumber(L, -1)){
            delete[] vertices;
            delete[] indices;
            luaL_error(L,"indices[%d] is not number",i);
        }
        indices[i] = lua_tonumber(L,-1);
        lua_pop(L,1);
    }
    assert(top == lua_gettop(L));

    TriangleVertexArray* triangleVertexArray = NULL;
    //parse normals
    if(top ==3){

    }else{
        triangleVertexArray = new TriangleVertexArray(verticesSize/3, vertices,  3 * sizeof(float),
                                                          indicesSize/3,
                                                           indices,sizeof(int),
                                                          TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                          TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
    }
    assert(top == lua_gettop(L));

   TriangleVertexArrayUserdata* result = new TriangleVertexArrayUserdata();
   result->obj = triangleVertexArray;
   result->triangleVertexArray = triangleVertexArray;

   result->vertices = vertices;
   result->indices = indices;
   result->normals = NULL;
   return result;
}



}