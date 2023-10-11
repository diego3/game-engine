#include "ScriptSystem.h"

#include <iostream>

#include <plog/Log.h>
#include <sol/sol.hpp>

void ScriptSystem::Initialize()
{
    sol::state lua;
    lua.open_libraries(sol::lib::base,
        sol::lib::coroutine,
        sol::lib::string,
        sol::lib::io);

    lua.script("print('bark bark bark!')");

    PLOG_DEBUG << "Lua script initialized successfully\n";
}
