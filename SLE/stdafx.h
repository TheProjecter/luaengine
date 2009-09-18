/*******************************************************************************
* 版权所有(C) 本软件遵循GPL协议。
* Filename		：stdafx.h
* Author			：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	：2009年08月17日
* GUID				：BFD48181-BCE4-4679-AB7A-28CFD7F2C7F2
* Comments	：
*******************************************************************************/

#pragma once
#pragma warning(disable:4996)
#ifdef _DEBUG
#pragma warning(disable:4251)
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#include <stdio.h>
#include <tchar.h>
#include <assert.h>
#define ASSERT(arg) assert(arg)


#define CHECK_POINTER(p)	if (!p) ASSERT(false);

#define DELETE_POINTER(p) { if (p) delete p; p = NULL; }

#define RETURN_ON_FAIL(condiction) { if (!(condiction)) { ASSERT(false); return false; } }


// TODO: reference additional headers your program requires here
void* _copypointer(const void *lpsrc, size_t nsize);
void _GenerateTempName(char * lpBuf, int nSize);
