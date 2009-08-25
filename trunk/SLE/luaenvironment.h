/*******************************************************************************
* 版权所有(C) Zhao Yu. 本软件遵循GPL协议。
* 文件名称：luaenvironment.h
* 作　　者：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* 创建日期：2009年08月17日
* 文件标识：FE8AAFB7-2ADF-47FB-9581-A7A85A29C342
* 内容摘要：
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
	//线程安全
	class EXPORT_CLASS luaenvironment
	{
	public:
		luaenvironment(void);
		virtual ~luaenvironment(void);
	public:
		virtual bool init();
		virtual bool dofile(const char *szFilename);
		virtual bool dostring(const char *szSource);
		virtual lua_State *luastate();
		//每当出错，都会回调到这里
		virtual void error(int nCode, const char* szDesp);
		virtual luaelement element(const char *szName);
		virtual luafunc func(const char *szName);
		virtual luatable table(const char *szName);
		virtual luavar variable(const char *szName);
		virtual luatable newtable(const char *szName);
	protected:
		int m_nErrCode;
		const char *m_nErrDesp;
		lua_State *m_lpLuaState;
	};
}