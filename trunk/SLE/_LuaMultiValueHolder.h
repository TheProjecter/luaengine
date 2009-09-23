#pragma once
namespace sle
{
	class luaenvironment;
	class _LuaValueHolder;
	class luatable;
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