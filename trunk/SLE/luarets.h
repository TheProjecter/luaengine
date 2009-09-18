/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：luarets.h
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time ：2009年09月18日 15时32分30秒
* GUID				：FE09D543-A9DE-425F-A606-AF4193F151BF
* Comments	：
*******************************************************************************/

#pragma once
#include "_Define.h"

namespace sle
{
	class _LuaValueHolder;
	class luaenvironment;
	class luatable;
	class EXPORT_CLASS _luarets
	{
	public:
		_luarets(luaenvironment *lpLuaEvrnt);
		virtual ~_luarets(void);
	private:
		//一下两个函数任何情况下都不能调用，因为无意义，所以直接private。
		_luarets(const _luarets &rhl){}
		_luarets& operator=(const _luarets &rhl) {return *this;}

	public:
		virtual void refresh();
		virtual _LuaValueHolder& operator[](int _idx);
	public: //一组强制类型转换函数
		virtual operator int();
		virtual operator double();
		virtual operator bool();
		virtual operator const char*();
		virtual operator luatable();

	protected:
		virtual void _Init();
	protected:
		_LuaValueHolder **m_lparyLuaValueHolder;
		luaenvironment *m_lpLuaEvrnt;
	};
	typedef _luarets& luarets;
}