/*******************************************************************************
* ��Ȩ����(C) �������ѭGPLЭ�顣
* Filename		��LuaValueHolder.h
* Author			��ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	��2009��08��17��
* GUID				��FFD574A9-16C5-4E4B-B686-E77985626E0B
* Comments	��
*******************************************************************************/

#pragma once
namespace sle
{
	class luaenvironment;
	class luatable;
	class _LuaValueHolder
	{
	public:
		_LuaValueHolder(luaenvironment *lpLuaEvrnt);
		_LuaValueHolder(const _LuaValueHolder &rhl);
		virtual ~_LuaValueHolder(void);
		virtual _LuaValueHolder& operator=(const _LuaValueHolder &rhl);
	public:
		template <typename T>
		void setvalue(int nType, T _v);

		template <typename T>
		void setvalue(int nType, T* _lpv, size_t nsize);

		template <typename T>
		void setvalue(int nType, T** _lplpv, size_t nsize);

		void setvalue(int nStackDeep);

		virtual void clearvalue();

	public: //һ��ǿ������ת������
		virtual operator int();
		virtual operator double();
		virtual operator bool();
		virtual operator const char*();
		virtual operator luatable();

	protected:
		virtual void _CopyObject(const _LuaValueHolder &rhl);
		//��ջ����table������ʱ������������
		bool _SetTable(int nDeep);

	protected:
		int m_nType;
		size_t m_nSize;
		void *m_lpBuffer;
		//ָʾ��ǰֵ������table���Ƿ�����ʱ�����ģ�����ǣ�������ʱ���Ҫɾ��
		bool m_bTemp;
		luaenvironment *m_lpLuaEvrnt;
	};

	template <typename T>
	void _LuaValueHolder::setvalue(int nType, T _v)
	{
		setvalue(nType, &_v, sizeof(T));
	}

	template <typename T>
	void _LuaValueHolder::setvalue(int nType, T* _lpv, size_t nsize)
	{
		clearvalue();
		m_nType = nType;
		m_nSize = nsize;
		if (nsize > 0)
			m_lpBuffer = _copypointer(_lpv, nsize);
		else
			m_lpBuffer = NULL;
	}

	template <typename T>
	void _LuaValueHolder::setvalue(int nType, T** _lplpv, size_t nsize)
	{
		ASSERT(false);
	}
}
