/*******************************************************************************
* File Header
* Filename		£ºstdafx.cpp
* Author			£ºZhaoYu
* Create Time	£º2009-08-17
* GUID				£º8D68FB51-DDD4-416C-8748-7F730BB1C778
* Comments	£º
*******************************************************************************/

#include "stdafx.h"
#include "malloc.h"
#include "stdlib.h"
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
unsigned int s_nTempTableId = 0;
void* _copypointer(const void *lpsrc, size_t nsize)
{
	CHECK_POINTER(lpsrc);
	void *lpdest;
	lpdest = new char[nsize];
	memcpy(lpdest, lpsrc, nsize);
	return lpdest;
}
void _GenerateTempName(char * lpBuf, int nSize)
{
	sprintf_s(lpBuf, nSize, "sletemptb%d%d", rand()*10000, s_nTempTableId++);
}
