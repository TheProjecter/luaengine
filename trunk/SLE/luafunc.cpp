/*******************************************************************************
* ��Ȩ����(C) Zhao Yu. �������ѭGPLЭ�顣
* �ļ����ƣ�luafunc.cpp
* �������ߣ�ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* �������ڣ�2009��08��17��
* �ļ���ʶ��8809F554-D91B-4092-8D5A-BDD6A7709365
* ����ժҪ��
*******************************************************************************/

#include "stdafx.h"
#include <lua.hpp>
#include "luaenvironment.h"
#include "_LuaStackPrase.h"
#include "_LuaValueHolder.h"
#include <string>

#include "luafunc.h"
#include "string.h"
#include <vector>
using namespace std;
using namespace sle;

luafunc::luafunc(luaenvironment *lpluaevt, const char *szName) :
	luaelement(lpluaevt, szName)
{

}
luafunc::~luafunc(void)
{
}
_LuaValueHolder& luafunc::_Call(int nargs, int nresults)
{
	clearerr();
	m_nErrCode = lua_pcall(m_lpLuaEvrnt->luastate(), nargs, nresults, 0);
	if (m_nErrCode)
	{
		m_szErrDesp = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
		m_lpLuaEvrnt->error(m_nErrCode, m_szErrDesp.c_str());
		m_lpValueHolder->clearvalue();
	}
	else
	{
		m_lpValueHolder->setvalue(m_lpStackPrase->get_type(-1), m_lpStackPrase->get_raw(-1), m_lpStackPrase->get_rawsize(-1));
		lua_pop(m_lpLuaEvrnt->luastate(), 1);
	}
	_Pop();
	return *m_lpValueHolder;
}

