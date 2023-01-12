#ifndef aabb_h
#define aabb_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "reactphysics3d/reactphysics3d.h"



using namespace reactphysics3d;

namespace rp3dDefold {
    class AABBLua {
    public:
        AABB aabb;
        AABBLua(AABB aabb);
        AABBLua();
        ~AABBLua();
    };

    void AABBPush(lua_State *L, AABB aabb);
    AABBLua* AABBCheck(lua_State *L, int index);
}
#endif