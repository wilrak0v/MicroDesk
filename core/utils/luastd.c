#include "luastd.h"

int run = 1;

static int luaNeofetch(lua_State *L) {
    neofetch();
    return 0;
}

static int luaClear(lua_State *L) {
    clear();
    return 0;
}

static int luaVersion(lua_State *L) {
    version();
    return 0;
}

static int luaAbout(lua_State *L) {
    about();
    return 0;
}

static int luaInfo(lua_State *L) {
    const char *s = luaL_checkstring(L, 1);
    char args[15];
    strncpy(args, s, sizeof(args) - 1);
    args[sizeof(args) - 1] = '\0';
    info(args);
    return 0;
}

static int luaStop(lua_State *L) {
    run = 0;
    return 0;
}

void luaRegister(lua_State *lua) {
    lua_register(lua, "neofetch", luaNeofetch);
    lua_register(lua, "clear", luaClear);
    lua_register(lua, "version", luaVersion);
    lua_register(lua, "about", luaAbout);
    lua_register(lua, "info", luaInfo);
    lua_register(lua, "exit", luaStop);
}

void luaInter() {
    run = 1;
    lua_State *lua;
    lua = lua_wrapper_new();
    luaRegister(lua);
    char script[40];
    while(run) {
        serial_fgets(script, sizeof script);
        int err = lua_dostring(lua, script);
        if (err) printf("\nERROR: your script doesn't work I think.\n");
    }
}