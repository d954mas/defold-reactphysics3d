#include "static_hash.h"
#include "objects/debug_renderer_userdata.h"
#include "utils.h"

#define META_NAME "rp3d::DebugRenderer"
#define USERDATA_TYPE "rp3d::DebugRenderer"

#include <render/render_ddf.h> // dmRenderDDF::DrawLine
namespace dmRender
{
    extern const char* RENDER_SOCKET_NAME;
}

namespace dmMessage
{
    Result GetSocket(const char *name, HSocket* out_socket);
}




using namespace reactphysics3d;

namespace rp3dDefold {

DebugRendererUserdata::DebugRendererUserdata(DebugRenderer* renderer): BaseUserData(USERDATA_TYPE){
    this->metatable_name = META_NAME;
    this->renderer = renderer;
    this->obj = renderer;
    this->renderer->setUserData(this);
}

DebugRendererUserdata::~DebugRendererUserdata() {

}


DebugRendererUserdata* DebugRendererUserdataCheck(lua_State *L, int index) {
    DebugRendererUserdata *userdata = (DebugRendererUserdata*) BaseUserData_get_userdata(L, index, USERDATA_TYPE);
	return userdata;
}

static int SetIsDebugItemDisplayed(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 3);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    DebugRenderer::DebugItem item = DebugRendererDebugItemStringToEnum(L,lua_tostring(L,2));
    bool isDisplayed = lua_toboolean(L,3);
    userdata->renderer->setIsDebugItemDisplayed(item,isDisplayed);
    return 0;
}

static int GetIsDebugItemDisplayed(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 2);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    DebugRenderer::DebugItem item = DebugRendererDebugItemStringToEnum(L,lua_tostring(L,2));
    lua_pushboolean(L,userdata->renderer->getIsDebugItemDisplayed(item));
    return 1;
}

static int SetContactPointSphereRadius (lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    float radius = luaL_checknumber(L,2);
    userdata->renderer->setContactPointSphereRadius(radius);
    return 0;
}

static int GetContactPointSphereRadius(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->renderer->getContactPointSphereRadius());
    return 1;
}

static int SetContactNormalLength (lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 2);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    float radius = luaL_checknumber(L,2);
    userdata->renderer->setContactNormalLength(radius);
    return 0;
}

static int GetContactNormalLength(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    lua_pushnumber(L,userdata->renderer->getContactNormalLength());
    return 1;
}

inline void RGBUintToVector(uint rgb, dmVMath::Vector4 &color){
    color.setX(((rgb & 0x00FF0000) >> 16)/256.0);
    color.setY(((rgb & 0x0000FF00) >> 8)/256.0);
    color.setZ(((rgb & 0x000000FF) >> 0)/256.0);
}

inline void DrawLine(dmRenderDDF::DrawLine &msg, Vector3 p1,Vector3 p2,uint32 color){;
    msg.m_StartPoint.setX(p1.x);
    msg.m_StartPoint.setY(p1.y);
    msg.m_StartPoint.setZ(p1.z);

    msg.m_EndPoint.setX(p2.x);
    msg.m_EndPoint.setY(p2.y);
    msg.m_EndPoint.setZ(p2.z);

    RGBUintToVector(color,msg.m_Color);
}

static int Draw(lua_State *L){
    DM_LUA_STACK_CHECK(L, 0);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);

    dmGameObject::HInstance instance = dmScript::CheckGOInstance(L);
    dmMessage::URL receiver;
    dmMessage::ResetURL(&receiver);
    dmMessage::Result result = dmMessage::GetSocket(dmRender::RENDER_SOCKET_NAME, &receiver.m_Socket);
    if (result != dmMessage::RESULT_OK)
    {
        luaL_error(L,"The socket '%s' could not be found.", dmRender::RENDER_SOCKET_NAME);
    }


    const Array<DebugRenderer::DebugLine>& lines = userdata->renderer->getLines();
    //dmLogInfo("lines:%d",lines.size());

    dmRenderDDF::DrawLine msg;
    for(int i=0;i<lines.size();i++){
        DebugRenderer::DebugLine line = lines[i];


        DrawLine(msg,line.point1,line.point2,line.color1);
        result = dmMessage::PostDDF(&msg,0x0, &receiver, (uintptr_t) instance,0, 0);
        if(result!=dmMessage::RESULT_OK){luaL_error(L,"can't draw line");}
    }

    const Array<DebugRenderer::DebugTriangle>& triangles = userdata->renderer->getTriangles();
    //dmLogInfo("triangles:%d",triangles.size());
    for(int i=0;i<triangles.size();i++){
        DebugRenderer::DebugTriangle triangle = triangles[i];

        DrawLine(msg,triangle.point1,triangle.point2,triangle.color1);
        result = dmMessage::PostDDF(&msg,0x0, &receiver, (uintptr_t) instance,0, 0);
        if(result!=dmMessage::RESULT_OK){luaL_error(L,"can't draw line");}

        DrawLine(msg,triangle.point2,triangle.point3,triangle.color2);
        result = dmMessage::PostDDF(&msg,0x0, &receiver, (uintptr_t) instance,0, 0);
        if(result!=dmMessage::RESULT_OK){luaL_error(L,"can't draw line");}

        DrawLine(msg,triangle.point3,triangle.point1,triangle.color3);
        result = dmMessage::PostDDF(&msg,0x0, &receiver, (uintptr_t) instance,0, 0);
        if(result!=dmMessage::RESULT_OK){luaL_error(L,"can't draw line");}
    }

	return 0;
}

static int ToString(lua_State *L){
    DM_LUA_STACK_CHECK(L, 1);
    check_arg_count(L, 1);
    DebugRendererUserdata *userdata = DebugRendererUserdataCheck(L, 1);
    lua_pushfstring( L, "rp3d::DebugRenderer[%p]",(void *) userdata->renderer);
	return 1;
}

void DebugRendererUserdataInitMetaTable(lua_State *L){
    int top = lua_gettop(L);

    luaL_Reg functions[] = {
        {"setIsDebugItemDisplayed",SetIsDebugItemDisplayed},
        {"getIsDebugItemDisplayed",GetIsDebugItemDisplayed},
        {"getContactPointSphereRadius",GetContactPointSphereRadius},
        {"setContactPointSphereRadius",SetContactPointSphereRadius},
        {"getContactNormalLength",GetContactNormalLength},
        {"setContactNormalLength",SetContactNormalLength},
        {"draw",Draw},
        {"__tostring",ToString},
        { 0, 0 }
    };
    luaL_newmetatable(L, META_NAME);
    luaL_register (L, NULL,functions);
    lua_pushvalue(L, -1);
    lua_setfield(L, -1, "__index");
    lua_pop(L, 1);

    assert(top == lua_gettop(L));
}


void DebugRendererUserdata::Destroy(lua_State *L){
    renderer->setUserData(NULL);
    renderer = NULL;
    BaseUserData::Destroy(L);
}

void DebugRendererPush(lua_State *L, DebugRenderer* renderer){
    if(renderer->getUserData()!=NULL){
        DebugRendererUserdata* userdata =(DebugRendererUserdata*) renderer->getUserData();
        userdata->Push(L);
    }else{
        DebugRendererUserdata* userdata = new DebugRendererUserdata(renderer);
        userdata->Push(L);
    }
}

DebugRenderer::DebugItem DebugRendererDebugItemStringToEnum(lua_State *L,const char* str){
    switch (hash_string(str)){
        case HASH_COLLIDER_AABB:
            return DebugRenderer::DebugItem::COLLIDER_AABB;
        case HASH_COLLIDER_BROADPHASE_AABB:
            return DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB;
        case HASH_COLLISION_SHAPE:
            return DebugRenderer::DebugItem::COLLISION_SHAPE;
        case HASH_CONTACT_POINT:
            return DebugRenderer::DebugItem::CONTACT_POINT;
        case HASH_CONTACT_NORMAL:
            return DebugRenderer::DebugItem::CONTACT_NORMAL;
        default:
            luaL_error(L, "unknown DebugRenderer::DebugItem:%s", str);
            break;
    }
}
const char * DebugRendererDebugItemEnumToString(DebugRenderer::DebugItem name){
    switch(name){
        case DebugRenderer::DebugItem::COLLIDER_AABB:
            return "COLLIDER_AABB";
        case DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB:
            return "COLLIDER_BROADPHASE_AABB";
        case DebugRenderer::DebugItem::COLLISION_SHAPE:
            return "COLLISION_SHAPE";
        case DebugRenderer::DebugItem::CONTACT_POINT:
            return "CONTACT_POINT";
        case DebugRenderer::DebugItem::CONTACT_NORMAL:
            return "CONTACT_NORMAL";
        default:
            assert(false);
    }
}

}