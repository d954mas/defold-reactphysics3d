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

static int GetNbVertices(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->triangleVertexArray->getNbVertices());
	return 1;
}

static int GetNbTriangles(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->triangleVertexArray->getNbTriangles());
	return 1;
}
static int GetTriangleVertices(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    int idx = luaL_checknumber(L,2);
    if(idx<0 || idx>=userdata->triangleVertexArray->getNbTriangles()){
        luaL_error(L,"Bad idx:%d. Triangles:%d",idx,userdata->triangleVertexArray->getNbTriangles());
    }
    Vector3 result[3];
    userdata->triangleVertexArray->getTriangleVertices(0,result);
    lua_newtable(L);
    for(int i=0;i<3;++i){
        dmVMath::Vector3 dmV3(result[i].x,result[i].y,result[i].z);
        dmScript::PushVector3(L, dmV3);
        lua_rawseti(L, -2, i+1);
    }
	return 1;
}

static int GetTriangleVerticesNormals(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    int idx = luaL_checknumber(L,2);
    if(idx<0 || idx>=userdata->triangleVertexArray->getNbTriangles()){
        luaL_error(L,"Bad idx:%d. Triangles:%d",idx,userdata->triangleVertexArray->getNbTriangles());
    }
    Vector3 result[3];
    userdata->triangleVertexArray->getTriangleVerticesNormals(0,result);
    lua_newtable(L);
    for(int i=0;i<3;++i){
        dmVMath::Vector3 dmV3(result[i].x,result[i].y,result[i].z);
        dmScript::PushVector3(L, dmV3);
        lua_rawseti(L, -2, i+1);
    }
	return 1;
}

static int GetTriangleVerticesIndices(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    int idx = luaL_checknumber(L,2);
    if(idx<0 || idx>=userdata->triangleVertexArray->getNbTriangles()){
        luaL_error(L,"Bad idx:%d. Triangles:%d",idx,userdata->triangleVertexArray->getNbTriangles());
    }
    uint32 result[3];
    userdata->triangleVertexArray->getTriangleVerticesIndices(0,result);
    lua_newtable(L);
    for(int i=0;i<3;++i){
        lua_pushnumber(L,result[i]);
        lua_rawseti(L, -2, i+1);
    }
	return 1;
}


static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::TriangleVertexArray[%p]",(void *) userdata->obj);
	return 1;
}


void TriangleVertexArrayUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"getNbVertices", GetNbVertices},
        {"getNbTriangles", GetNbTriangles},
        {"getTriangleVertices", GetTriangleVertices},
        {"getTriangleVerticesNormals", GetTriangleVerticesNormals},
        {"getTriangleVerticesIndices", GetTriangleVerticesIndices},
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


void TriangleVertexArrayUserdata::Destroy(lua_State *L){
    triangleVertexArray = NULL;
    delete[] vertices;
    delete[] indices;
    delete[] normals;
    BaseUserData::Destroy(L);
}

TriangleVertexArrayUserdata* TriangleVertexArrayUserdataFromLua(lua_State *L){
    int top = lua_gettop(L);
    check_arg_count(L, 2,3);
    if (!lua_istable(L, 1)) luaL_error(L,"vertices is not table");
    if (!lua_istable(L, 2)) luaL_error(L,"indices is not table");

    int verticesSize = lua_objlen(L,1)+1; //start from 0
    int indicesSize = lua_objlen(L,2)+1; //start from 0
    if(verticesSize%3 !=0) luaL_error(L,"vertices bad number.Should be power of 3");
    if(indicesSize%3 !=0) luaL_error(L,"indices bad number.Should be power of 3");

    if(top == 3){
       if(!lua_istable(L, 3)) luaL_error(L,"normals should be nil or table");
       int normalsSize = lua_objlen(L,3)+1;
       if(normalsSize!=verticesSize) luaL_error(L,"normals count not same as vertices");
    }

    //parse vertices
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

    if(top ==3){
         //parse normals
        float *normals = new float[verticesSize];
        for(int i=0;i<verticesSize;i++){
            lua_pushnumber(L, i);
            lua_gettable(L, 3);
            if(!lua_isnumber(L, -1)){
                delete[] vertices;
                delete[] indices;
                delete[] normals;
                luaL_error(L,"normals[%d] is not number",i);
            }
            normals[i] = lua_tonumber(L,-1);
            lua_pop(L,1);
        }
        assert(top == lua_gettop(L));
        triangleVertexArray = new TriangleVertexArray(verticesSize/3, vertices,  3 * sizeof(float),
                                                                  normals, 3 * sizeof(float),
                                                                  indicesSize/3,
                                                                  indices,sizeof(int),
                                                                  TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                                  TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
                                                                  TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
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