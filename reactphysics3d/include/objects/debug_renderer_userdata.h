#ifndef debug_renderer_userdata_h
#define debug_renderer_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

namespace rp3dDefold {

//use same class to collision and rigid body.
//use diff meta tables
class DebugRendererUserdata : public BaseUserData {
private:

public:
    reactphysics3d::DebugRenderer *renderer;
    DebugRendererUserdata(reactphysics3d::DebugRenderer* renderer);
	~DebugRendererUserdata();

	virtual void Destroy(lua_State *L);
};

void DebugRendererUserdataInitMetaTable(lua_State *L);
DebugRendererUserdata* DebugRendererUserdataCheck(lua_State *L, int index);
void DebugRendererPush(lua_State *L,reactphysics3d::DebugRenderer* renderer);
reactphysics3d::DebugRenderer::DebugItem DebugRendererDebugItemStringToEnum(lua_State *L,const char* str);
const char * DebugRendererDebugItemEnumToString(reactphysics3d::DebugRenderer::DebugItem name);
}
#endif