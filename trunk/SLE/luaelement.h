/*******************************************************************************
* ��Ȩ����(C) �������ѭGPLЭ�顣
* Filename		��luaelement.h
* Author			��ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	��2009��08��20��
* GUID				��3194A591-A506-4C08-AF6D-51D1AA388F2B
* Comments	��
*******************************************************************************/

#pragma once
#include "_Define.h"
#include <string>
namespace sle
{
	class luaenvironment;
	class _LuaStackPrase;
	class _LuaValueHolder;
	class EXPORT_CLASS luaelement
	{
		//��ΪLuaStackPraseҪʹһ��luaelement��ջ���ͱ������PushMethod����
		friend _LuaStackPrase;
	public:
		luaelement(luaenvironment *lpLuaEvrnt, const char *szName);
		luaelement(const luaelement& rhl);
		virtual luaelement& operator=(const luaelement& rhl);
		virtual ~luaelement(void);
	public:
		virtual int lasterr();
		virtual const char* lasterrdesp();
		virtual void clearerr();
		virtual int type();
		virtual bool nil();
		//��鵱ǰ�����Ƿ�Ϸ������������push˵�������ǺϷ���
		virtual bool verify();
	protected:
		virtual void _CopyObject(const luaelement& rhl);
		virtual bool _Push();
		virtual void _Pop(int nExtraPop = 0);
	protected:
		luaenvironment *m_lpLuaEvrnt;
		//������Lua���֣�����"T1.func1"������"tbTable.T1.x"
		std::string m_szName;
		//�ϴγ���Ĵ���
		int m_nErrCode;
		//�ϴγ���Ĵ�������
		std::string m_szErrDesp;
		//����һ��luaֵ
		_LuaValueHolder* m_lpValueHolder;
		//lua��ջ������
		_LuaStackPrase* m_lpStackPrase;
		//�����ջʱ��push����
		int m_nPushCount;
	};
}