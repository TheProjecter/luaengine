/*******************************************************************************
* File Header
* Filename		��luarets.h
* Author			��ZhaoYu
* Create Time ��2009��09��18�� 15ʱ32��30��
* GUID				��FE09D543-A9DE-425F-A606-AF4193F151BF
* Comments	��
*******************************************************************************/

#pragma once
#include "_Define.h"

namespace sle
{
	#define ST(i) arg##i = m_lpLuaMultiValueHolder->operator[](i - 1);
	#define ST1 ST(1)
	#define ST2 ST1 ST(2)
	#define ST3 ST2 ST(3)
	#define ST4 ST3 ST(4)
	#define ST5 ST4 ST(5)

	#define DECLARE_GET_METHOD(ARG_NUMBER) \
		template <DECLARE_TYPENAME##ARG_NUMBER> \
		void get(DECLARE_REF_ARG##ARG_NUMBER) \
		{ \
			ST##ARG_NUMBER \
		}
	class _LuaValueHolder;
	class _LuaMultiValueHolder;
	//Thread safe
	class EXPORT_CLASS luarets
	{
	public:
		luarets(const _LuaMultiValueHolder &values);
		virtual ~luarets(void);
		//���operator=������ģ�������������������ֵ
		void operator=(const _LuaMultiValueHolder &rhl);
	private:
		//���������������ܵ��ã���Ϊ�����壬��ֹ����ã�ֱ��private
		luarets(const luarets &rhl) {}
		void operator=(const luarets &rhl) {}

	public:
		virtual _LuaValueHolder& operator[](int _idx);
		DECLARE_GET_METHOD(2);
		DECLARE_GET_METHOD(1);
		DECLARE_GET_METHOD(3);
		DECLARE_GET_METHOD(4);
		DECLARE_GET_METHOD(5);

	protected:
		_LuaMultiValueHolder *m_lpLuaMultiValueHolder;
	};
}