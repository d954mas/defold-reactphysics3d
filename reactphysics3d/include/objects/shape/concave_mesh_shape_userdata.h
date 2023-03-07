#ifndef concave_mesh_shape_h
#define concave_mesh_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

#define RP3D_CONCAVE_MESH_SHAPE_META_FUNCTIONS \
{"getNbSubparts", ConcaveMeshShape_GetNbSubparts},\
{"getNbTriangles", ConcaveMeshShape_GetNbTriangles},\
{"getTriangleVerticesIndices", ConcaveMeshShape_GetTriangleVerticesIndices}\

namespace rp3dDefold {
    int ConcaveMeshShape_GetNbSubparts(lua_State *L);
    int ConcaveMeshShape_GetNbTriangles(lua_State *L);
    CollisionShapeUserdata* ConcaveMeshShapeCheckUserdata(lua_State *L, int index);
    void ConcaveMeshShapeUserdataInitMetaTable(lua_State *L);
}
#endif