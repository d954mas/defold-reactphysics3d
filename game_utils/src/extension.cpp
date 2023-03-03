#define EXTENSION_NAME game_utils
#define LIB_NAME "game_utils"
#define MODULE_NAME "game_utils"

#include <dmsdk/sdk.h>
#include "utils.h"

const dmBuffer::StreamDeclaration streams_decl[] = {
    {dmHashString64("position"), dmBuffer::VALUE_TYPE_FLOAT32, 3},
    {dmHashString64("normal"), dmBuffer::VALUE_TYPE_FLOAT32, 3},
};

static int HeightfieldUpdateMesh(lua_State* L){
    DM_LUA_STACK_CHECK(L, 1);
    rp3dDefold::check_arg_count(L, 3);
    int sizeIndices = luaL_getn(L, 1);
    int sizeVertices = luaL_getn(L, 2);
    int sizeNormals = luaL_getn(L, 3);
    if(sizeVertices!=sizeNormals){
        luaL_error(L, "vertices and normals should be same size");
    }
    dmBuffer::HBuffer buffer;
    dmBuffer::Result r = dmBuffer::Create(sizeIndices+1, streams_decl, 2, &buffer);
     if (r != dmBuffer::RESULT_OK) {
        luaL_error(L,"can't create buffer");
    }
    float* bufferPositions;
    uint32_t  bufferPositionsStride;
    r = dmBuffer::GetStream(buffer, dmHashString64("position"),
                (void**)&bufferPositions, NULL, NULL, &bufferPositionsStride);
    if (r != dmBuffer::RESULT_OK) {dmLogError("can't get buffer position"); }

    float* bufferNormals;
    uint32_t  bufferNormalsStride;
    r = dmBuffer::GetStream(buffer, dmHashString64("normal"),
                (void**)&bufferNormals, NULL, NULL, &bufferNormalsStride);
    if (r != dmBuffer::RESULT_OK) {dmLogError("can't get buffer normal"); }

    for (int i = 0; i<=sizeIndices; ++i) {
        lua_rawgeti(L,1,i);
        int index = luaL_checknumber(L,-1);
        lua_pop(L,1);

      //  dmLogInfo("index:%d",index)
        lua_rawgeti(L,2,index);
        dmVMath::Vector3* positionV = dmScript::CheckVector3(L, -1);
        lua_pop(L,1);
      //  dmLogInfo("positionV:%f %f %f",positionV->getX(),positionV->getY(),positionV->getZ())

        lua_rawgeti(L,3,index);
        dmVMath::Vector3* normalV = dmScript::CheckVector3(L, -1);
        lua_pop(L,1);
      //  dmLogInfo("normalV:%f %f %f",normalV->getX(),normalV->getY(),normalV->getZ())

        bufferPositions[0] = positionV->getX();
        bufferPositions[1] = positionV->getY();
        bufferPositions[2] = positionV->getZ();
        bufferPositions +=bufferPositionsStride;

        bufferNormals[0] = normalV->getX();
        bufferNormals[1] = normalV->getY();
        bufferNormals[2] = normalV->getZ();
        bufferNormals +=bufferNormalsStride;
    }

    dmScript::LuaHBuffer luabuffer = { buffer, dmScript::OWNER_LUA };
    PushBuffer(L, luabuffer);

    return 1;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] ={
    {"heightfield_update_mesh", HeightfieldUpdateMesh},
    {0, 0}
};

static void LuaInit(lua_State* L){
	int top = lua_gettop(L);
	// Register lua names
	luaL_register(L, MODULE_NAME, Module_methods);
	lua_pop(L, 1);
	assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}
static dmExtension::Result InitializeMyExtension(dmExtension::Params* params){
	LuaInit(params->m_L);
	printf("Registered %s Extension\n", MODULE_NAME);
	return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params){return dmExtension::RESULT_OK;}

static dmExtension::Result FinalizeMyExtension(dmExtension::Params* params){return dmExtension::RESULT_OK;}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeMyExtension, AppFinalizeMyExtension, InitializeMyExtension, 0, 0, FinalizeMyExtension)