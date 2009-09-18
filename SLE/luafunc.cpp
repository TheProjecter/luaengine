/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luafunc.cpp
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月17日
* GUID				：8809F554-D91B-4092-8D5A-BDD6A7709365
* Comments	：
*******************************************************************************/

#include "stdafx.h"
#include <lua.hpp>
#include "luaenvironment.h"
#include "_LuaStackPrase.h"
#include "_LuaValueHolder.h"
#include <string>
#include "luarets.h"
#include "luafunc.h"
#include "string.h"
#include <vector>
using namespace std;
using namespace sle;

luafunc::luafunc(luaenvironment *lpluaevt, const char *szName) :
	luaelement(lpluaevt, szName),
	m_lpLuarets(NULL)
{
	m_lpLuarets = new luarets(lpluaevt);
}
luafunc::luafunc(const luafunc &rhl) :
	luaelement(rhl),
	m_lpLuarets(NULL)
{
	_CopyObject(rhl);
}
luafunc& luafunc::operator=(const luafunc &rhl)
{
	_CopyObject(rhl);
	return *this;
}
void luafunc::_CopyObject(const luafunc &rhl)
{
	DELETE_POINTER(m_lpLuarets);
	//m_lpLuarets不需要复制，因为每次CallLua后，m_lpLuarets都会刷新
	m_lpLuarets = new luarets(rhl.m_lpLuaEvrnt);
	luaelement::_CopyObject(rhl);
}
luafunc::~luafunc(void)
{
	DELETE_POINTER(m_lpLuarets);
}
luarets& luafunc::_Call(int nargs, int nresults)
{
	clearerr();
	m_nErrCode = lua_pcall(m_lpLuaEvrnt->luastate(), nargs, MAX_RETURN_COUNT, 0);
	if (m_nErrCode)
	{
		m_szErrDesp = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
		m_lpLuaEvrnt->error(m_nErrCode, m_szErrDesp.c_str());
		m_lpValueHolder->clearvalue();
	}
	else
	{
		//m_lpValueHolder->setvalue(m_lpStackPrase->get_type(-1), m_lpStackPrase->get_raw(-1), m_lpStackPrase->get_rawsize(-1));
		//m_lpValueHolder->setvalue(-1);
		m_lpLuarets->refresh();
	}
	//之前_Push了函数地址，这里本应该掉_Pop，但是函数返回值已经在m_lpLuarets->refresh()中处理了，所以不用pop，直接设置0
	m_nPushCount = 0;
	//_Pop();
	return *m_lpLuarets;
}

