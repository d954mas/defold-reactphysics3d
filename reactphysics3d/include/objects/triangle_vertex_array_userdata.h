#ifndef triangle_vertex_array_userdata_h
#define triangle_vertex_array_userdata_h

#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "objects/base_userdata.h"
#include "reactphysics3d/reactphysics3d.h"

namespace rp3dDefold {

class TriangleVertexArrayUserdata : public BaseUserData {
private:

public:
    float *vertices=NULL;
    float *normals=NULL;
    int *indices=NULL;
    reactphysics3d::TriangleVertexArray *triangleVertexArray=NULL;

    TriangleVertexArrayUserdata(reactphysics3d::TriangleVertexArray *triangleVertexArray);
	~TriangleVertexArrayUserdata();

	virtual void Destroy(lua_State *L);
};
void TriangleVertexArrayPush(lua_State *L, reactphysics3d::TriangleVertexArray* array);
void TriangleVertexArrayUserdataInitMetaTable(lua_State *L);
TriangleVertexArrayUserdata* TriangleVertexArrayUserdataCheck(lua_State *L, int index);
TriangleVertexArrayUserdata* TriangleVertexArrayUserdataFromLua(lua_State *L);
TriangleVertexArrayUserdata* TriangleVertexArrayUserdataFromBufferClone(reactphysics3d::PhysicsCommon *physicsCommon,lua_State *L);

}
#endif