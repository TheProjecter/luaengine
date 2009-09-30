/*******************************************************************************
* File Header
* Filename		：luatable.h
* Author			：ZhaoYu
* Create Time	：2009-08-17
* GUID				：64C29307-C658-4590-BF06-5672D7F4CBA1
* Comments	：
*******************************************************************************/

#pragma once
#include "_Define.h"
#include "luaelement.h"
#include "_LuaStackPrase.h"
#include "luaenvironment.h"
namespace sle
{
	//NOT Thread safe, setvalue中_Push和_Pop应该加同步锁
	class EXPORT_CLASS luatable : public luaelement
	{
	public:
		luatable();
		luatable(luaenvironment *lpLuaEvrnt, const char *szName);
		virtual ~luatable(void);
	public:
		template <typename T_K, typename T_V>
		void setvalue(T_K _k, T_V _v);

		template <typename T>
		int insert(T _v);

		_LuaValueHolder& getvalue(size_t _idx);
		_LuaValueHolder& getvalue(const char *_k);
		luavar operator[](size_t _idx);
		luavar operator[](const char* _k);
	protected:
		int _GetFirstEmptyPos();
	};

	template <typename T_K, typename T_V>
	void luatable::setvalue(T_K _k, T_V _v)
	{
		_Push();
		m_lpStackPrase->pushvalue(_k); 
		m_lpStackPrase->pushvalue(_v);
		m_lpLuaEvrnt->_SetTable(-3);
		_Pop();
	}

	template <typename T>
	int luatable::insert(T _v)
	{
		int pos = _GetFirstEmptyPos();
		setvalue(pos, _v);
		return pos;
	}
}
