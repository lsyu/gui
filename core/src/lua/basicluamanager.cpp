/*
 * Labs4Physics - visualisation of physics process
 * Copyright (C) 2013  Leyko Sergey powt81lsyu@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "basicluamanager.h"

namespace bhm {

lua_State *CBasicLuaManager::m_lua = luaL_newstate();

CBasicLuaManager::CBasicLuaManager()
{
    if (m_lua) {
        const luaL_Reg lualibs[] =
        {
            { "base", luaopen_base },
            { NULL, NULL}
        };

        const luaL_Reg *lib = lualibs;
        for(; lib->func != NULL; lib++)
        {
            lib->func(m_lua);
            lua_settop(m_lua, 0);
        }
    }
}

CBasicLuaManager::~CBasicLuaManager()
{
    if (m_lua) {
        lua_close(m_lua);
        m_lua = nullptr;
    }
}

void CBasicLuaManager::closeLua()
{
    if (m_lua) {
        lua_close(m_lua);
        m_lua = nullptr;
    }

}

} // namespace behemoth
