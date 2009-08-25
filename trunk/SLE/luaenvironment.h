/*******************************************************************************
* ��Ȩ����(C) Zhao Yu. �������ѭGPLЭ�顣
* �ļ����ƣ�luaenvironment.h
* �������ߣ�ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* �������ڣ�2009��08��17��
* �ļ���ʶ��FE8AAFB7-2ADF-47FB-9581-A7A85A29C342
* ����ժҪ��
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
	protected:
		int m_nErrCode;
		const char *m_nErrDesp;
		lua_State *m_lpLuaState;
	};
}