#include "script/type/def.h"
#include "script/class_type.h"
#include "script/lua_bind.h"
#include "script/state.h"

#include "go/game_object.h"
#include "com/sprite2d/sprite.h"
#include "com/sprite2d/camera2d.h"
#include "com/sprite2d/quad_sprite.h"
#include "com/sprite2d/texture_atlas.h"

#include "com/scene2d/world_box2d.h"
#include "com/scene2d/shape_desc.h"

using namespace sprite2d;
using namespace scene2d;

namespace script {
    static int c3d_lua_add_layout(lua_State* L) {
        sprite_mgr& mgr = converter<sprite_mgr&>::from(L, 1, nullptr);
        sprite_mgr::vertices_t vertices;
        for (int i = 2, t = lua_gettop(L); i <= t; ++i) {
            luaL_argcheck(L, lua_istable(L, i), i, "expect a table");
            lua_rawgeti(L, -1, 1);
            lua_rawgeti(L, -2, 2);
            if (lua_isstring(L, -2)) {
                // FIXME: we assume only Float for now
                vertices.push_back({
                    lua_tostring(L, -2),
                    vertex_layout::Float,
                    (int)lua_tonumber(L, -1)
                });
            }
            lua_pop(L, 2);
        }
        lua_pushnumber(L, mgr.add_type(vertices));
        return 1;
    }
    
    static int c3d_lua_set_gravity(lua_State* L) {
        world2d_mgr& mgr = converter<world2d_mgr&>::from(L, 1, nullptr);
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        mgr.set_gravity(vector2f(x, y));
        lua_settop(L, 1);
        return 1;
    }
    
    static int c3d_lua_world_query(lua_State* L) {
        world2d_mgr& mgr = converter<world2d_mgr&>::from(L, 1, nullptr);
        luaL_argcheck(L, lua_isfunction(L, 4), 4, "expect a function");
        float x = lua_tonumber(L, 2);
        float y = lua_tonumber(L, 3);
        mgr.query([=] (collider2d *c) {
            lua_pushvalue(L, 4);
            converter<collider2d*>::to(L, c);
            if (lua_pcall(L, 1, 1, 0) != 0) {
                // TODO: error
                printf("error: %s", lua_tostring(L, -1));
                return false; // stop querying
            } else {
                bool is_done = lua_toboolean(L, -1);
                lua_pop(L, 1);
                return !is_done;
            }
        }, vector2f(x, y));
        lua_settop(L, 1);
        return 1;
    }
    
    static int c3d_lua_cast_from_screen(lua_State* L) {
        auto& camera = converter<camera2d&>::from(L, 1, nullptr);
        
        auto ray = camera.cast_from_screen({lua_tonumber(L, 2), lua_tonumber(L, 3)});
        float t = -ray.p.z() / ray.d.z();
        auto cross = ray.p + ray.d * t;
        lua_pushnumber(L, cross[0]);
        lua_pushnumber(L, cross[1]);
        return 2;
    }
    
    void def_sprite2d(state* st, std::string const& scope) {
        st->import((scope + ".collider").c_str())
        .import<uint8_t>(LUA_ENUM(collider2d, dynamic))
        .import<uint8_t>(LUA_ENUM(collider2d, kinametic))
        .import<uint8_t>("static", collider2d::static_)
        .import<uint8_t>("normal", collider2d::type_normal)
        .import<uint8_t>("character", collider2d::type_character)
        .import<uint8_t>("bullet", collider2d::type_bullet)
        
        ;
        
        class_<game_object>::type()
        .def("add_quad_sprite", LUA_BIND((&game_object::add_component<quad_sprite, int>)))
        .def("add_camera2d", LUA_BIND((&game_object::add_component<camera2d>)))
        .def("add_collider2d", LUA_BIND((&game_object::add_component<collider2d, int, int>)))
        .def("get_camera2d", LUA_BIND((&game_object::get_component<camera2d>)))
        ;
        
        class_<sprite2d::sprite>::type()
        .def("set_material", LUA_BIND_S(void (sprite::*)(sprite_material*),
                                        &sprite::set_material))
        ;
        
        class_<quad_sprite>::type()
        .derive<sprite2d::sprite>()
        .def("set_from_atlas", LUA_BIND(&quad_sprite::set_from_atlas))
        ;
        
        class_<sprite_mgr>::type()
        .def("add_material", LUA_BIND_S(sprite_material* (sprite_mgr::*)(std::string const&,
                                                                         gpu_program*,
                                                                         render_state::ptr const&,
                                                                         render_uniform::ptr const&),
                                        &sprite_mgr::add_material))
        .def("vertex_layout", LUA_BIND(&sprite_mgr::vertex_layout))
        .def("add_layout", c3d_lua_add_layout)
        ;
        
        
        class_<camera2d>::type()
        .derive<com::camera>()
        .def("cast_from_screen", c3d_lua_cast_from_screen)
        ;
        
        class_<world2d_mgr>::type()
        .def("set_gravity", c3d_lua_set_gravity)
        .def("query", c3d_lua_world_query)
        ;
#if 0
        script::class_<texture_atlas>::type()
        ;
#endif
        
   }
}

