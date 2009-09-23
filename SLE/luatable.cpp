/*******************************************************************************
* File Header
* Filename		£ºluatable.cpp
* Author			£ºZhaoYu
* Create Time	£º2009Äê08ÔÂ17ÈÕ
* GUID				£º7AD51E0F-23A2-4D47-A36E-B48F927F5E04
* Comments	£º
*******************************************************************************/

#include "StdAfx.h"
#include "luatable.h"
#include "luaenvironment.h"
#include "_LuaValueHolder.h"
#include "_LuaStackPrase.h"
#include "luavar.h"
#include <string>
#include "lua.hpp"
#define aux_getn(L,n)	(luaL_checktype(L, n, LUA_TTABLE), luaL_getn(L, n))
using namespace sle;
using namespace std;

luatable::luatable()
{

}
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
	CHECK_POINTER(m_lpLuaEvrnt);
	char szBuf[255];
	itoa((int)_idx, szBuf, 10);
	string szName = m_szName;
	szName.append(".");
	szName.append(szBuf);
	luavar var = m_lpLuaEvrnt->variable(szName.c_str());
	return var;
}
luavar luatable::operator[](const char* _k)
{
	CHECK_POINTER(m_lpLuaEvrnt);
	string szName = m_szName;
	szName.append(".");
	szName.append(_k);
	luavar var = m_lpLuaEvrnt->variable(szName.c_str());
	return var;
}
int luatable::_GetFirstEmptyPos()
{
	_Push();
	int pos = aux_getn(m_lpLuaEvrnt->luastate(), 1) + 1;  /* first empty element */
	_Pop();
	return pos;
}