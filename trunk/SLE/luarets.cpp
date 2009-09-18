#include "StdAfx.h"
#include "luarets.h"
#include "luatable.h"
#include "luaenvironment.h"
#include "_LuaValueHolder.h"
#include "lua.hpp"
using namespace sle;
_luarets::_luarets(luaenvironment *lpLuaEvrnt) :
	m_lpLuaEvrnt(NULL),
	m_lparyLuaValueHolder(NULL)
{
	m_lpLuaEvrnt = lpLuaEvrnt;
}

_luarets::~_luarets(void)
{
	if (m_lparyLuaValueHolder)
	{
		for (int i = 0; i < MAX_RETURN_COUNT; ++i)
		{
			DELETE_POINTER(m_lparyLuaValueHolder[i]);
		}
		delete[] m_lparyLuaValueHolder;
		m_lparyLuaValueHolder = NULL;
	}
}

void _luarets::_Init()
{
	m_lparyLuaValueHolder = new _LuaValueHolder*[MAX_RETURN_COUNT];
	for (int i = 0; i < MAX_RETURN_COUNT; ++i)
	{
		m_lparyLuaValueHolder[i] = new _LuaValueHolder(m_lpLuaEvrnt);
	}
}

void _luarets::refresh()
{
	if (!m_lparyLuaValueHolder)
		_Init();
	int n = m_lpLuaEvrnt->gettop();
	for (int i = 0; i < MAX_RETURN_COUNT; ++i)
	{
		int _idx =MAX_RETURN_COUNT - i - 1;
		_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[_idx]);
		holder.setvalue(-1);
		lua_pop(m_lpLuaEvrnt->luastate(), 1);
		 n = m_lpLuaEvrnt->gettop();
	}
}

_LuaValueHolder& _luarets::operator[](int _idx)
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[_idx - 1]);
	return holder;
}

_luarets::operator int()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}

_luarets::operator double()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}

_luarets::operator bool()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}

_luarets::operator const char*()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}

_luarets::operator luatable()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}
