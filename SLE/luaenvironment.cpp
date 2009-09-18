/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luaenvironment.cpp
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月17日
* GUID				：BE34DB74-4F6D-419C-B377-961CD4E9B103
* Comments	：
*******************************************************************************/

#include "StdAfx.h"
#include "luaenvironment.h"
#include <lua.hpp>
#include "luaelement.h"
#include "luafunc.h"
#include "luatable.h"
#include "luavar.h"
#include "_TempTableManager.h"
using namespace sle;

luaenvironment::luaenvironment(void) :
	m_lpLuaState(NULL)
{
}

luaenvironment::~luaenvironment(void)
{
}
bool luaenvironment::init()
{
	int error;
	m_lpLuaState = lua_open();
	error = luaopen_base(m_lpLuaState);
	luaL_openlibs(m_lpLuaState);
	lua_settop(m_lpLuaState, 0);
	return error == 0;
}
bool luaenvironment::dofile(const char *szFilename)
{
	return 	luaL_dofile(m_lpLuaState, szFilename);
}
bool luaenvironment::dostring(const char *szSource)
{
	return luaL_dostring(m_lpLuaState, szSource);
}
lua_State* luaenvironment::luastate()
{
	return m_lpLuaState;
}
luafunc luaenvironment::func(const char *szName)
{
	luafunc func(this, szName);
	int nType = func.type();
	ASSERT(nType == LUA_TFUNCTION);
	return func;
}
luaelement luaenvironment::element(const char *szName)
{
	luaelement element(this, szName);
	int nType = element.type();
	ASSERT(!element.nil());
	return element;
}
luatable luaenvironment::table(const char *szName)
{
	luatable table(this, szName);
	int nType = table.type();
	ASSERT(nType == LUA_TTABLE);
	return table;
}
luatable luaenvironment::newtable(const char *szName)
{
	luatable tbTmp = newtable();
	luavar var(this, szName);
	var = tbTmp;
	luatable table(this, szName);
	tbTmp.setnil();
	return table;
}
luatable luaenvironment::newtable()
{
	char szName[255] = {0};
	_GenerateTempName(szName, 255);
	lua_newtable(m_lpLuaState);
	lua_setglobal(m_lpLuaState, szName);
	luatable table(this, szName);
	return table;
}
luavar luaenvironment::variable(const char *szName)
{
	luavar var(this, szName);
	int nType = LUA_TNONE;
	if (!var.verify())
		ASSERT(false);
	return var;
}
void luaenvironment::error(int nCode, const char* szDesp)
{

}
int luaenvironment::__IncTabRef(const char *szName)
{
	return m_lpTempTableManager->increase(szName);
}
int luaenvironment::__DecTabRef(const char *szName)
{
	return m_lpTempTableManager->increase(szName);
}
int luaenvironment::gettop()
{
	return lua_gettop(m_lpLuaState);
}
void luaenvironment::_SetGlobal(const char *lpszName)
{
	lua_setglobal(m_lpLuaState, lpszName);
}
void luaenvironment::_SetTable(int _idx)
{
	lua_settable(m_lpLuaState, _idx);
}
