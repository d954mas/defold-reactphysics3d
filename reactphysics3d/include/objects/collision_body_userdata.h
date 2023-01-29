#ifndef collision_body_userdata_h
#define collision_body_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"


namespace rp3dDefold {

//use same class to collision and rigid body.
//use diff meta tables
class CollisionBodyUserdata : public BaseUserData {
private:

public:
    reactphysics3d::CollisionBody *body;
    int user_data_ref;
    bool isRigidBody;

    CollisionBodyUserdata(reactphysics3d::CollisionBody* body);
    CollisionBodyUserdata(reactphysics3d::RigidBody* body);
    reactphysics3d::RigidBody* GetRigidBodyOrError(lua_State *L);
	~CollisionBodyUserdata();

	virtual void Destroy(lua_State *L);
};

void CollisionBodyUserdataInitMetaTable(lua_State *L);
CollisionBodyUserdata* CollisionBodyUserdataCheck(lua_State *L, int index);
void CollisionBodyPush(lua_State *L, reactphysics3d::CollisionBody *body);
reactphysics3d::BodyType BodyTypeStringToEnum(lua_State *L,const char* str);
const char * BodyTypeEnumToString(reactphysics3d::BodyType name);
}
#endif