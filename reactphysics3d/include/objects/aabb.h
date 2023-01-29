#ifndef aabb_h
#define aabb_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "reactphysics3d/reactphysics3d.h"



namespace rp3dDefold {
    class AABBLua {
    public:
        reactphysics3d::AABB aabb;
        AABBLua(reactphysics3d::AABB aabb);
        AABBLua();
        ~AABBLua();
    };

    void AABBPush(lua_State *L, reactphysics3d::AABB aabb);
    AABBLua* AABBCheck(lua_State *L, int index);
}
#endif