#ifndef polyhedron_mesh_userdata_h
#define polyhedron_mesh_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

namespace rp3dDefold {

class PolyhedronMeshUserdata : public BaseUserData {
private:

public:
    float *vertices=NULL;
    int *indices=NULL;
    reactphysics3d::PolygonVertexArray::PolygonFace* faces=NULL;
    reactphysics3d::PolygonVertexArray* polygonVertexArray=NULL;
    reactphysics3d::PolyhedronMesh *mesh=NULL;

    PolyhedronMeshUserdata();
	~PolyhedronMeshUserdata();

	virtual void Destroy(lua_State *L);
};

void PolyhedronMeshUserdataInitMetaTable(lua_State *L);
PolyhedronMeshUserdata* PolyhedronMeshUserdataCheck(lua_State *L, int index);
PolyhedronMeshUserdata* PolyhedronMeshUserdataFromLua(reactphysics3d::PhysicsCommon *physicsCommon,lua_State *L);

}
#endif