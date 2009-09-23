/*******************************************************************************
* File Header
* Filename		：luaenvironment.h
* Author			：ZhaoYu
* Create Time	：2009年08月17日
* GUID				：FE8AAFB7-2ADF-47FB-9581-A7A85A29C342
* Comments	：
*******************************************************************************/

#pragma once
#include "_Define.h"
struct lua_State;

namespace sle
{
	class luafunc;
	class luatable;
	class luavar;
	class luaelement;
	class _LuaStackPrase;
	//线程安全
	class EXPORT_CLASS luaenvironment
	{
		friend luaelement;
		friend luatable;
		friend luavar;
	public:
		luaenvironment(void);
		virtual bool operator==(const luaenvironment &rhl) const;
		virtual ~luaenvironment(void);
	private:
		virtual luaenvironment& operator=(const luaenvironment &rhl);
	public:
		virtual bool init();
		virtual bool close();
		virtual bool dofile(const char *szFilename) const;
		virtual bool dostring(const char *szSource) const;
		virtual lua_State *luastate() const;
		//每当出错，都会回调到这里
		virtual void error(int nCode, const char* szDesp);
		virtual luaelement element(const char *szName);
		virtual luafunc func(const char *szName, int nReturns = 1);
		virtual luatable table(const char *szName);
		virtual luavar variable(const char *szName);
		virtual luatable newtable(const char *szName);
		virtual luatable newtable();
		virtual int gettop() const;
		DECLARE_PROPERTY_GET(_LuaStackPrase*, m_lpStackPrase, _GetStackPrase);
	protected:
		virtual void _SetGlobal(const char *lpszName) const;
		virtual void _SetTable(int _idx) const;

	protected:
		int m_nErrCode;
		const char *m_nErrDesp;
		lua_State *m_lpLuaState;
		//lua堆栈解析器
		_LuaStackPrase* m_lpStackPrase;
	};
}