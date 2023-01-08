#ifndef utils_h
#define utils_h


#include <dmsdk/sdk.h>

namespace rp3dDefold {
	void check_arg_count(lua_State *L, int count_exact);
	void check_arg_count(lua_State *L, int count_from, int count_to);
}

#endif