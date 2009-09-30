/*******************************************************************************
* File Header
* Filename		：luaelement.h
* Author			：ZhaoYu
* Create Time	：2009-08-20
* GUID				：3194A591-A506-4C08-AF6D-51D1AA388F2B
* Comments	：
*******************************************************************************/

#pragma once
#include "_Define.h"
#include <string>
namespace sle
{
	class luaenvironment;
	class _LuaStackPrase;
	class _LuaValueHolder;
	//NOT Thread safe, _PUSH涉及多次堆栈操作，要加堆栈锁
	class EXPORT_CLASS luaelement
	{
		//因为LuaStackPrase要使一个luaelement进栈，就必须调用PushMethod方法
		friend _LuaStackPrase;
	public:
		luaelement();
		luaelement(luaenvironment *lpLuaEvrnt, const char *szName);
		luaelement(const luaelement& rhl);
		virtual luaelement& operator=(const luaelement &rhl);
		virtual bool operator==(const luaelement &rhl) const;
		virtual ~luaelement(void);
	public:
		virtual int lasterr();
		virtual const char* lasterrdesp();
		virtual void clearerr();
		virtual int type();
		virtual bool nil();
		//检查当前域名是否合法，如果能正常push说明域名是合法的
		virtual bool verify();
		virtual const char *name();
		//reset this domain to nil
		virtual void setnil();
	protected:
		virtual void _CopyObject(const luaelement& rhl);
		virtual bool _Push();
		virtual void _Pop(int nExtraPop = 0);
		//这个push对域名的最后一个值（即key），不做rawget处理，因为要lua_settable
		virtual bool _PushWithoutKey();
		virtual bool _IsGlobal();
	protected:
		luaenvironment *m_lpLuaEvrnt;
		//完整的Lua名字，比如"T1.func1"，或者"tbTable.T1.x"
		std::string m_szName;
		//上次出错的代码
		int m_nErrCode;
		//上次出错的错误描述
		std::string m_szErrDesp;
		//保存一个lua值
		_LuaValueHolder* m_lpValueHolder;
		//lua堆栈解析器
		_LuaStackPrase* m_lpStackPrase;
		//指示上次push是否影响堆栈，及进栈的次数
		int m_nPushCount;
	};
}