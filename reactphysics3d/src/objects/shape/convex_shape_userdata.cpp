#include "objects/base_userdata.h"
#include "static_hash.h"

#include "objects/shape/collision_shape_userdata.h"
#include "utils.h"




using namespace reactphysics3d;

namespace rp3dDefold {

static ConvexShape* ConvexShapeCheck(lua_State* L, int index){
    CollisionShapeUserdata *shape = CollisionShapeCheck(L,index);
    if (shape->shape->isConvex()){
        return (ConvexShape*)shape->shape;
    }else{
        luaL_error(L, "shape not ConvexShape");
    }
}

int ConvexShape_GetMargin(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    ConvexShape* shape = ConvexShapeCheck(L,1);
    lua_pushnumber(L,shape->getMargin());
    return 1;
}


}
