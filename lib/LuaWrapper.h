#ifndef LUA_WRAPPER_H
#define LUA_WRAPPER_H

#define LUA_USE_C89
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"

// Création et initialisation du Lua state
lua_State* lua_wrapper_new(void);

// Exécution d'un script Lua (avec ajout des constantes Arduino)
int lua_dostring(lua_State *L, const char *script);

// Enregistrement d'une fonction Lua
void lua_register_func(lua_State *L, const char *name, lua_CFunction func);

// Fonction print personnalisée pour Lua
int lua_wrapper_print(lua_State *L);

// Ajout des constantes Arduino dans Lua
void lua_add_constants(lua_State *L);

#endif

