#ifndef triangle_mesh_userdata_h
#define triangle_mesh_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

namespace rp3dDefold {

class TriangleMeshUserdata : public BaseUserData {
private:

public:
    reactphysics3d::TriangleMesh *mesh=NULL;

    TriangleMeshUserdata(reactphysics3d::TriangleMesh *triangleMesh);
	~TriangleMeshUserdata();

	virtual void Destroy(lua_State *L);
};

void TriangleMeshUserdataInitMetaTable(lua_State *L);
TriangleMeshUserdata* TriangleMeshUserdataCheck(lua_State *L, int index);

}
#endif