/*******************************************************************************
* ��Ȩ����(C) Zhao Yu. �������ѭGPLЭ�顣
* �ļ����ƣ�luavar.cpp
* �������ߣ�ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* �������ڣ�2009��08��20��
* �ļ���ʶ��B2ABD955-30D0-4B7F-A072-A36FD51303FC
* ����ժҪ��
*******************************************************************************/

#include "StdAfx.h"
#include "luavar.h"
#include "_LuaValueHolder.h"

using namespace sle;

luavar::luavar(luaenvironment *lpLuaEvrnt, const char *szName) :
	luaelement(lpLuaEvrnt, szName)
{
}

luavar::~luavar(void)
{
}
bool luavar::_PushWithoutKey()
{
	//TODO ��strtok�̲߳���ȫ���п��Լ�д��ʵʱ��split
	bool bRet = true;
	char *lpBuffer = new char[m_szName.size() + 1];
	strcpy(lpBuffer, m_szName.c_str());
	const char *szName = strtok(lpBuffer, ".");
	if (szName != NULL)
		lua_getglobal(m_lpLuaEvrnt->luastate(), szName);
	m_nPushCount = 0;
	while ((szName = strtok(NULL, ".")) != NULL)
	{
		if (m_nPushCount != 0)
		{
			int nType = m_lpStackPrase->get_type(-2);
			//����Ҫ�жϣ������м��ĳ��Ϊnil��˵����ǰ��������Ч�ģ�����T1.T2.T3����T2��nil������Ч
			//���Pushʧ�ܣ��ָ���ջԭ״
			if (nType == LUA_TNIL)
			{
				_Pop();
				bRet = false;
				break;
			}
			lua_rawget(m_lpLuaEvrnt->luastate(), -2);
		}
		++m_nPushCount;
		int nKey = atoi(szName);
		if (nKey > 0)
			lua_pushinteger(m_lpLuaEvrnt->luastate(), nKey);
		else
			lua_pushstring(m_lpLuaEvrnt->luastate(), szName);
	}
	DELETE_POINTER(lpBuffer);
	return bRet;
}
luavar::operator int()
{
	_Push();
	int nType = m_lpStackPrase->get_type(-1);
	ASSERT(nType == LUA_TNUMBER);
	double dValue = lua_tonumber(m_lpLuaEvrnt->luastate(), -1);
	_Pop();
	lua_pop(m_lpLuaEvrnt->luastate(), 1);
	return (int)dValue;
}
luavar::operator double()
{
	_Push();
	int nType = m_lpStackPrase->get_type(-1);
	ASSERT(nType == LUA_TNUMBER);
	double dValue = lua_tonumber(m_lpLuaEvrnt->luastate(), -1);
	_Pop();
	lua_pop(m_lpLuaEvrnt->luastate(), 1);
	return dValue;
}
luavar::operator bool()
{
	_Push();
	int nType = m_lpStackPrase->get_type(-1);
	ASSERT(nType == LUA_TBOOLEAN);
	int bValue = lua_toboolean(m_lpLuaEvrnt->luastate(), -1);
	_Pop();
	lua_pop(m_lpLuaEvrnt->luastate(), 1);
	return bValue != 0;
}
luavar::operator const char*()
{
	_LuaValueHolder vHolder;
	_Push();
	const char *szValue = lua_tostring(m_lpLuaEvrnt->luastate(), -1);
	vHolder.setvalue(LUA_TNUMBER, szValue, strlen(szValue) + 1);
	_Pop();
	lua_pop(m_lpLuaEvrnt->luastate(), 1);
	return vHolder;
}
