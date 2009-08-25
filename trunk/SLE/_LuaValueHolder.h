/*******************************************************************************
* 版权所有(C) Zhao Yu. 本软件遵循GPL协议。
* 文件名称：LuaValueHolder.h
* 作　　者：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* 创建日期：2009年08月17日
* 文件标识：FFD574A9-16C5-4E4B-B686-E77985626E0B
* 内容摘要：
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
	public: //一组强制类型转换函数
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
