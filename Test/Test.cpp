// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sle.h"
#include "lua.hpp"
#include <string>
using namespace sle;
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	luaenvironment ee;
	bool b;
	double d;
	int n = 0;
	ee.init();
	ee.dofile("c:\\test.lua");
	n = lua_gettop(ee.luastate());
	ee.dostring("tbRole={ tbBase={}, tbFightSkill={}, tbLifeSkill={}, tbTask={}, tbItem={}, tbState={}, tbCustom={}, tbRecipe={} };");
	n = lua_gettop(ee.luastate());
	luatable t1 = ee.table("T2");
	t1.clear();
	b = t1.nil();
	luatable nt = ee.newtable();
	nt.insert(10);
	nt["a"] = 99;
	d = nt["a"];
	t1.insert(nt);
	n = lua_gettop(ee.luastate());
	nt.clear();
	n = lua_gettop(ee.luastate());
	n =t1.insert(2);
	d = t1[2];
	t1 =  ee.table("T2");
	n =t1.insert(20);
	d = t1[4];
	n = lua_gettop(ee.luastate());
	luavar v = ee.variable("T1.TT1.1");
	n = lua_gettop(ee.luastate());
	d = t1[3];
	n = lua_gettop(ee.luastate());
	d = v;
	n = lua_gettop(ee.luastate());
	v = 10;
	d = v;
	n = lua_gettop(ee.luastate());
	b = t1.verify();
	b = t1.nil();
	n = lua_gettop(ee.luastate());
	/*luatable nt = ee.newtable();
	nt["asdf"] = 10;
	nt["dd"] = "asdf";*/
	//t1.insert(10);
	//t1.insert(nt);
	//t1 =  ee.table("tbRole.tbFightSkill.1");
	//d = t1["asdf"];
	luafunc f = ee.func("getlen");
	n = lua_gettop(ee.luastate());
	d = f(t1);
	n = lua_gettop(ee.luastate());

	return 0;
}

