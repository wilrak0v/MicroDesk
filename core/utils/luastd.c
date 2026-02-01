#include "luastd.h"

void luaInter() {
    lua_State *lua;
    lua = lua_wrapper_new();
    char script[40];
    while(1) {
        printf("You can write your command just down\n");
        serial_fgets(script, sizeof script);
        int err = lua_dostring(lua, script);
        if (err) printf("ERROR: your script doesn't work I think.\n");
    }
}