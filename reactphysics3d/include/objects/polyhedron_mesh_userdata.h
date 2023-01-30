#ifndef polyhedron_mesh_userdata_h
#define collider_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

namespace rp3dDefold {

class PolyhedronMeshUserdata : public BaseUserData {
private:

public:
    reactphysics3d::PolyhedronMesh *mesh;

    PolyhedronMeshUserdata();
	~PolyhedronMeshUserdata();

	virtual void Destroy(lua_State *L);
};

void PolyhedronMeshUserdataInitMetaTable(lua_State *L);
PolyhedronMeshUserdata* PolyhedronMeshUserdataCheck(lua_State *L, int index);

}
#endif