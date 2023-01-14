#ifndef world_h
#define world_h

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

}
#endif