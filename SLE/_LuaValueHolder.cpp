/*******************************************************************************
* 版权所有(C) Zhao Yu. 本软件遵循GPL协议。
* 文件名称：LuaValueHolder.cpp
* 作　　者：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* 创建日期：2009年08月17日
* 文件标识：FD175154-7265-43CB-A2E4-F7739CBCD8B0
* 内容摘要：
*******************************************************************************/

#include "StdAfx.h"
#include "_LuaValueHolder.h"
#include "lua.hpp"
using namespace sle;
_LuaValueHolder::_LuaValueHolder(void) :
	m_nType(LUA_TNONE), m_lpBuffer(NULL), m_nSize(0)
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
	clearvalue();
	_CopyObject(rhl);
	return *this;
}

void _LuaValueHolder::_CopyObject(const _LuaValueHolder &rhl)
{
	setvalue(rhl.m_nType, rhl.m_lpBuffer, rhl.m_nSize);
}

void _LuaValueHolder::clearvalue()
{
	m_nType = LUA_TNONE;
	DELETE_POINTER(m_lpBuffer);
	m_nSize = 0;
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