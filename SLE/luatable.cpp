/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luatable.cpp
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月17日
* GUID				：7AD51E0F-23A2-4D47-A36E-B48F927F5E04
* Comments	：
*******************************************************************************/

#include "StdAfx.h"
#include "luatable.h"
#include "luaenvironment.h"
#include "_LuaValueHolder.h"
#include "_LuaStackPrase.h"
#include "luavar.h"
#include <string>
#include "lua.hpp"
using namespace sle;
using namespace std;
luatable::luatable(luaenvironment *lpLuaEvrnt, const char *szName) :
	luaelement(lpLuaEvrnt, szName)
{

}

luatable::~luatable(void)
{
}

_LuaValueHolder& luatable::getvalue(size_t _idx)
{
	_Push();
	lua_pushinteger(m_lpLuaEvrnt->luastate(), _idx);
	lua_gettable(m_lpLuaEvrnt->luastate(), -2);
	//m_lpValueHolder->setvalue(m_lpStackPrase->get_type(-1), m_lpStackPrase->get_raw(-1), m_lpStackPrase->get_rawsize(-1));
	m_lpValueHolder->setvalue(-1);
	_Pop(1);
	return *m_lpValueHolder;
}
_LuaValueHolder& luatable::getvalue(const char *_k)
{
	_Push();
	lua_pushstring(m_lpLuaEvrnt->luastate(), _k);
	lua_gettable(m_lpLuaEvrnt->luastate(), -2);
	//m_lpValueHolder->setvalue(m_lpStackPrase->get_type(-1), m_lpStackPrase->get_raw(-1), m_lpStackPrase->get_rawsize(-1));
	m_lpValueHolder->setvalue(-1);
	_Pop(1);
	return *m_lpValueHolder;
}
luavar luatable::operator[](size_t _idx)
{
	char szBuf[255];
	itoa((int)_idx, szBuf, 10);
	std::string szName = m_szName;
	szName.append(".");
	szName.append(szBuf);
	luavar var = m_lpLuaEvrnt->variable(szName.c_str());
	return var;
}
luavar luatable::operator[](const char* _k)
{
	std::string szName = m_szName;
	szName.append(".");
	szName.append(_k);
	luavar var = m_lpLuaEvrnt->variable(szName.c_str());
	return var;
}