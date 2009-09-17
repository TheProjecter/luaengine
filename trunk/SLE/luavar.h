/*******************************************************************************
* ��Ȩ����(C) �������ѭGPLЭ�顣
* Filename		��luavar.h
* Author			��ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	��2009��08��20��
* GUID				��631CCA32-B851-4ED0-A02D-416BB02DA3BC
* Comments	��
*******************************************************************************/

#pragma once
#include "_Define.h"
#include "luaelement.h"
#include "luaenvironment.h"
#include "_LuaStackPrase.h"
#include "lua.hpp"
namespace sle
{
	class EXPORT_CLASS luavar : public luaelement
	{
	public:
		luavar(luaenvironment *lpLuaEvrnt, const char *szName);
		virtual ~luavar(void);
	public:
		template <typename T>
		luavar& operator=(T _v);

		virtual void setnil();
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
			lua_setglobal(m_lpLuaEvrnt->luastate(), m_szName.c_str());
		}
		else
		{
			lua_settable(m_lpLuaEvrnt->luastate(), -3);
		}
		_Pop();
		return *this;
	}
}
