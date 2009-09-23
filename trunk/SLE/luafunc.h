/*******************************************************************************
* File Header
* Filename		：luafunc.h
* Author			：ZhaoYu
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

	#define DECLARE_INVOKE_METHOD(ARG_NUMBER) \
		template <DECLARE_TYPENAME##ARG_NUMBER> \
		_LuaMultiValueHolder& invoke(DECLARE_ARG##ARG_NUMBER) \
		{ \
			_Push(); \
			PUSH_VALUE##ARG_NUMBER \
			return _Call(ARG_NUMBER, 1); \
		} \
		template <DECLARE_TYPENAME##ARG_NUMBER> \
		_LuaMultiValueHolder& operator()(DECLARE_ARG##ARG_NUMBER) \
		{ \
			_Push(); \
			PUSH_VALUE##ARG_NUMBER \
			return _Call(ARG_NUMBER, 1); \
		}
	class _LuaMultiValueHolder;
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
		_LuaMultiValueHolder& invoke()
		{
			_Push();
			return _Call(0, 1);
		}
		_LuaMultiValueHolder& operator()()
		{
			return invoke();
		}
		DECLARE_PROPERTY(int, m_nRetCount, set_retnums, get_retnums);
		DECLARE_INVOKE_METHOD(1)
		DECLARE_INVOKE_METHOD(2)
		DECLARE_INVOKE_METHOD(3)
		DECLARE_INVOKE_METHOD(4)
		DECLARE_INVOKE_METHOD(5)
	protected:
		virtual void _CopyObject(const luafunc &rhl);
		//调用函数，并处理错误
		virtual _LuaMultiValueHolder& _Call(int nargs, int nresults);
	protected:
		_LuaMultiValueHolder *m_lpLuaMultiValueHolder;
		int m_nRetCount;
	};
}
