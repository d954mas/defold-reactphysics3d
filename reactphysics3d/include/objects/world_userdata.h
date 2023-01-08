#ifndef world_h
#define world_h

#include <dmsdk/sdk.h>
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "static_hash.h"

using namespace reactphysics3d;

namespace rp3dDefold {

class WorldUserdata : public BaseUserData {
private:

public:
    PhysicsWorld *world;

    WorldUserdata(PhysicsWorld* world);
	~WorldUserdata();

	virtual void Destroy(lua_State *L);
};

void WorldUserdataInitMetaTable(lua_State *L);
WorldUserdata* WorldUserdataCheck(lua_State *L, int index);

PhysicsWorld::WorldSettings WorldSettings_from_table(lua_State *L, int index);

}
#endif