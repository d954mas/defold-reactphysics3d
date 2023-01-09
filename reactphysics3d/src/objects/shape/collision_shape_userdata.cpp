#ifndef world_h
#define world_h

#include "objects/base_userdata.h"
#include "static_hash.h"

#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"
#include "reactphysics3d/reactphysics3d.h"




using namespace reactphysics3d;

namespace rp3dDefold {

CollisionShapeLua::CollisionShapeLua(CollisionShape* shape){
    this->shape = shape;
}

CollisionShapeLua::~CollisionShapeLua() {

}

CollisionShapeLua* CollisionShape_get_userdata(lua_State* L, int index){
    CollisionShapeLua *shape = NULL;

    if(luaL_checkudata(L, index, META_NAME_BOX_SHAPE)){
         shape =  *static_cast<CollisionShapeLua**>(luaL_checkudata(L, index, META_NAME_BOX_SHAPE));
    }

    if(shape==NULL){
        luaL_error(L, "Not collision shape");
    }
    if(shape->shape == NULL){
        luaL_error(L, "Can't use destroyed collision shape");
    }

    return shape;
}



int CollisionShape_GetName(lua_State *L){

    return 0;
}

int CollisionShape_GC(lua_State *L){
    return 0;
}


void CollisionShapePush(lua_State *L, CollisionShape* shape){
    switch(shape->getName()) {
        case CollisionShapeName::BOX:
            BoxShapePush(L,(BoxShape*) shape);
            break;
    }

}

}
#endif