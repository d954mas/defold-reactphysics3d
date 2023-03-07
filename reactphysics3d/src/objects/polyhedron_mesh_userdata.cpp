#include "static_hash.h"
#include "objects/polyhedron_mesh_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::PolyhedronMesh"
#define USERDATA_TYPE "rp3d::PolyhedronMesh"

static const dmhash_t HASH_POSITION  = dmHashString64("position");


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


static int GetNbVertices(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataCheck(L, 1);
    lua_pushnumber(L,mesh->mesh->getNbVertices());
    return 1;
}

static int GetVertex(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataCheck(L, 1);
    int vertexIndex = luaL_checknumber(L,2);
    if(vertexIndex<0 || vertexIndex>=mesh->mesh->getNbVertices()){
        luaL_error(L,"bad vertexIndex:%d",vertexIndex);
    }
    Vector3 v3 = mesh->mesh->getVertex(vertexIndex);
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}

static int GetNbFaces(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataCheck(L, 1);
    lua_pushnumber(L,mesh->mesh->getNbFaces());
    return 1;
}

static int GetFaceNormal(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataCheck(L, 1);
    int faceIndex = luaL_checknumber(L,2);
    if(faceIndex<0 || faceIndex>=mesh->mesh->getNbFaces()){
        luaL_error(L,"bad faceIndex:%d",faceIndex);
    }
    Vector3 v3 = mesh->mesh->getFaceNormal(faceIndex);
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}

static int GetCentroid(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataCheck(L, 1);
    Vector3 v3 = mesh->mesh->getCentroid();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}

static int GetVolume(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    PolyhedronMeshUserdata *mesh = PolyhedronMeshUserdataCheck(L, 1);
    lua_pushnumber(L,mesh->mesh->getVolume());
    return 1;
}

void PolyhedronMeshUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"getNbVertices",GetNbVertices},
        {"getVertex",GetVertex },
        {"getNbFaces",GetNbFaces },
        {"getFaceNormal",GetFaceNormal },
        {"getCentroid",GetCentroid },
        {"getVolume",GetVolume  },
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

static bool AreSame(float a, float b){
    return fabs(a - b) <  1.0e-6;
}

// Return the index of a given vertex in the mesh
static int findVertexIndex(const dmArray<Vector3>& vertices, const Vector3& vertex) {
    for (size_t i = 0; i < vertices.Size(); i++) {
        const Vector3& v1 =vertices[i];
		if (AreSame(v1.x,vertex.x)&&AreSame(v1.y,vertex.y)&&AreSame(v1.z,vertex.z)) {
			return i;
		}
	}
	return -1;
}

PolyhedronMeshUserdata* PolyhedronMeshUserdataFromBufferClone(PhysicsCommon *physicsCommon,lua_State *L){
    int top = lua_gettop(L);
    check_arg_count(L, 1);
    dmBuffer::HBuffer buffer = dmScript::CheckBufferUnpack(L,1);
    dmBuffer::Result validate = dmBuffer::ValidateBuffer(buffer);
    if(validate!=dmBuffer::RESULT_OK ) luaL_error(L,"buffer invalid");
    float* positions = 0x0;
    uint32_t components = 0;
    uint32_t stride = 0;
    uint32_t count = 0;
    dmBuffer::Result r = dmBuffer::GetStream(buffer, HASH_POSITION, (void**)&positions, &count, &components, &stride);
    if (r != dmBuffer::RESULT_OK) luaL_error(L,"buffer can't get position");

    float *vertices = new float[count*components];
    float *verticesIter = positions;
    for (int i = 0; i < count; ++i){
        vertices[i*3] = verticesIter[0];
        vertices[i*3+1] = verticesIter[1];
        vertices[i*3+2] = verticesIter[2];
        verticesIter += stride;
        //dmLogInfo("vertex1(%f %f %f)",vertices[i*3],vertices[i*3+1],vertices[i*3+2]);
    }
    int *indices = new int[count];
    int facesSize = count/3;
    PolygonVertexArray::PolygonFace* faces = new PolygonVertexArray::PolygonFace[facesSize];
    PolygonVertexArray::PolygonFace* face = faces;
    Vector3 vertex;
    dmArray<Vector3> verticesV3;
    verticesV3.SetCapacity(count);
    for (int f=0; f < facesSize; f++) {
        for (int v = 0; v < 3; v++) {
            int index = f*3+v;
            //int indexCCW = f*3 + (2-v);
            vertex.x = vertices[index*3];
            vertex.y = vertices[index*3+1];
            vertex.z = vertices[index*3+2];
            int vIndex = findVertexIndex(verticesV3, vertex);
            if (vIndex == -1) {
                vIndex = verticesV3.Size();
                verticesV3.Push(vertex);
            }
            indices[index] = vIndex;
        }
        face->indexBase = f * 3;
        face->nbVertices = 3;
        face++;
    }

    face = faces;
    for (int f=0; f < facesSize; f++) {
        Vector3 p1 = verticesV3[indices[face->indexBase]];
        Vector3 p2 = verticesV3[indices[face->indexBase+1]];
        Vector3 p3 = verticesV3[indices[face->indexBase+2]];
        face++;
    }

    delete[] vertices;
    vertices = new float[verticesV3.Size()*3];
    for (int i = 0; i < verticesV3.Size(); ++i){
        Vector3 v3 = verticesV3[i];
        vertices[i*3] = v3.x;
        vertices[i*3+1] = v3.y;
        vertices[i*3+2] = v3.z;
    }

    PolygonVertexArray* polygonVertexArray = new PolygonVertexArray(
        verticesV3.Size(), vertices,  3 * sizeof(float),
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