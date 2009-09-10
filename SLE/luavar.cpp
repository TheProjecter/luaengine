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
bool luavar::_PushWithoutKey()
{
	//TODO 用strtok线程不安全，有空自己写个实时的split
	bool bRet = true;
	char *lpBuffer = new char[m_szName.size() + 1];
	strcpy(lpBuffer, m_szName.c_str());
	const char *szName = strtok(lpBuffer, ".");
	if (szName != NULL)
		lua_getglobal(m_lpLuaEvrnt->luastate(), szName);
	//m_nPushCount = 0;
	bool bFirst = true;
	while ((szName = strtok(NULL, ".")) != NULL)
	{
		if (!bFirst)
		{
			int nType = m_lpStackPrase->get_type(-2);
			//这里要判断，域名中间的某级为nil，说明当前域名是无效的，比如T1.T2.T3，而T2是nil，则无效
			//如果Push失败，恢复堆栈原状
			if (nType == LUA_TNIL)
			{
				_Pop();
				bRet = false;
				break;
			}
			lua_rawget(m_lpLuaEvrnt->luastate(), -2);
			lua_remove(m_lpLuaEvrnt->luastate(), -2);
		}
		//++m_nPushCount;
		bFirst = false;
		int nKey = atoi(szName);
		if (nKey > 0)
			lua_pushinteger(m_lpLuaEvrnt->luastate(), nKey);
		else
			lua_pushstring(m_lpLuaEvrnt->luastate(), szName);
	}
	DELETE_POINTER(lpBuffer);
	return bRet;
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
	_LuaValueHolder vHolder;
	_Push();
	const char *szValue = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
	vHolder.setvalue(LUA_TNUMBER, szValue, strlen(szValue) + 1);
	_Pop();
	return vHolder;
}
void luavar::clear()
{
	_PushWithoutKey();
	lua_pushnil(m_lpLuaEvrnt->luastate()); //TODO:把pushnil方法封装到stackprase里面
	if (_IsGlobal())
	{
		lua_setglobal(m_lpLuaEvrnt->luastate(), m_szName.c_str());
		lua_pop(m_lpLuaEvrnt->luastate(), 1);
	}
	else
		lua_settable(m_lpLuaEvrnt->luastate(), -3);
	_Pop();
}
