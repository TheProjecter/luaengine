/*******************************************************************************
* File Header
* Filename		£ºluavar.h
* Author			£ºZhaoYu
* Create Time	£º2009Äê08ÔÂ20ÈÕ
* GUID				£º631CCA32-B851-4ED0-A02D-416BB02DA3BC
* Comments	£º
*******************************************************************************/

#pragma once
#include "_Define.h"
#include "luaelement.h"
#include "luaenvironment.h"
#include "_LuaStackPrase.h"

namespace sle
{
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
