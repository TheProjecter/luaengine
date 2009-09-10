/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luaelement.cpp
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月20日
* GUID				：0DC2837B-DA31-4CFB-8E42-D425BF022F46
* Comments	：
*******************************************************************************/

#include "StdAfx.h"
#include "luaelement.h"
#include "lua.hpp"
#include "luaenvironment.h"
#include "_LuaStackPrase.h"
#include "_LuaValueHolder.h"
using namespace sle;
#define CONSTRUCTOR_INIT \
	m_nErrCode(0), \
	m_szErrDesp(""), \
	m_lpStackPrase(NULL), \
	m_lpValueHolder(NULL)
//m_nPushCount(0), \

luaelement::luaelement(luaenvironment *lpLuaEvrnt, const char *szName) :
	CONSTRUCTOR_INIT
{
	m_lpLuaEvrnt = lpLuaEvrnt;
	m_szName = szName;
	m_lpStackPrase = new _LuaStackPrase(lpLuaEvrnt);
	m_lpValueHolder = new _LuaValueHolder();
}
luaelement::luaelement(const luaelement& rhl) :
	CONSTRUCTOR_INIT
{
	_CopyObject(rhl);
}
luaelement& luaelement::operator=(const luaelement& rhl)
{
	_CopyObject(rhl);
	return *this;
}
void luaelement::_CopyObject(const luaelement& rhl)
{
	DELETE_POINTER(m_lpStackPrase);
	DELETE_POINTER(m_lpValueHolder);
	m_lpLuaEvrnt = rhl.m_lpLuaEvrnt;
	m_nErrCode = rhl.m_nErrCode;
	m_szErrDesp = rhl.m_szErrDesp;
	m_szName = rhl.m_szName;
	//m_nPushCount = rhl.m_nPushCount;
	m_lpStackPrase = new _LuaStackPrase(*rhl.m_lpStackPrase);
	m_lpValueHolder = new _LuaValueHolder(*rhl.m_lpValueHolder);
}

luaelement::~luaelement(void)
{
	DELETE_POINTER(m_lpStackPrase);
	DELETE_POINTER(m_lpValueHolder);
	m_lpLuaEvrnt = NULL;
	//m_nPushCount = 0;
	m_szName.clear();
	clearerr();
}
int luaelement::lasterr()
{
	return m_nErrCode; 
}
const char* luaelement::lasterrdesp()
{
	return m_szErrDesp.c_str();
}
void luaelement::clearerr()
{
	m_nErrCode = 0;
	m_szErrDesp.clear();
}
int luaelement::type()
{
	int nType = LUA_TNONE;
	_Push();
	nType = m_lpStackPrase->get_type(-1);
	_Pop();
	return nType;
}
bool luaelement::nil()
{
	int nType = LUA_TNONE;
	_Push();
	nType = m_lpStackPrase->get_type(-1);
	_Pop();
	return nType == LUA_TNIL;
}
bool luaelement::verify()
{
	if (!_Push())
		return false;
	_Pop();
	return true;
}
const char* luaelement::name()
{
	return m_szName.c_str();
}

bool luaelement::_Push()
{
	//TODO 用strtok线程不安全，有空自己写个实时的split
	bool bRet = true;
	char *lpBuffer = new char[m_szName.size() + 1];
	strcpy(lpBuffer, m_szName.c_str());
	const char *szName = strtok(lpBuffer, ".");
	if (szName != NULL)
		lua_getglobal(m_lpLuaEvrnt->luastate(), szName);
	//m_nPushCount = 0;
	while ((szName = strtok(NULL, ".")) != NULL)
	{
		int nKey = atoi(szName);
		if (nKey > 0 || strcmp(szName, "0") == 0)
			lua_pushinteger(m_lpLuaEvrnt->luastate(), nKey);
		else
			lua_pushstring(m_lpLuaEvrnt->luastate(), szName);
		int nType = m_lpStackPrase->get_type(-2);
		//这里要判断，域名中间的某级为nil，说明当前域名是无效的，比如T1.T2.T3，而T2是nil，则无效
		//如果Push失败，恢复堆栈原状
		if (nType == LUA_TNIL)
		{
			bRet = false;
			_Pop();
			break;
		}
		lua_rawget(m_lpLuaEvrnt->luastate(), -2);
		lua_remove(m_lpLuaEvrnt->luastate(), -2);
	}
	DELETE_POINTER(lpBuffer);
	return bRet;
}
void luaelement::_Pop(int nExtraPop)
{
	lua_pop(m_lpLuaEvrnt->luastate(), 1 + nExtraPop);
}
bool luaelement::_IsGlobal()
{
	int pos = m_szName.find('.');
	return pos < 0;
}
void luaelement::clear()
{
	_Push();
	lua_pushnil(m_lpLuaEvrnt->luastate()); //TODO:把pushnil方法封装到stackprase里面
	if (_IsGlobal())
	{
		lua_setglobal(m_lpLuaEvrnt->luastate(), m_szName.c_str());
		lua_pop(m_lpLuaEvrnt->luastate(), 1);
	}
	else
		lua_settable(m_lpLuaEvrnt->luastate(), -3);
	_Pop();
}
