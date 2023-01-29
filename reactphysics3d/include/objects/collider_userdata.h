#ifndef collider_userdata_h
#define collider_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

namespace rp3dDefold {

//use same class to collision and rigid body.
//use diff meta tables
class ColliderUserdata : public BaseUserData {
private:

public:
    reactphysics3d::Collider *collider;
    int user_data_ref;

    ColliderUserdata(reactphysics3d::Collider* collider);
	~ColliderUserdata();

	virtual void Destroy(lua_State *L);
};

void ColliderUserdataInitMetaTable(lua_State *L);
ColliderUserdata* ColliderUserdataCheck(lua_State *L, int index);
void ColliderPush(lua_State *L, reactphysics3d::Collider* collider);
}
#endif