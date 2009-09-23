/*******************************************************************************
* File Header
* Filename		：_Define.h
* Author			：ZhaoYu
* Create Time ：2009年08月25日 11时52分27秒
* GUID				：F50FDD61-3DAA-4EC1-A97D-C34422993C96
* Comments	：
*******************************************************************************/
namespace sle
{
#define EXPORT_CLASS _declspec(dllexport)

#define DECLARE_TYPENAME1 typename T1
#define DECLARE_TYPENAME2 DECLARE_TYPENAME1, typename T2
#define DECLARE_TYPENAME3 DECLARE_TYPENAME2, typename T3
#define DECLARE_TYPENAME4 DECLARE_TYPENAME3, typename T4
#define DECLARE_TYPENAME5 DECLARE_TYPENAME4, typename T5

#define DECLARE_REF_ARG1 T1& arg1
#define DECLARE_REF_ARG2 DECLARE_REF_ARG1, T2 &arg2
#define DECLARE_REF_ARG3 DECLARE_REF_ARG2, T3 &arg3
#define DECLARE_REF_ARG4 DECLARE_REF_ARG3, T4 &arg4
#define DECLARE_REF_ARG5 DECLARE_REF_ARG4, T5 &arg5

#define DECLARE_ARG1 T1 arg1
#define DECLARE_ARG2 DECLARE_ARG1, T2 arg2
#define DECLARE_ARG3 DECLARE_ARG2, T3 arg3
#define DECLARE_ARG4 DECLARE_ARG3, T4 arg4
#define DECLARE_ARG5 DECLARE_ARG4, T5 arg5

#define DECLARE_PROPERTY(_ty, _v, _set, _get) \
	void _set(_ty _value) { _v = _value; } \
	_ty _get() { return _v; }
#define DECLARE_PROPERTY_GET(_ty, _v, _get) \
	_ty _get() { return _v; }
#define DECLARE_PROPERTY_SET(_ty, _v, _set) \
	void _set(_ty _value) { _v = _value; }
}