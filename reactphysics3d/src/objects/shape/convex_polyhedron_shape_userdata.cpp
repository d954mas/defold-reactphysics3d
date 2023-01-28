#ifndef world_h
#define world_h

#include "objects/base_userdata.h"
#include "static_hash.h"

#include "objects/shape/convex_polyhedron_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"
#include "utils.h"




using namespace reactphysics3d;

namespace rp3dDefold {

static ConvexPolyhedronShape* ConvexPolyhedronShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->isConvex() && shape->shape->isPolyhedron()){
        return (ConvexPolyhedronShape*)shape->shape;
    }else{
        luaL_error(L, "shape not ConvexPolyhedronShape");
    }
}

int ConvexPolyhedronShape_GetNbFaces(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    lua_pushnumber(L,shape->getNbFaces());
    return 1;
}

int ConvexPolyhedronShape_GetFace(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    uint32 faceIndex = luaL_checknumber(L,2);
    if(faceIndex<0 || faceIndex>=shape->getNbFaces()){
        luaL_error(L,"bad faceIndex:%d",faceIndex);
    }
    pushRp3dHalfEdgeStructureFace(L,shape->getFace(faceIndex));
    return 1;
}

int ConvexPolyhedronShape_GetNbVertices(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    lua_pushnumber(L,shape->getNbVertices());
    return 1;
}

int ConvexPolyhedronShape_GetVertex(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    uint32 vertexIndex = luaL_checknumber(L,2);
    if(vertexIndex<0 || vertexIndex>=shape->getNbVertices()){
        luaL_error(L,"bad vertexIndex:%d",vertexIndex);
    }
    pushRp3dHalfEdgeStructureVertex(L,shape->getVertex(vertexIndex));
    return 1;
}

int ConvexPolyhedronShape_GetVertexPosition(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    uint32 vertexIndex = luaL_checknumber(L,2);
    if(vertexIndex<0 || vertexIndex>=shape->getNbVertices()){
        luaL_error(L,"bad vertexIndex:%d",vertexIndex);
    }
    Vector3 v3 = shape->getVertexPosition(vertexIndex);
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}
int ConvexPolyhedronShape_GetFaceNormal(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    uint32 faceIndex = luaL_checknumber(L,2);
    if(faceIndex<0 || faceIndex>=shape->getNbFaces()){
        luaL_error(L,"bad faceIndex:%d",faceIndex);
    }
    Vector3 v3 = shape->getFaceNormal(faceIndex);
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}

int ConvexPolyhedronShape_GetNbHalfEdges(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    lua_pushnumber(L,shape->getNbHalfEdges());
    return 1;
}

int ConvexPolyhedronShape_GetHalfEdge(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    uint32 edgeIndex = luaL_checknumber(L,2);
    if(edgeIndex<0 || edgeIndex>=shape->getNbHalfEdges()){
        luaL_error(L,"bad edgeIndex:%d",edgeIndex);
    }
    pushRp3dHalfEdgeStructureEdge(L,shape->getHalfEdge(edgeIndex));
    return 1;
}

int ConvexPolyhedronShape_GetCentroid(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    Vector3 v3 = shape->getCentroid();
    dmVMath::Vector3 dmV3(v3.x,v3.y,v3.z);
    dmScript::PushVector3(L, dmV3);
    return 1;
}

int ConvexPolyhedronShape_FindMostAntiParallelFace(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    ConvexPolyhedronShape* shape = ConvexPolyhedronShapeCheck(L,1);
    dmVMath::Vector3* dmV3 = dmScript::CheckVector3(L, 2);
    Vector3 v3(dmV3->getX(),dmV3->getY(),dmV3->getZ());
    lua_pushnumber(L,shape->findMostAntiParallelFace(v3));
    return 1;
}

}
#endif