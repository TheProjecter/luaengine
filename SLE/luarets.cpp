#include "StdAfx.h"
#include "luarets.h"
#include "luatable.h"
#include "lua.hpp"
#include "_LuaMultiValueHolder.h"
#include "_LuaValueHolder.h"
using namespace sle;
luarets::luarets(const _LuaMultiValueHolder &values)
{
	m_lpLuaMultiValueHolder = (_LuaMultiValueHolder*)(&values);
}

luarets::~luarets(void)
{
	//DELETE_ARRAY(m_lparrySaveTarget);
}



void luarets::_Hold(int nCount, ...)
{/*
	for (int i = 0; i < nCount; ++i)
	{
		m_lpSaveTarget[i] = &arg##i
	}
*/
}

void luarets::_Get(int nCount, ...)
{/*#$%#$%
	va_list ap;
	va_start ( ap, nCount );
	for (int i= 0; i< nCount; ++i)
	{
		int t = va_arg (ap, int);
		if ( t > m )
		{
			m = t;
		}
	}
	va_end (ap);
*/
}


void luarets::operator=(const _LuaMultiValueHolder &rhl)
{
	m_lpLuaMultiValueHolder = (_LuaMultiValueHolder*)(&rhl);
	
}

_LuaValueHolder& luarets::operator[](int _idx)
{
	_LuaValueHolder &holder = m_lpLuaMultiValueHolder->operator[](_idx);
	return holder;
}
