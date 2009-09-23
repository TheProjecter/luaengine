/*******************************************************************************
* File Header
* Filename		：luavar.h
* Author			：ZhaoYu
* Create Time	：2009年08月20日
* GUID				：631CCA32-B851-4ED0-A02D-416BB02DA3BC
* Comments	：
*******************************************************************************/

#pragma once
#include "_Define.h"
#include "luaelement.h"
#include "luaenvironment.h"
#include "_LuaStackPrase.h"

namespace sle
{
	//NOT Thread safe, operator=中_Push和_Pop应该加同步锁
	class EXPORT_CLASS luavar : public luaelement
	{
	public:
		luavar();
		luavar(luaenvironment *lpLuaEvrnt, const char *szName);
		virtual ~luavar(void);
	public:
		template <typename T>
		luavar& operator=(T _v);

	public:
		virtual operator int();
		virtual operator double();
		virtual operator bool();
		virtual operator const char*();
	protected:
	};
	template <typename T>
	luavar& luavar::operator=(T _v)
	{
		_PushWithoutKey();
		m_lpStackPrase->pushvalue(_v);
		if (_IsGlobal())
		{
			m_lpLuaEvrnt->_SetGlobal(m_szName.c_str());
		}
		else
		{
			m_lpLuaEvrnt->_SetTable(-3);
		}
		_Pop();
		return *this;
	}
}
