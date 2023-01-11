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

	reactphysics3d::Transform checkRp3dTransform(lua_State *L, int index);
}

#endif