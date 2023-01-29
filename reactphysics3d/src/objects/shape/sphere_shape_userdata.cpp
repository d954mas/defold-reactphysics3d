#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"
#include "objects/shape/convex_shape_userdata.h"
#include "objects/shape/convex_polyhedron_shape_userdata.h"
#include "utils.h"

using namespace reactphysics3d;

namespace rp3dDefold {

static SphereShape* SphereShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::SPHERE){
        return (SphereShape*)shape->shape;
    }else{
        luaL_error(L, "shape not SphereShape");
    }
}

CollisionShapeUserdata* SphereShapeCheckUserdata(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::SPHERE){
        return shape;
    }else{
        luaL_error(L, "shape not SphereShape");
    }
}

void SphereShapeUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);
    luaL_Reg functions[] ={
            RP3D_COLLISION_SHAPE_META_FUNCTIONS,
            RP3D_CONVEX_SHAPE_META_FUNCTIONS,
          //  RP3D_SPHERE_SHAPE_META_FUNCTIONS,
            {0, 0}
        };
    luaL_newmetatable(L, META_NAME_SPHERE_SHAPE);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}



}