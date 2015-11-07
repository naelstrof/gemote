#ifndef IS_LUA_H_
#define IS_LUA_H_

#define LUA_COMPAT_MODULE
#include <lua.hpp>
#include <string>
#include <iostream>
#include <fstream>

class lua {
public:
    lua();
    ~lua();
    bool doFile( std::string file );
    void addFunction( std::string name, lua_CFunction func );
    std::string getString( std::string name );
    bool getBool( std::string name );
private:
    lua_State* l;
};

int onPanic( lua_State* l );
int traceback( lua_State* l );

#endif
