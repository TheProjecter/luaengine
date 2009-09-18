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

#include "luafunc.h"
#include "string.h"
#include <vector>
using namespace std;
using namespace sle;

luafunc::luafunc(luaenvironment *lpluaevt, const char *szName) :
	luaelement(lpluaevt, szName)
{

}
luafunc::~luafunc(void)
{
}
_LuaValueHolder& luafunc::_Call(int nargs, int nresults)
{
	clearerr();
	m_nErrCode = lua_pcall(m_lpLuaEvrnt->luastate(), nargs, nresults, 0);
	if (m_nErrCode)
	{
		m_szErrDesp = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
		m_lpLuaEvrnt->error(m_nErrCode, m_szErrDesp.c_str());
		m_lpValueHolder->clearvalue();
	}
	else
	{
		//m_lpValueHolder->setvalue(m_lpStackPrase->get_type(-1), m_lpStackPrase->get_raw(-1), m_lpStackPrase->get_rawsize(-1));
		m_lpValueHolder->setvalue(-1);
	}
	_Pop();
	return *m_lpValueHolder;
}

