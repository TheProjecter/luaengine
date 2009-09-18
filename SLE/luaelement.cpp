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
	m_lpValueHolder(NULL), \
	m_nPushCount(0)

luaelement::luaelement(luaenvironment *lpLuaEvrnt, const char *szName) :
	CONSTRUCTOR_INIT
{
	m_lpLuaEvrnt = lpLuaEvrnt;
	m_szName = szName;
	m_lpStackPrase = new _LuaStackPrase(lpLuaEvrnt);
	m_lpValueHolder = new _LuaValueHolder(lpLuaEvrnt);
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
bool luaelement::operator==(const luaelement &rhl) const
{
	return false;
}
void luaelement::_CopyObject(const luaelement& rhl)
{
	DELETE_POINTER(m_lpStackPrase);
	DELETE_POINTER(m_lpValueHolder);
	m_lpLuaEvrnt = rhl.m_lpLuaEvrnt;
	m_nErrCode = rhl.m_nErrCode;
	m_szErrDesp = rhl.m_szErrDesp;
	m_szName = rhl.m_szName;
	m_nPushCount = rhl.m_nPushCount;
	m_lpStackPrase = new _LuaStackPrase(*rhl.m_lpStackPrase);
	m_lpValueHolder = new _LuaValueHolder(*rhl.m_lpValueHolder);
}

luaelement::~luaelement(void)
{
	DELETE_POINTER(m_lpStackPrase);
	DELETE_POINTER(m_lpValueHolder);
	m_lpLuaEvrnt = NULL;
	m_nPushCount = 0;
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
	//push和pop必须成对出现，如果之前有push，则不能再push
	 RETURN_ON_FAIL(m_nPushCount == 0);
	//TODO 用strtok线程不安全，有空自己写个实时的split
	bool bRet = true;
	char *lpBuffer = new char[m_szName.size() + 1];
	strcpy(lpBuffer, m_szName.c_str());
	const char *szName = strtok(lpBuffer, ".");
	if (szName != NULL)
		lua_getglobal(m_lpLuaEvrnt->luastate(), szName);
	m_nPushCount++;
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

bool luaelement::_PushWithoutKey()
{
	//push和pop必须成对出现，如果之前有push，则不能再push
	RETURN_ON_FAIL(m_nPushCount == 0);
	//TODO 用strtok线程不安全，有空自己写个实时的split
	bool bRet = true;
	bool bPushed = false;
	char *lpBuffer = new char[m_szName.size() + 1];
	strcpy(lpBuffer, m_szName.c_str());
	const char *szName = strtok(lpBuffer, ".");
	if (szName != NULL)
		lua_getglobal(m_lpLuaEvrnt->luastate(), szName);
	m_nPushCount++;
	bool bFirst = true;
	while ((szName = strtok(NULL, ".")) != NULL)
	{
		if (!bFirst)
		{
			int nType = m_lpStackPrase->get_type(-2);
			//这里要判断，域名中间的某级为nil，说明当前域名是无效的，比如T1.T2.T3，而T2是nil，则无效
			//如果Push失败，恢复堆栈原状
			if (nType == LUA_TNIL)
			{
				_Pop();
				bRet = false;
				break;
			}
			lua_rawget(m_lpLuaEvrnt->luastate(), -2);
			lua_remove(m_lpLuaEvrnt->luastate(), -2);
		}
		//++m_nPushCount;
		bFirst = false;
		int nKey = atoi(szName);
		if (nKey > 0)
			lua_pushinteger(m_lpLuaEvrnt->luastate(), nKey);
		else
			lua_pushstring(m_lpLuaEvrnt->luastate(), szName);
	}
	DELETE_POINTER(lpBuffer);
	return bRet;
}

void luaelement::_Pop(int nExtraPop)
{
	lua_pop(m_lpLuaEvrnt->luastate(), m_nPushCount + nExtraPop);
	m_nPushCount = 0;
}

bool luaelement::_IsGlobal()
{
	int pos = (int)m_szName.find('.');
	return pos < 0;
}

void luaelement::setnil()
{
	if (!verify())
		return;
	if (nil())
		return;
	_PushWithoutKey();
	lua_pushnil(m_lpLuaEvrnt->luastate()); //TODO:把pushnil方法封装到stackprase里面
	if (_IsGlobal())
	{
		m_lpLuaEvrnt->_SetGlobal(m_szName.c_str());
	}
	else
	{
		m_lpLuaEvrnt->_SetTable(-3);
	}
	_Pop();
}
