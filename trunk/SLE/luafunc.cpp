/*******************************************************************************
* ��Ȩ����(C) �������ѭGPLЭ�顣
* Filename		��luafunc.cpp
* Author			��ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	��2009��08��17��
* GUID				��8809F554-D91B-4092-8D5A-BDD6A7709365
* Comments	��
*******************************************************************************/

#include "stdafx.h"
#include <lua.hpp>
#include "luaenvironment.h"
#include "_LuaStackPrase.h"
#include "_LuaValueHolder.h"
#include <string>
#include "luarets.h"
#include "luafunc.h"
#include "string.h"
#include <vector>
using namespace std;
using namespace sle;

luafunc::luafunc(luaenvironment *lpluaevt, const char *szName) :
	luaelement(lpluaevt, szName),
	m_lpLuarets(NULL)
{
	m_lpLuarets = new luarets(lpluaevt);
}
luafunc::luafunc(const luafunc &rhl) :
	luaelement(rhl),
	m_lpLuarets(NULL)
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
	DELETE_POINTER(m_lpLuarets);
	//m_lpLuarets����Ҫ���ƣ���Ϊÿ��CallLua��m_lpLuarets����ˢ��
	m_lpLuarets = new luarets(rhl.m_lpLuaEvrnt);
	luaelement::_CopyObject(rhl);
}
luafunc::~luafunc(void)
{
	DELETE_POINTER(m_lpLuarets);
}
luarets& luafunc::_Call(int nargs, int nresults)
{
	clearerr();
	m_nErrCode = lua_pcall(m_lpLuaEvrnt->luastate(), nargs, MAX_RETURN_COUNT, 0);
	if (m_nErrCode)
	{
		m_szErrDesp = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
		m_lpLuaEvrnt->error(m_nErrCode, m_szErrDesp.c_str());
		m_lpValueHolder->clearvalue();
	}
	else
	{
		//m_lpValueHolder->setvalue(m_lpStackPrase->get_type(-1), m_lpStackPrase->get_raw(-1), m_lpStackPrase->get_rawsize(-1));
		//m_lpValueHolder->setvalue(-1);
		m_lpLuarets->refresh();
	}
	//֮ǰ_Push�˺�����ַ�����ﱾӦ�õ�_Pop�����Ǻ�������ֵ�Ѿ���m_lpLuarets->refresh()�д����ˣ����Բ���pop��ֱ������0
	m_nPushCount = 0;
	//_Pop();
	return *m_lpLuarets;
}

