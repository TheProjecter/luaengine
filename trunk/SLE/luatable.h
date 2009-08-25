/*******************************************************************************
* ��Ȩ����(C) Zhao Yu. �������ѭGPLЭ�顣
* �ļ����ƣ�luatable.h
* �������ߣ�ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* �������ڣ�2009��08��17��
* �ļ���ʶ��64C29307-C658-4590-BF06-5672D7F4CBA1
* ����ժҪ��
*******************************************************************************/

#pragma once
#include "_Define.h"
#include "luaelement.h"
#include "lua.hpp"
#include "_LuaStackPrase.h"
#include "luaenvironment.h"
namespace sle
{
	class EXPORT_CLASS luatable : public luaelement
	{
	public:
		luatable(luaenvironment *lpLuaEvrnt, const char *szName);
		virtual ~luatable(void);
	public:
		template <typename T>
		void setvalue(size_t _idx, T _v);
		template <typename T>
		void setvalue(const char* _k, T _v);
		_LuaValueHolder& getvalue(size_t _idx);
		_LuaValueHolder& getvalue(const char *_k);
		luavar operator[](size_t _idx);
		luavar operator[](const char* _k);
	protected:
		template <typename K_T, typename V_T>
		void _SetValue(K_T _k, V_T _v);
	};

	template <typename K_T, typename V_T>
	void luatable::_SetValue(K_T _k, V_T _v)
	{
		_Push();
		lua_pushstring(m_lpLuaEvrnt->luastate(), _k);
		m_lpStackPrase->pushvalue(_v);
		lua_settable(m_lpLuaEvrnt->luastate(), -3);
		_Pop();
		lua_pop(m_lpLuaEvrnt->luastate(), 1);
	}
	template <typename T>
	void luatable::setvalue(const char* _k, T _v)
	{
		_SetValue(_k, _v);
	}

	template <typename T>
	void luatable::setvalue(size_t _idx, T _v)
	{
		_SetValue(_idx, _v);
	}
}
