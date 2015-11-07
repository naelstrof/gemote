#include "lua.hpp"

lua::lua() {
    l = luaL_newstate();
    lua_atpanic( l, onPanic );
    luaL_openlibs( l );
}

lua::~lua() {
    lua_close( l );
}

bool lua::doFile( std::string file ) {
    return luaL_dofile( l, file.c_str() );
}

void lua::addFunction( std::string name, lua_CFunction func ) {
    lua_register( l, name.c_str(), func );
}

std::string lua::getString( std::string name ) {
    lua_getglobal( l, "_G" );
    lua_getfield( l, -1, name.c_str() );
    if ( !lua_isstring( l, -1 ) ) {
        printf( "Warning: Lua tried to use %s as a string. (It's not a string or doesn't exist!)\n", name.c_str() );
        lua_pop( l, 2 );
        return "NULL";
    }
    std::string text = lua_tostring( l, -1 );
    lua_pop( l, 2 );
    return text;
}

bool lua::getBool( std::string name ) {
    lua_getglobal( l, "_G" );
    lua_getfield( l, -1, name.c_str() );
    if ( !lua_isboolean( l, -1 ) ) {
        printf( "Warning: Lua tried to use %s as a boolean. (It's not a boolean or doesn't exist!)\n", name.c_str() );
        lua_pop( l, 2 );
        return false;
    }
    bool boolean = (bool)lua_toboolean( l, -1 );
    lua_pop( l, 2 );
    return boolean;
}

int traceback( lua_State* l ) {
    if ( !lua_isstring( l, 1 ) ) {
        return 0;
    }
    lua_getglobal( l, "debug" );
    if ( !lua_istable( l, -1 ) ) {
        lua_pop( l, 1 );
        return 0;
    }
    lua_getfield( l, -1, "traceback" );
    if ( !lua_isfunction( l, -1 ) ) {
        lua_pop( l, 2 );
        return 0;
    }
    lua_pushvalue( l, 1 );
    lua_pushinteger( l, 2 );
    lua_call( l, 2, 1 );
    return 1;
}

int onPanic( lua_State* l ) {
    std::string error = lua_tostring( l, -1 );
    printf( "Error: %s\n", error.c_str() );
    if ( traceback( l ) ) {
        printf( "Error: %s\n", lua_tostring( l, -1 ) );
    }
    return 0;
}
