#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"


using namespace reactphysics3d;

namespace rp3dDefold {

CollisionShapeUserdata* BoxShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::BOX){
        return shape;
    }else{
        luaL_error(L, "shape not BoxShape");
    }
}

void BoxShapeShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            {"getName", CollisionShape_GetName},
            {"getType", CollisionShape_GetType},
            {"isPolyhedron", CollisionShape_IsPolyhedron},
            {"isConvex", CollisionShape_IsConvex},
            {"getLocalBounds", CollisionShape_GetLocalBounds},
            {"getId", CollisionShape_GetId},
            {"getLocalInertiaTensor", CollisionShape_GetLocalInertiaTensor},
            {"getVolume", CollisionShape_GetVolume},
            {"computeAABB", CollisionShape_ComputeAABB},
            {"__tostring", CollisionShape_ToString},
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_BOX_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}


}