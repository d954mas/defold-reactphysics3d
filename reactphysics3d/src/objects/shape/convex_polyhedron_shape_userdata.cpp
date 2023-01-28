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


}
#endif