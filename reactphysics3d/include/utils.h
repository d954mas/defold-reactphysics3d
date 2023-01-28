#ifndef utils_h
#define utils_h


#include <dmsdk/sdk.h>
#include "undefine_none.h"
#include "reactphysics3d/reactphysics3d.h"
#include <string>

namespace rp3dDefold {
	void check_arg_count(lua_State *L, int count_exact);
	void check_arg_count(lua_State *L, int count_from, int count_to);
	void push_std_string(lua_State *L, std::string str);

	void pushRp3dTransform(lua_State *L,reactphysics3d::Transform transform);
	void pushRp3dRaycastInfo(lua_State *L,const  reactphysics3d::RaycastInfo &info);
	void pushRp3dMaterial(lua_State *L, reactphysics3d::Material &material);
	reactphysics3d::Transform checkRp3dTransform(lua_State *L, int index);
	reactphysics3d::Ray CheckRay(lua_State *L, int index);
    void checkRp3dMaterial(lua_State *L, int index, reactphysics3d::Material &material);


    void pushRp3dHalfEdgeStructureFace(lua_State *L,const reactphysics3d::HalfEdgeStructure::Face &face);
    void pushRp3dHalfEdgeStructureVertex(lua_State *L,const reactphysics3d::HalfEdgeStructure::Vertex &vertex);

}

#endif