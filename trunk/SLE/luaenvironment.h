/*******************************************************************************
* ��Ȩ����(C) �������ѭGPLЭ�顣
* Filename		��luaenvironment.h
* Author			��ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	��2009��08��17��
* GUID				��FE8AAFB7-2ADF-47FB-9581-A7A85A29C342
* Comments	��
*******************************************************************************/

#pragma once
#include "_Define.h"
struct lua_State;

namespace sle
{
	class luafunc;
	class luatable;
	class luavar;
	class luaelement;
	class _TempTableManager;
	//�̰߳�ȫ
	class EXPORT_CLASS luaenvironment
	{
	public:
		luaenvironment(void);
		virtual ~luaenvironment(void);
	public:
		virtual bool init();
		virtual bool dofile(const char *szFilename);
		virtual bool dostring(const char *szSource);
		virtual lua_State *luastate();
		//ÿ����������ص�������
		virtual void error(int nCode, const char* szDesp);
		virtual luaelement element(const char *szName);
		virtual luafunc func(const char *szName);
		virtual luatable table(const char *szName);
		virtual luavar variable(const char *szName);
		virtual luatable newtable(const char *szName);
		virtual luatable newtable();
		virtual int __IncTabRef(const char *szName);
		virtual int __DecTabRef(const char *szName);

	protected:
		int m_nErrCode;
		const char *m_nErrDesp;
		lua_State *m_lpLuaState;
		_TempTableManager *m_lpTempTableManager;
	};
}