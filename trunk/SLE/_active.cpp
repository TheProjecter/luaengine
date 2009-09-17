#include "stdafx.h"
#include "sle.h"
using namespace sle;
void _active()
{
	luaenvironment e;
	e.init();
	luafunc f = e.func("NULL");
	f(NULL);
	f(NULL, NULL);
	f(NULL, NULL, NULL);
	f(NULL, NULL, NULL, NULL);
	f(NULL, NULL, NULL, NULL, NULL);
}