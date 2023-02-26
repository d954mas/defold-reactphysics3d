#include "objects/base_userdata.h"
#include "static_hash.h"

#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/concave_shape_userdata.h"
#include "utils.h"



using namespace reactphysics3d;

namespace rp3dDefold {

static HeightFieldShape* HeightFieldShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::HEIGHTFIELD){
        return (HeightFieldShape*)shape->shape;
    }else{
        luaL_error(L, "shape not HeightFieldShape");
    }
}


void HeightFieldShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_COLLISION_SHAPE_META_FUNCTIONS,
            RP3D_CONCAVE_SHAPE_META_FUNCTIONS,
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_HEIGHTFIELD_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

}
