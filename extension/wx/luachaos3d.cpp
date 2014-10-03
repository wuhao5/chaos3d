#include "luachaos3d.h"
#include "render_wxwindow.h"
#include "re/render_device.h"
#include "re/gles20/render_device.h"

#include "script/type/def.h"
#include "script/class_type.h"
#include "script/lua_bind.h"
#include "script/state.h"
#include "script/converter_ptr.h"

#include "wxlua/wxlstate.h"
#include "wxlua/wxlbind.h"
#include <wx/window.h>

using namespace script;

static int c3d_lua_create_wxwindow(lua_State* L) {
    wxLuaState state(L);
    
    render_device& device = converter<render_device&>::from(L, 1, nullptr);
    gles20::render_wxwindow_egl* window =
        gles20::render_wxwindow_egl::create(dynamic_cast<gles20::render_device*>(&device),
                                            (wxWindow*)state.GetUserDataType(2, *p_wxluatype_wxWindow),
                                            render_target::target_size_t(),
                                            render_window::window_pos_t());
    converter<gles20::render_wxwindow_egl*>::to(L, window);
    window->release();
    return 1;
}

extern "C" int luaopen_chaos3d_wx(lua_State *L) {
    class_<render_device>::type()
    .def("create_wxwindow", c3d_lua_create_wxwindow)
    ;
    
    return 0;
}