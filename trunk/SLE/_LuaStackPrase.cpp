/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：LuaStackPrase.cpp
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月17日
* GUID				：93D66506-73B4-49EE-B530-D539D0CD2DD8
* Comments	：
*******************************************************************************/
#include "StdAfx.h"
#include "lua.hpp"
#include "_LuaStackPrase.h"
#include "luaenvironment.h"
#include "luavar.h"
using namespace sle;

_LuaStackPrase::_LuaStackPrase(luaenvironment *lpLuaEvrnt)
	: m_lpLuaEvrnt(lpLuaEvrnt), m_lpBuffer(NULL), m_bAlloced(false), m_nSize(0)
{
}
_LuaStackPrase::_LuaStackPrase(const _LuaStackPrase& rhl)
{
	_CopyObject(rhl);
}
_LuaStackPrase& _LuaStackPrase::operator =(const _LuaStackPrase& rhl)
{
	_CopyObject(rhl);
	return *this;
}

_LuaStackPrase::~_LuaStackPrase(void)
{
	_ClearBuffer();
}
const void* _LuaStackPrase::get_raw(int _idx)
{
	_ClearBuffer();
	int nType = lua_type(m_lpLuaEvrnt->luastate(), _idx);
	switch (nType)
	{
	case LUA_TNUMBER:
	{
		LUA_NUMBER n = lua_tonumber(m_lpLuaEvrnt->luastate(), _idx);
		m_lpBuffer = _CopyPointer(&n, get_rawsize(_idx));
		break;
	}
	case LUA_TSTRING:
	{
		m_lpBuffer = (void*)lua_tostring(m_lpLuaEvrnt->luastate(), _idx);
		break;
	}
	default:
		ASSERT(false);
	}
	return m_lpBuffer;
}
size_t _LuaStackPrase::get_rawsize(int _idx)
{
	int nType = lua_type(m_lpLuaEvrnt->luastate(), _idx);
	size_t nSize = 0;
	switch (nType)
	{
	case LUA_TNUMBER:
		nSize = sizeof(LUA_NUMBER);
		break;
	case LUA_TSTRING:
		nSize = lua_strlen(m_lpLuaEvrnt->luastate(), _idx) + 1;
		break;
	default:
		ASSERT(false);
	}
	return nSize;
}
int _LuaStackPrase::get_type(int _idx)
{
	return lua_type(m_lpLuaEvrnt->luastate(), _idx);
}
void _LuaStackPrase::_ClearBuffer()
{
	if (m_bAlloced)
	{
		DELETE_POINTER(m_lpBuffer);
		m_nSize = 0;
		m_bAlloced = false;
	}
}
void* _LuaStackPrase::_CopyPointer(const void *lpsrc, size_t nsize)
{
	m_bAlloced = true;
	m_nSize = nsize;
	return _copypointer(lpsrc, nsize);
}
void _LuaStackPrase::_CopyObject(const _LuaStackPrase &rhl)
{
	m_bAlloced = rhl.m_bAlloced;
	m_nSize = rhl.m_nSize;
	if (m_bAlloced)
		m_lpBuffer =  _CopyPointer(rhl.m_lpBuffer, m_nSize);
	else
		m_lpBuffer = rhl.m_lpBuffer;
	m_lpLuaEvrnt = rhl.m_lpLuaEvrnt;
}
void _LuaStackPrase::pushvalue(int _v)
{
	lua_pushinteger(m_lpLuaEvrnt->luastate(), _v);
}
void _LuaStackPrase::pushvalue(double _v)
{
	lua_pushnumber(m_lpLuaEvrnt->luastate(), _v);
}
void _LuaStackPrase::pushvalue(const char *lpstr)
{
	lua_pushstring(m_lpLuaEvrnt->luastate(), lpstr);
}
void _LuaStackPrase::pushvalue(bool _v)
{
	lua_pushboolean(m_lpLuaEvrnt->luastate(), _v);
}
void _LuaStackPrase::pushvalue(luaelement& _v)
{
	_v._Push();
}