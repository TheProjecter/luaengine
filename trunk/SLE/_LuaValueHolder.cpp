/*******************************************************************************
* File Header
* Filename		：LuaValueHolder.cpp
* Author			：ZhaoYu
* Create Time	：2009年08月17日
* GUID				：FD175154-7265-43CB-A2E4-F7739CBCD8B0
* Comments	：
*******************************************************************************/

#include "StdAfx.h"
#include "_LuaValueHolder.h"
#include "_LuaStackPrase.h"
#include "luaenvironment.h"
#include "lua.hpp"
#include "luatable.h"
#include "string.h"
using namespace sle;
_LuaValueHolder::_LuaValueHolder(luaenvironment *lpLuaEvrnt) :
	m_nType(LUA_TNONE), m_lpBuffer(NULL), m_nSize(0), m_lpLuaEvrnt(lpLuaEvrnt), m_bTemp(false)
{
}

_LuaValueHolder::~_LuaValueHolder(void)
{
	clearvalue();
}

_LuaValueHolder::_LuaValueHolder(const _LuaValueHolder &rhl)
	: m_nType(LUA_TNONE), m_lpBuffer(NULL), m_nSize(0)
{
	_CopyObject(rhl);
}

_LuaValueHolder& _LuaValueHolder::operator=(const _LuaValueHolder &rhl)
{
	_CopyObject(rhl);
	return *this;
}

void _LuaValueHolder::_CopyObject(const _LuaValueHolder &rhl)
{
	m_lpLuaEvrnt = rhl.m_lpLuaEvrnt;
	//这里不能复制m_bTemp，如果复制了，目标对象析构时，临时table就会delete
	//temp对象只有当创建者析构时，才能删除
	//m_bTemp = m_bTemp;
	setvalue(rhl.m_nType, rhl.m_lpBuffer, rhl.m_nSize);
}

void _LuaValueHolder::clearvalue()
{
	if (m_nType == LUA_TTABLE && m_bTemp)
	{
		luatable table(m_lpLuaEvrnt, (const char*)m_lpBuffer);
		table.setnil();
	}
	m_bTemp = false;
	m_nType = LUA_TNONE;
	DELETE_POINTER(m_lpBuffer);
	m_nSize = 0;
}
int _LuaValueHolder::type()
{
	return m_nType;
}
_LuaValueHolder::operator int()
{
	if (m_nType == LUA_TNONE)
		return 0;
	if (m_nType != LUA_TNUMBER)
		ASSERT(false);
	return (int)(*(double*)m_lpBuffer);
}

_LuaValueHolder::operator double()
{
	if (m_nType == LUA_TNONE)
		return 0.0f;
	if (m_nType != LUA_TNUMBER)
		ASSERT(false);
	return *(double*)m_lpBuffer;
}

_LuaValueHolder::operator bool()
{
	if (m_nType == LUA_TNONE)
		return false;
	if (m_nType != LUA_TBOOLEAN)
		ASSERT(false);	
	return *(bool*)m_lpBuffer;
}

_LuaValueHolder::operator const char*()
{
	if (m_nType == LUA_TNONE)
		return NULL;
	if (m_nType != LUA_TSTRING)
		ASSERT(false);
	return (const char*)m_lpBuffer;
}

_LuaValueHolder::operator luatable()
{
	if (m_nType == LUA_TNONE)
		ASSERT(false);
	if (m_nType != LUA_TTABLE)
		ASSERT(false);
	luatable table(m_lpLuaEvrnt, (const char*)m_lpBuffer);
	return table;
}

void _LuaValueHolder::setvalue(int nStackDeep)
{
	_LuaStackPrase sp(m_lpLuaEvrnt);
	int nType = sp.get_type(nStackDeep);
	switch(nType)
	{
	case LUA_TTABLE:
		_SetTable(nStackDeep);
		break;
	case LUA_TNUMBER:
		setvalue(nType, sp.get_raw(nStackDeep), sp.get_rawsize(nStackDeep));
		break;
	case LUA_TSTRING:
		setvalue(nType, sp.get_raw(nStackDeep), sp.get_rawsize(nStackDeep));
		break;
	case LUA_TBOOLEAN:
		setvalue(nType, sp.get_raw(nStackDeep), sp.get_rawsize(nStackDeep));
		break;
	case LUA_TNIL:
		setvalue(nType, (void*)NULL, 0);
	};
}

bool _LuaValueHolder::_SetTable(int nDeep)
{
	RETURN_ON_FAIL(nDeep == -1);
	char szName[255] = {0};
	_GenerateTempName(szName, 255);
	lua_setglobal(m_lpLuaEvrnt->luastate(), szName);
	lua_getglobal(m_lpLuaEvrnt->luastate(), szName);
	setvalue(LUA_TTABLE, (char*)szName, strlen(szName) + 1);
	m_bTemp = true;
	return true;
}
