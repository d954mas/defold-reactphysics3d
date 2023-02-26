#include "static_hash.h"
#include "objects/triangle_vertex_array_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::TriangleVertexArray"
#define USERDATA_TYPE "rp3d::TriangleVertexArray"

static const dmhash_t HASH_POSITION  = dmHashString64("position");
static const dmhash_t HASH_NORMAL  = dmHashString64("normal");


using namespace reactphysics3d;

namespace rp3dDefold {

TriangleVertexArrayUserdata::TriangleVertexArrayUserdata(TriangleVertexArray *triangleVertexArray): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    this->obj = triangleVertexArray;
    this->triangleVertexArray = triangleVertexArray;
    triangleVertexArray->setUserData(this);
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
    userdata->triangleVertexArray->getTriangleVertices(idx,result);
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
    userdata->triangleVertexArray->getTriangleVerticesNormals(idx,result);
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
    userdata->triangleVertexArray->getTriangleVerticesIndices(idx,result);
    lua_newtable(L);
    for(int i=0;i<3;++i){
        lua_pushnumber(L,result[i]);
        lua_rawseti(L, -2, i+1);
    }
	return 1;
}

static int GetVertex(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    int idx = luaL_checknumber(L,2);
    if(idx<0 || idx>=userdata->triangleVertexArray->getNbVertices()){
        luaL_error(L,"Bad idx:%d. Vertices:%d",idx,userdata->triangleVertexArray->getNbVertices());
    }
    Vector3 v3;
    userdata->triangleVertexArray->getVertex(idx,&v3);
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
	return 1;
}

static int GetNormal(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    TriangleVertexArrayUserdata *userdata = TriangleVertexArrayUserdataCheck(L, 1);
    int idx = luaL_checknumber(L,2);
    if(idx<0 || idx>=userdata->triangleVertexArray->getNbVertices()){
        luaL_error(L,"Bad idx:%d. Vertices:%d",idx,userdata->triangleVertexArray->getNbVertices());
    }
    Vector3 v3;
    userdata->triangleVertexArray->getNormal(idx,&v3);
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
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
        {"getVertex", GetVertex},
        {"getNormal", GetNormal},
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
    triangleVertexArray->setUserData(NULL);
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
                                                                  indices,3*sizeof(int),
                                                                  TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                                  TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
                                                                  TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
    }else{
        triangleVertexArray = new TriangleVertexArray(verticesSize/3, vertices,  3 * sizeof(float),
                                                          indicesSize/3,
                                                           indices,3*sizeof(int),
                                                          TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                          TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
    }
    assert(top == lua_gettop(L));

   TriangleVertexArrayUserdata* result = new TriangleVertexArrayUserdata(triangleVertexArray);

   result->vertices = vertices;
   result->indices = indices;
   result->normals = NULL;
   return result;
}

TriangleVertexArrayUserdata* TriangleVertexArrayUserdataFromBufferClone(PhysicsCommon *physicsCommon,lua_State *L){
    int top = lua_gettop(L);
    check_arg_count(L, 1);
    dmBuffer::HBuffer buffer = dmScript::CheckBufferUnpack(L,1);
    dmBuffer::Result validate = dmBuffer::ValidateBuffer(buffer);
    if(validate!=dmBuffer::RESULT_OK ) luaL_error(L,"buffer invalid");
    float* positions = 0x0;
    uint32_t pos_components = 0;
    uint32_t pos_stride = 0;
    uint32_t pos_count = 0;
    dmBuffer::Result r = dmBuffer::GetStream(buffer, HASH_POSITION, (void**)&positions, &pos_count, &pos_components, &pos_stride);
    if (r != dmBuffer::RESULT_OK) luaL_error(L,"buffer can't get position");

    float* normalsBuffer = 0x0;
    uint32_t normal_components = 0;
    uint32_t normal_stride = 0;
    uint32_t normal_count = 0;
    r = dmBuffer::GetStream(buffer, HASH_NORMAL, (void**)&normalsBuffer, &normal_count, &normal_components, &normal_stride);
    if (r != dmBuffer::RESULT_OK) luaL_error(L,"buffer can't get normal");

    if(normal_components!=pos_components) luaL_error(L,"positions and normal components not same");
    if(normal_count!=pos_count) luaL_error(L,"positions and normal count not same");
    if(pos_count%3 !=0) luaL_error(L,"bad number of vertices or triangles");


    float *vertices = new float[pos_count*pos_components];
    float *verticesIter = positions;
    float *normals = new float[pos_count*pos_components];
    float *normalsIter = normalsBuffer;

    int *indices = new int[pos_count];
    for (int i = 0; i < pos_count; ++i){
        vertices[i*3] = verticesIter[0];
        vertices[i*3+1] = verticesIter[1];
        vertices[i*3+2] = verticesIter[2];

        normals[i*3] = normalsIter[0];
        normals[i*3+1] = normalsIter[1];
        normals[i*3+2] = normalsIter[2];

        indices[i] = i;

        verticesIter += pos_stride;
        normalsIter += normal_stride;
       // dmLogInfo("vertex(%f %f %f)",vertices[i*3],vertices[i*3+1],vertices[i*3+2]);
     //   dmLogInfo("normal(%f %f %f)",normals[i*3],normals[i*3+1],normals[i*3+2]);
    }

    TriangleVertexArray *triangleVertexArray = new TriangleVertexArray(pos_count, vertices,  3 * sizeof(float),
                                                                  normals, 3 * sizeof(float),
                                                                  pos_count/3,
                                                                  indices,3*sizeof(int),
                                                                  TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
                                                                  TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
                                                                  TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

    TriangleVertexArrayUserdata* result = new TriangleVertexArrayUserdata(triangleVertexArray);

    result->vertices = vertices;
    result->indices = indices;
    result->normals = normals;
    return result;
}


void TriangleVertexArrayPush(lua_State *L, TriangleVertexArray* array){
    if(array->getUserData()!=NULL){
        TriangleVertexArrayUserdata* userdata =(TriangleVertexArrayUserdata*) array->getUserData();
        userdata->Push(L);
    }else{
        TriangleVertexArrayUserdata* userdata = new TriangleVertexArrayUserdata(array);
        userdata->Push(L);
    }
}



}