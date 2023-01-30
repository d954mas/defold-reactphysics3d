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
    delete[] vertices;
    delete[] indices;
    delete[] faces;
    delete polygonVertexArray;
    BaseUserData::Destroy(L);
}

PolyhedronMeshUserdata* PolyhedronMeshUserdataFromLua(PhysicsCommon *physicsCommon,lua_State *L){
    int top = lua_gettop(L);
    check_arg_count(L, 3);

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
    //parse faces
    if (!lua_istable(L, 3)) {
        delete[] vertices;
        delete[] indices;
        luaL_error(L,"faces is not table");
    }
    int facesSize = lua_objlen(L,3)+1; //start from 0
    PolygonVertexArray::PolygonFace* faces = new PolygonVertexArray::PolygonFace[facesSize];
    PolygonVertexArray::PolygonFace* face = faces;
    for(int i=0;i<facesSize;i++){
        lua_pushnumber(L, i);
        lua_gettable(L, 3);
        if(!lua_istable(L, -1)){
            delete[] vertices;
            delete[] indices;
            delete[] faces;
            luaL_error(L,"faces[%d] is not table",i);
        }
        lua_getfield(L, -1, "indexBase");
        lua_getfield(L, -2, "nbVertices");
        //-1 nbVertices -2 indexBase -3 face table
        if(!lua_isnumber(L, -1)||!lua_isnumber(L, -2)){
            delete[] vertices;
            delete[] indices;
            delete[] faces;
            luaL_error(L,"faces[%d] bad table",i);
        }
        face->nbVertices = lua_tonumber(L,-1);
        face->indexBase = lua_tonumber(L,-2);
        lua_pop(L,3);
        face++;
    }
    assert(top == lua_gettop(L));

    PolygonVertexArray* polygonVertexArray = new PolygonVertexArray(
    verticesSize/3, vertices,  3 * sizeof(float),
    indices, sizeof(int),
    facesSize, faces,
    PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
    PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

   // Create the polyhedron mesh
   PolyhedronMesh* polyhedronMesh = physicsCommon->createPolyhedronMesh(polygonVertexArray);
   PolyhedronMeshUserdata* result = new PolyhedronMeshUserdata();
   result->obj = polyhedronMesh;
   result->mesh = polyhedronMesh;

   result->vertices = vertices;
   result->indices = indices;
   result->faces = faces;
   result->polygonVertexArray = polygonVertexArray;
   return result;
}


}