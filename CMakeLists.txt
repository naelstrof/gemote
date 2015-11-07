cmake_minimum_required(VERSION 2.8)

project( "gemote" )

set( gemote_VERSION_MAJOR 0 )
set( gemote_VERSION_MINOR 0 )
set( gemote_VERSION_PATCH 0 )

set( BIN_TARGET "${PROJECT_NAME}" )

if( NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE )
   set( CMAKE_BUILD_TYPE RelWithDebInfo )
endif()

# Linux compiler initialization.
if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
     "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
     "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -std=c++11" )
    set( CMAKE_CXX_FLAGS_DEBUG "-Wextra -pedantic -O0 -g" )
    set( CMAKE_CXX_FLAGS_RELEASE "-O2" )
    set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g" )
         # -Wall:   Enable all warnings.
         # -Wextra: Enable some more warnings.
         # -Werror: Have errors on warnings.
         # -pedantic-errors: Even more errors.
         # -Wno-unused-parameter: Don't error on unused parameters, required since we have function hooks
         #                        that have unused parameters.
         # -O#: Optimization level
else()
    message( FATAL_ERROR "Your operating system isn't supported yet! CMake will now exit." )
endif()

find_program( CPPCHECK_EXECUTABLE cppcheck
              DOC "A tool for static C/C++ code analysis." )
if ( CPPCHECK_EXECUTABLE )
    add_custom_target( "check"
                       COMMAND "${CPPCHECK_EXECUTABLE}" "--enable=all" "*"
                       WORKING_DIRECTORY src VERBATIM )
endif()

set(source
    src/main.cpp
    src/lua.cpp)

find_package(Lua REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

add_executable(${BIN_TARGET} ${source})

target_link_libraries(${BIN_TARGET}
                      ${LUA_LIBRARIES})
