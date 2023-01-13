#ifndef collision_body_userdata_h
#define collision_body_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"
#include "static_hash.h"

using namespace reactphysics3d;

namespace rp3dDefold {

//use same class to collision and rigid body.
//use diff meta tables
class CollisionBodyUserdata : public BaseUserData {
private:

public:
    CollisionBody *body;
    int user_data_ref;
    bool isRigidBody;

    CollisionBodyUserdata(CollisionBody* body);
    CollisionBodyUserdata(RigidBody* body);
	~CollisionBodyUserdata();

	virtual void Destroy(lua_State *L);
};

void CollisionBodyUserdataInitMetaTable(lua_State *L);
CollisionBodyUserdata* CollisionBodyUserdataCheck(lua_State *L, int index);

}
#endif