/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luaenvironment.h
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
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
	class _TempTableManager;
	//线程安全
	class EXPORT_CLASS luaenvironment
	{
		friend luaelement;
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
		virtual luafunc func(const char *szName);
		virtual luatable table(const char *szName);
		virtual luavar variable(const char *szName);
		virtual luatable newtable(const char *szName);
		virtual luatable newtable();
		virtual int gettop() const;
		//virtual int __IncTabRef(const char *szName);
		//virtual int __DecTabRef(const char *szName);

		virtual void _SetGlobal(const char *lpszName) const;
		virtual void _SetTable(int _idx) const;

	protected:
		int m_nErrCode;
		const char *m_nErrDesp;
		lua_State *m_lpLuaState;
		//_TempTableManager *m_lpTempTableManager;
	};
}