/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luafunc.h
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月17日
* GUID				：4FDD0991-DCF4-48CA-93E0-1B2AE4300075
* Comments	：
*******************************************************************************/

#pragma once
#include "_Define.h"
#include "luaelement.h"
namespace sle
{
	#define PUSH_VALUE1 m_lpStackPrase->pushvalue(arg1);
	#define PUSH_VALUE2 PUSH_VALUE1 m_lpStackPrase->pushvalue(arg2);
	#define PUSH_VALUE3 PUSH_VALUE2 m_lpStackPrase->pushvalue(arg3);
	#define PUSH_VALUE4 PUSH_VALUE3 m_lpStackPrase->pushvalue(arg4);
	#define PUSH_VALUE5 PUSH_VALUE4 m_lpStackPrase->pushvalue(arg5);

	#define DECLARE_TYPENAME1 typename T1
	#define DECLARE_TYPENAME2 DECLARE_TYPENAME1, typename T2
	#define DECLARE_TYPENAME3 DECLARE_TYPENAME2, typename T3
	#define DECLARE_TYPENAME4 DECLARE_TYPENAME3, typename T4
	#define DECLARE_TYPENAME5 DECLARE_TYPENAME4, typename T5

	#define DECLARE_ARG1 T1 arg1
	#define DECLARE_ARG2 DECLARE_ARG1, T2 arg2
	#define DECLARE_ARG3 DECLARE_ARG2, T3 arg3
	#define DECLARE_ARG4 DECLARE_ARG3, T4 arg4
	#define DECLARE_ARG5 DECLARE_ARG4, T5 arg5

	#define DECLARE_INVOKE_METHOD(ARG_NUMBER) \
		template <DECLARE_TYPENAME##ARG_NUMBER> \
		_luarets& invoke(DECLARE_ARG##ARG_NUMBER) \
		{ \
			_Push(); \
			PUSH_VALUE##ARG_NUMBER \
			return _Call(ARG_NUMBER, 1); \
		} \
		template <DECLARE_TYPENAME##ARG_NUMBER> \
		_luarets& operator()(DECLARE_ARG##ARG_NUMBER) \
		{ \
			_Push(); \
			PUSH_VALUE##ARG_NUMBER \
			return _Call(ARG_NUMBER, 1); \
		}
	class _luarets;
	//////////////////////////////////////////////////////////////////////////
	class EXPORT_CLASS luafunc : public luaelement
	{
	public:
		luafunc(luaenvironment *lpluaevt, const char *szName);
		luafunc(const luafunc &rhl);
		luafunc& operator=(const luafunc &rhl);
		virtual ~luafunc(void);
	public:
		//没有参数的函数调用
		_luarets& invoke()
		{
			_Push();
			return _Call(0, 1);
		}
		_luarets& operator()()
		{
			return invoke();
		}
		DECLARE_INVOKE_METHOD(1)
		DECLARE_INVOKE_METHOD(2)
		DECLARE_INVOKE_METHOD(3)
		DECLARE_INVOKE_METHOD(4)
		DECLARE_INVOKE_METHOD(5)
	protected:
		virtual void _CopyObject(const luafunc &rhl);
		//调用函数，并处理错误
		virtual _luarets& _Call(int nargs, int nresults);
	protected:
		_luarets *m_lpLuarets;
	};
}
