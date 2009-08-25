/*******************************************************************************
* ��Ȩ����(C) Zhao Yu. �������ѭGPLЭ�顣
* �ļ����ƣ�LuaValueHolder.h
* �������ߣ�ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* �������ڣ�2009��08��17��
* �ļ���ʶ��FFD574A9-16C5-4E4B-B686-E77985626E0B
* ����ժҪ��
*******************************************************************************/

#pragma once
namespace sle
{
	class _LuaValueHolder
	{
	public:
		_LuaValueHolder(void);
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

		virtual void clearvalue();
	public: //һ��ǿ������ת������
		virtual operator int();
		virtual operator double();
		virtual operator bool();
		virtual operator const char*();

	protected:
		virtual void _CopyObject(const _LuaValueHolder &rhl);

	protected:
		int m_nType;
		size_t m_nSize;
		void *m_lpBuffer;
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
