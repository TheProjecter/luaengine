/*******************************************************************************
* File Header
* Filename		��LuaStackPrase.h
* Author			��ZhaoYu
* Create Time	��2009��08��17��
* GUID				��AF973E30-6A37-4CBD-971E-056EA441AD4E
* Comments	��
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
		//����ֵ��һ���Եģ���Ϊlua�Ķ�ջ�Ǳ䶯�ģ�
		//������಻�洢���ݣ�ֻ�ǰ�lua��ջ�ϵ����ݽ�����void*ָ�뷵��
		//���Է��ص�buffer����lua��ջ�䶯��ʧЧ��ָ��δ֪����
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