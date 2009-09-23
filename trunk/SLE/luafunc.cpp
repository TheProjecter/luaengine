/*******************************************************************************
* File Header
* Filename		��luafunc.cpp
* Author			��ZhaoYu
* Create Time	��2009��08��17��
* GUID				��8809F554-D91B-4092-8D5A-BDD6A7709365
* Comments	��
*******************************************************************************/

#include "stdafx.h"
#include <lua.hpp>
#include "luaenvironment.h"
#include "_LuaMultiValueHolder.h"
#include "luafunc.h"
using namespace sle;

luafunc::luafunc(luaenvironment *lpluaevt, const char *szName) :
	luaelement(lpluaevt, szName),
	m_lpLuaMultiValueHolder(NULL),
	m_nRetCount(0)
{
	m_lpLuaMultiValueHolder = new _LuaMultiValueHolder(lpluaevt);
}
luafunc::luafunc(const luafunc &rhl) :
	luaelement(rhl),
	m_lpLuaMultiValueHolder(NULL)
{
	_CopyObject(rhl);
}
luafunc& luafunc::operator=(const luafunc &rhl)
{
	_CopyObject(rhl);
	return *this;
}
void luafunc::_CopyObject(const luafunc &rhl)
{
	DELETE_POINTER(m_lpLuaMultiValueHolder);
	//m_lpLuarets����Ҫ���ƣ���Ϊÿ��CallLua��m_lpLuarets����ˢ��
	m_lpLuaMultiValueHolder = new _LuaMultiValueHolder(rhl.m_lpLuaEvrnt);
	m_nRetCount = rhl.m_nRetCount;
	luaelement::_CopyObject(rhl);
}
luafunc::~luafunc(void)
{
	DELETE_POINTER(m_lpLuaMultiValueHolder);
}
_LuaMultiValueHolder& luafunc::_Call(int nargs, int nresults)
{
	clearerr();
	m_nErrCode = lua_pcall(m_lpLuaEvrnt->luastate(), nargs, m_nRetCount, 0);
	if (m_nErrCode)
	{
		m_szErrDesp = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
		m_lpLuaEvrnt->error(m_nErrCode, m_szErrDesp.c_str());
	}
	else
	{
		m_lpLuaMultiValueHolder->_Refresh(m_nRetCount);
	}
	//֮ǰ_Push�˺�����ַ�����ﱾӦ��_Pop�����Ǻ�������ֵ�Ѿ���m_lpLuarets->refresh()�д����ˣ����Բ���pop��ֱ������0
	//_Pop();
	m_nPushCount = 0;
	return *m_lpLuaMultiValueHolder;
}

