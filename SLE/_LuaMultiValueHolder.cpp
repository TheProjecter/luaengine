#include "StdAfx.h"
#include "_LuaMultiValueHolder.h"
#include "lua.hpp"
#include "luaenvironment.h"
#include "_LuaValueHolder.h"
#include "luatable.h"
using namespace sle;
_LuaMultiValueHolder::_LuaMultiValueHolder(luaenvironment *lpLuaEvrnt) :
	m_lparyLuaValueHolder(NULL)
{
	m_lpLuaEvrnt = lpLuaEvrnt;
}

_LuaMultiValueHolder::~_LuaMultiValueHolder(void)
{
	if (m_lparyLuaValueHolder)
	{
		for (int i = 0; i < MAX_RETURN_COUNT; ++i)
		{
			DELETE_POINTER(m_lparyLuaValueHolder[i]);
		}
		DELETE_ARRAY(m_lparyLuaValueHolder);
	}
}

void _LuaMultiValueHolder::_Init()
{
	m_lparyLuaValueHolder = new _LuaValueHolder*[m_nCount];
	for (int i = 0; i < m_nCount; ++i)
	{
		m_lparyLuaValueHolder[i] = new _LuaValueHolder(m_lpLuaEvrnt);
	}
}

void _LuaMultiValueHolder::_Refresh(int nCount)
{
	m_nCount = nCount;
	if (!m_lparyLuaValueHolder)
		_Init();
	for (int i = 0; i < m_nCount; ++i)
	{
		int _idx =m_nCount - i - 1;
		_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[_idx]);
		holder.setvalue(-1);
		lua_pop(m_lpLuaEvrnt->luastate(), 1);
	}
}

_LuaValueHolder& _LuaMultiValueHolder::operator[](int _idx)
{
	ASSERT(_idx <= m_nCount);
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[_idx - 1]);
	return holder;
}

_LuaMultiValueHolder::operator int()
{
	_LuaValueHolder &holder = *(m_lparyLuaValueHolder[0]);
	return holder;
}

_LuaMultiValueHolder::operator double()
{
	_LuaValueHolder &holder = *(m_lparyLuaValueHolder[0]);
	return holder;
}

_LuaMultiValueHolder::operator bool()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}

_LuaMultiValueHolder::operator const char*()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}

_LuaMultiValueHolder::operator luatable()
{
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[0]);
	return holder;
}
