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
using namespace sle;
int luaenvironment::s_nTempTableId = 0;

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
	tbTmp.clear();
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
	/*
	nType = var.type();
	ASSERT(nType == LUA_TNIL || nType == LUA_TNUMBER || nType == LUA_TSTRING || nType == LUA_TBOOLEAN);
	*/
	return var;
}
void luaenvironment::error(int nCode, const char* szDesp)
{

}
void luaenvironment::_GenerateTempName(char * lpBuf, int nSize)
{
	sprintf_s(lpBuf, nSize, "sletemptb%d%d", rand()*10000, s_nTempTableId++);
}
