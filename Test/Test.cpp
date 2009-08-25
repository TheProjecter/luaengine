// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sle.h"
#include <iostream>
using namespace std;
using namespace sle;
#include "time.h"

int _tmain(int argc, _TCHAR* argv[])
{
	luaenvironment e;
	e.init();
	e.dofile("c:\\test.lua");
	luavar var = e.variable("T1.x");
	double d = var;
	return 0;
}

