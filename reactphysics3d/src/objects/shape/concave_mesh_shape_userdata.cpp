#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/concave_mesh_shape_userdata.h"
#include "objects/shape/concave_shape_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static ConcaveMeshShape* ConcaveMeshShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::TRIANGLE_MESH){
        return (ConcaveMeshShape*)shape->shape;
    }else{
        luaL_error(L, "shape not ConcaveMeshShape");
    }
}

CollisionShapeUserdata* ConcaveMeshShapeCheckUserdata(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::TRIANGLE_MESH){
        return shape;
    }else{
        luaL_error(L, "shape not ConcaveMeshShape");
    }
}

int ConcaveMeshShape_GetNbSubparts(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConcaveMeshShape* shape = ConcaveMeshShapeCheck(L,1);
    lua_pushnumber(L,shape->getNbSubparts());
    return 1;
}

int ConcaveMeshShape_GetNbTriangles(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    ConcaveMeshShape* shape = ConcaveMeshShapeCheck(L,1);
    int subPart = luaL_checknumber(L,2);
    if (subPart<0 || subPart >= shape->getNbSubparts()){
        luaL_error(L,"Bad subPart:%d. Subparts:%d",subPart,shape->getNbSubparts());
    }
    lua_pushnumber(L,shape->getNbTriangles(subPart));
    return 1;
}

int ConcaveMeshShape_GetTriangleVerticesIndices(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 3);
    ConcaveMeshShape* shape = ConcaveMeshShapeCheck(L,1);
    int subPart = luaL_checknumber(L,2);
    if (subPart<0 || subPart >= shape->getNbSubparts()){
        luaL_error(L,"Bad subPart:%d. Subparts:%d",subPart,shape->getNbSubparts());
    }
    int triangleIndex = luaL_checknumber(L,3);
    if (triangleIndex<0 || triangleIndex >= shape->getNbTriangles(subPart)){
        luaL_error(L,"Bad triangle:%d. Triangles:%d",triangleIndex,shape->getNbTriangles(subPart));
    }
    uint32 result[3];
    shape->getTriangleVerticesIndices(subPart,triangleIndex,result);

    lua_newtable(L);
    for(int i=0;i<3;++i){
        lua_pushnumber(L,result[i]);
        lua_rawseti(L, -2, i+1);
    }
    return 1;
}

void ConcaveMeshShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_COLLISION_SHAPE_META_FUNCTIONS,
            RP3D_CONCAVE_SHAPE_META_FUNCTIONS,
            RP3D_CONCAVE_MESH_SHAPE_META_FUNCTIONS,
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_CONCAVE_MESH_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}




}