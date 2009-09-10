/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luatable.h
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月17日
* GUID				：64C29307-C658-4590-BF06-5672D7F4CBA1
* Comments	：
*******************************************************************************/

#pragma once
#include "_Define.h"
#include "luaelement.h"
#include "lua.hpp"
#include "_LuaStackPrase.h"
#include "luaenvironment.h"
#define aux_getn(L,n)	(luaL_checktype(L, n, LUA_TTABLE), luaL_getn(L, n))
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

		template <typename T>
		int insert(T _v);

		_LuaValueHolder& getvalue(size_t _idx);
		_LuaValueHolder& getvalue(const char *_k);
		luavar operator[](size_t _idx);
		luavar operator[](const char* _k);
	protected:
	};

	template <typename T>
	void luatable::setvalue(const char* _k, T _v)
	{
		_Push();
		lua_pushstring(m_lpLuaEvrnt->luastate(), _k); 
		m_lpStackPrase->pushvalue(_v);
		lua_settable(m_lpLuaEvrnt->luastate(), -3);
		_Pop();
	}

	template <typename T>
	void luatable::setvalue(size_t _idx, T _v)
	{
		_Push();
		lua_pushinteger(m_lpLuaEvrnt->luastate(), _idx); 
		m_lpStackPrase->pushvalue(_v);
		lua_settable(m_lpLuaEvrnt->luastate(), -3);
		_Pop();
	}

	template <typename T>
	int luatable::insert(T _v)
	{
		_Push();
		int pos = aux_getn(m_lpLuaEvrnt->luastate(), 1) + 1;  /* first empty element */
		_Pop();
		setvalue(pos, _v);
		return pos;
	}
}
