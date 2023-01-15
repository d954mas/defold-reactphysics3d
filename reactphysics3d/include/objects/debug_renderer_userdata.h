#ifndef debug_renderer_userdata_h
#define debug_renderer_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "static_hash.h"

using namespace reactphysics3d;

namespace rp3dDefold {

//use same class to collision and rigid body.
//use diff meta tables
class DebugRendererUserdata : public BaseUserData {
private:

public:
    DebugRenderer *renderer;
    DebugRendererUserdata(DebugRenderer* renderer);
	~DebugRendererUserdata();

	virtual void Destroy(lua_State *L);
};

void DebugRendererUserdataInitMetaTable(lua_State *L);
DebugRendererUserdata* DebugRendererUserdataCheck(lua_State *L, int index);
void DebugRendererPush(lua_State *L, DebugRenderer* renderer);
}
#endif