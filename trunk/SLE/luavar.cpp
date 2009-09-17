/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luavar.cpp
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月20日
* GUID				：B2ABD955-30D0-4B7F-A072-A36FD51303FC
* Comments	：
*******************************************************************************/

#include "StdAfx.h"
#include "luavar.h"
#include "_LuaValueHolder.h"

using namespace sle;

luavar::luavar(luaenvironment *lpLuaEvrnt, const char *szName) :
	luaelement(lpLuaEvrnt, szName)
{
}

luavar::~luavar(void)
{
}

luavar::operator int()
{
	_Push();
	int nType = m_lpStackPrase->get_type(-1);
	ASSERT(nType == LUA_TNUMBER);
	double dValue = lua_tonumber(m_lpLuaEvrnt->luastate(), -1);
	_Pop();
	return (int)dValue;
}
luavar::operator double()
{
	_Push();
	int nType = m_lpStackPrase->get_type(-1);
	ASSERT(nType == LUA_TNUMBER);
	double dValue = lua_tonumber(m_lpLuaEvrnt->luastate(), -1);
	_Pop();
	return dValue;
}
luavar::operator bool()
{
	_Push();
	int nType = m_lpStackPrase->get_type(-1);
	ASSERT(nType == LUA_TBOOLEAN);
	int bValue = lua_toboolean(m_lpLuaEvrnt->luastate(), -1);
	_Pop();
	return bValue != 0;
}
luavar::operator const char*()
{
	_Push();
	const char *szValue = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
	m_lpValueHolder->setvalue(LUA_TSTRING, szValue, strlen(szValue) + 1);
	_Pop();
	return *m_lpValueHolder;
}
void luavar::setnil()
{
	_PushWithoutKey();
	lua_pushnil(m_lpLuaEvrnt->luastate()); //TODO:把pushnil方法封装到stackprase里面
	if (_IsGlobal())
	{
		lua_setglobal(m_lpLuaEvrnt->luastate(), m_szName.c_str());
	}
	else
		lua_settable(m_lpLuaEvrnt->luastate(), -3);
	_Pop();
}
