/*******************************************************************************
* ��Ȩ����(C) �������ѭGPLЭ�顣
* Filename		��stdafx.cpp
* Author			��ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* Create Time	��2009��08��17��
* GUID				��8D68FB51-DDD4-416C-8748-7F730BB1C778
* Comments	��
*******************************************************************************/

#include "stdafx.h"
#include "malloc.h"
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
void* _copypointer(const void *lpsrc, size_t nsize)
{
	CHECK_POINTER(lpsrc);
	void *lpdest;
	lpdest = new char[nsize];
	memcpy(lpdest, lpsrc, nsize);
	return lpdest;
}