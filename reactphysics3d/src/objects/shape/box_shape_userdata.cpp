#ifndef world_h
#define world_h

#include "reactphysics3d/reactphysics3d.h"
#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"


using namespace reactphysics3d;

namespace rp3dDefold {

CollisionShapeLua* BoxShapeCheck(lua_State* L, int index){
    CollisionShapeLua *shape = CollisionShapeCheck(L,index);
    if (shape->shape->getName() == CollisionShapeName::BOX){
        return shape;
    }else{
        luaL_error(L, "shape not BoxShape");
    }
}

void BoxShapePush(lua_State *L, BoxShape* shape){
    CollisionShapeLua *shapeLua = new CollisionShapeLua(shape);
    *static_cast<CollisionShapeLua**>(lua_newuserdata(L, sizeof(CollisionShapeLua*))) = shapeLua;
    if(luaL_newmetatable(L, META_NAME_BOX_SHAPE)){
        static const luaL_Reg functions[] ={
            {"__gc", CollisionShape_GC},
            {0, 0}
        };
        luaL_register(L, NULL,functions);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
    }
    lua_setmetatable(L, -2);
}

}
#endif