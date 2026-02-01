#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include <stdio.h>

static int lua_wrapper_print(lua_State *L) {
    int n = lua_gettop(L);
    int i;
    lua_getglobal(L, "tostring");
    for (i = 1; i <= n; i++) {
        const char *s;
        size_t l;
        lua_pushvalue(L, -1); // function
        lua_pushvalue(L, i);  // argument
        lua_call(L, 1, 1);
        s = lua_tolstring(L, -1, &l);
        if (s == NULL)
            return luaL_error(L, "'tostring' must return a string to 'print'");
        if (i > 1) printf("\t");
        printf("%s", s);
        lua_pop(L, 1);
    }
    printf("\n");
    return 0;
}

lua_State* lua_wrapper_new() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "print", lua_wrapper_print);
    return L;
}

int lua_dostring(lua_State *L, const char *script) {
    int err = luaL_dostring(L, script);
    if (err) {
        printf("# lua error:\n");
        printf("%s", lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    return err;
}

void lua_register_func(lua_State *L, const char *name, lua_CFunction func) {
    lua_register(L, name, func);
}

