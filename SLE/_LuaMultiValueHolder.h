/*******************************************************************************
* File Header
* Filename		��_LuaMultiValueHolder.h
* Author			��ZhaoYu
* Create Time ��2009��09��23�� 16ʱ25��11��
* GUID				��2D7D3BBF-4514-4BA1-8CC1-E5651F38CA76
* Comments	��
*******************************************************************************/

#pragma once
namespace sle
{
	class luaenvironment;
	class _LuaValueHolder;
	class luatable;
	//NOT Thread safe, _Refresh�漰��ζ�ջ������Ҫ�Ӷ�ջ��
	class _LuaMultiValueHolder
	{
	public:
		_LuaMultiValueHolder(luaenvironment *lpLuaEvrnt);
		virtual ~_LuaMultiValueHolder(void);
	public:
		virtual void _Init();
		//��lua��ջ�ϻ�ȡN��ֵ�����Ƶ���ǰ�����У�Ȼ�����Щֵ��luaջ���Ƴ�
		virtual void _Refresh(int nCount);
	public:
		virtual _LuaValueHolder& operator[](int _idx);
		virtual operator int();
		virtual operator double();
		virtual operator bool();
		virtual operator const char*();
		virtual operator luatable();
	protected:
		//���飺����һ��Luaֵ
		_LuaValueHolder **m_lparyLuaValueHolder;
		int m_nCount;
		luaenvironment *m_lpLuaEvrnt;

	};
}