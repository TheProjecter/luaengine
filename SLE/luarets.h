/*******************************************************************************
* ��Ȩ����(C) �������ѭGPLЭ�顣
* Filename		��luarets.h
* Author			��ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time ��2009��09��18�� 15ʱ32��30��
* GUID				��FE09D543-A9DE-425F-A606-AF4193F151BF
* Comments	��
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
		//һ�����������κ�����¶����ܵ��ã���Ϊ�����壬����ֱ��private��
		_luarets(const _luarets &rhl){}
		_luarets& operator=(const _luarets &rhl) {return *this;}

	public:
		virtual void refresh();
		virtual _LuaValueHolder& operator[](int _idx);
	public: //һ��ǿ������ת������
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