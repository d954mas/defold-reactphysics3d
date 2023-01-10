#ifndef world_h
#define world_h

#include "objects/base_userdata.h"
#include "static_hash.h"

#include "objects/shape/box_shape_userdata.h"
#include "objects/shape/collision_shape_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "utils.h"




using namespace reactphysics3d;

namespace rp3dDefold {

CollisionShapeLua::CollisionShapeLua(CollisionShape* shape){
    this->shape = shape;
}

CollisionShapeLua::~CollisionShapeLua() {

}

CollisionShapeLua* CollisionShapeCheck(lua_State* L, int index){
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

const char * CollisionShapeNameEnumToString(CollisionShapeName name){
    dmLogInfo("enum");
    switch(name){
        case CollisionShapeName::TRIANGLE:
            return "TRIANGLE";
        case CollisionShapeName::SPHERE:
            return "SPHERE";
        case CollisionShapeName::CAPSULE:
            return "CAPSULE";
        case CollisionShapeName::BOX:
            return "BOX";
        case CollisionShapeName::CONVEX_MESH:
            return "CONVEX_MESH";
        case CollisionShapeName::TRIANGLE_MESH:
            return "TRIANGLE_MESH";
        case CollisionShapeName::HEIGHTFIELD:
            return "HEIGHTFIELD";
        default:
            assert(false);
    }
}


int CollisionShape_GetName(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    CollisionShapeLua* shape = CollisionShapeCheck(L,1);
    lua_pushstring(L,CollisionShapeNameEnumToString(shape->shape->getName()));
    return 1;
}

int CollisionShape_GC(lua_State *L){
    CollisionShapeLua **shape = reinterpret_cast<CollisionShapeLua **>(lua_touserdata(L, 1));
    delete *shape;
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