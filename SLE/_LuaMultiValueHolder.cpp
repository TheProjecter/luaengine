/*******************************************************************************
* File Header
* Filename		£º_LuaMultiValueHolder.cpp
* Author			£ºZhaoYu
* Create Time £º2009-09-23 16:25:38
* GUID				£ºC0E45520-C7C3-4E49-8CB8-DA0076507675
* Comments	£º
*******************************************************************************/

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
		for (int i = 0; i < m_nCount; ++i)
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
	_LuaValueHolder &holder = 	*(m_lparyLuaValueHolder[_idx]);
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
