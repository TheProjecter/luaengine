/*******************************************************************************
* File Header
* Filename		：LuaStackPrase.h
* Author			：ZhaoYu
* Create Time	：2009年08月17日
* GUID				：AF973E30-6A37-4CBD-971E-056EA441AD4E
* Comments	：
*******************************************************************************/

#pragma once
struct lua_State;

namespace sle
{
	class luaenvironment;
	class luaelement;
	class _LuaStackPrase
	{
	public:
		_LuaStackPrase(luaenvironment *lpLuaState);
		_LuaStackPrase(const _LuaStackPrase& rhl);
		virtual ~_LuaStackPrase(void);
		_LuaStackPrase& operator =(const _LuaStackPrase& rhl);
	public:
		//返回值是一次性的，因为lua的堆栈是变动的，
		//而这个类不存储数据，只是把lua堆栈上的数据解析成void*指针返回
		//所以返回的buffer会在lua堆栈变动后失效，指向未知区域
		virtual const void* get_raw(int _idx);
		virtual size_t get_rawsize(int _idx);
		virtual int get_type(int _idx);
		virtual void pushvalue(int _v);
		virtual void pushvalue(__int64 _v);
		virtual void pushvalue(double _v);
		virtual void pushvalue(char _v);
		virtual void pushvalue(unsigned short _v);
		virtual void pushvalue(unsigned long _v);
		virtual void pushvalue(unsigned int _v);
		virtual void pushvalue(const char *lpstr);
		virtual void pushvalue(bool _v);
		virtual void pushvalue(luaelement& _v);

	protected:
		virtual void _ClearBuffer();
		virtual void* _CopyPointer(const void *lpsrc, size_t nsize);
		virtual void _CopyObject(const _LuaStackPrase &rhl);

	protected:
		bool m_bAlloced;
		size_t m_nSize;
		void *m_lpBuffer;
		luaenvironment *m_lpLuaEvrnt;
	};
}