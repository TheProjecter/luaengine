/*******************************************************************************
* 版权所有(C) Zhao Yu. 本软件遵循GPL协议。
* 文件名称：stdafx.cpp
* 作　　者：ZhaoYu(icyplayer@126.com) <http://www.zhaoyu.me/>
* 创建日期：2009年08月17日
* 文件标识：8D68FB51-DDD4-416C-8748-7F730BB1C778
* 内容摘要：
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