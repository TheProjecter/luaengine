/*******************************************************************************
* File Header
* Filename		：_LuaMultiValueHolder.h
* Author			：ZhaoYu
* Create Time ：2009年09月23日 16时25分11秒
* GUID				：2D7D3BBF-4514-4BA1-8CC1-E5651F38CA76
* Comments	：
*******************************************************************************/

#pragma once
namespace sle
{
	class luaenvironment;
	class _LuaValueHolder;
	class luatable;
	//NOT Thread safe, _Refresh涉及多次堆栈操作，要加堆栈锁
	class _LuaMultiValueHolder
	{
	public:
		_LuaMultiValueHolder(luaenvironment *lpLuaEvrnt);
		virtual ~_LuaMultiValueHolder(void);
	public:
		virtual void _Init();
		//从lua堆栈上获取N个值，复制到当前对象中，然后把那些值从lua栈上移除
		virtual void _Refresh(int nCount);
	public:
		virtual _LuaValueHolder& operator[](int _idx);
		virtual operator int();
		virtual operator double();
		virtual operator bool();
		virtual operator const char*();
		virtual operator luatable();
	protected:
		//数组：保存一组Lua值
		_LuaValueHolder **m_lparyLuaValueHolder;
		int m_nCount;
		luaenvironment *m_lpLuaEvrnt;

	};
}