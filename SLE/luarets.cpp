#include "StdAfx.h"
#include "luarets.h"
#include "_LuaMultiValueHolder.h"
#include "_LuaValueHolder.h"
using namespace sle;
luarets::luarets(const _LuaMultiValueHolder &values)
{
	m_lpLuaMultiValueHolder = (_LuaMultiValueHolder*)(&values);
}

luarets::~luarets(void)
{
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
