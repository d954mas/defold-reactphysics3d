#ifndef height_field_shape_h
#define height_field_shape_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/shape/collision_shape_userdata.h"

#define RP3D_HEIGHTFIELD_SHAPE_META_FUNCTIONS \
{"getNbRows", HeightFieldShape_getNbRows},\
{"getNbColumns", HeightFieldShape_getNbColumns},\
{"getVertexAt", HeightFieldShape_getVertexAt},\
{"getHeightAt", HeightFieldShape_getHeightAt},\
{"getHeightDataType", HeightFieldShape_getHeightDataType}\

namespace rp3dDefold {
    CollisionShapeUserdata* HeightFieldShapeCheckUserdata(lua_State *L, int index);
    void HeightFieldShapeUserdataInitMetaTable(lua_State *L);
    int HeightFieldShape_getNbRows(lua_State *L);
    int HeightFieldShape_getNbColumns(lua_State *L);
    int HeightFieldShape_getHeightDataType(lua_State *L);
}
#endif