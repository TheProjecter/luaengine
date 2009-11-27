// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "sle.h"
#include "lua.hpp"
#include "time.h"
#include <string>
using namespace sle;
using namespace std;

//test global variables rw
bool test0(luaenvironment &e)
{
	int n;
	string s;
	luavar gVar1 = e.variable("gVar1");
	luavar gVar2 = e.variable("gVar2");
	n = gVar1;
	s = gVar2;
	RETURN_ON_FAIL(n == 10);
	RETURN_ON_FAIL(s == "asdf");
	gVar1 = 9;
	gVar2 = "fdsa";
	n = gVar1;
	s = gVar2;
	RETURN_ON_FAIL(n == 9);
	RETURN_ON_FAIL(s == "fdsa");
	return true;
}


//test call global functions
bool test1(luaenvironment &e)
{
	int a = 10;
	double b = 22.5;
	double c = 0;
	string s;
	luafunc test1 = e.func("test1");
	c = test1(a, b);
	luafunc test2 = e.func("test2");
	luafunc test_retnil = e.func("test_retnil");
	RETURN_ON_FAIL(c == 32.5);
	s = test2("a", "b");
	RETURN_ON_FAIL(s == "ab");
	test_retnil();
	return true;
}

//test call table functions
bool test2(luaenvironment &e)
{
	int a = 10;
	double b = 22.5;
	double c = 0;
	string s;
	luafunc test1 = e.func("tbFunc.test1");
	luafunc test2 = e.func("tbFunc.test2");
	c = test1(a, b);
	RETURN_ON_FAIL(c == 32.5);
	s = test2("a", "b", "ccc");
	RETURN_ON_FAIL(s == "abccc");
	return true;
}

//test table variables r - string index
bool test3(luaenvironment &e)
{
	int n;
	string s;
	luatable tbT1 = e.table("tbT1");
	n = tbT1["a"];
	RETURN_ON_FAIL(n == 1);
	n = tbT1.getvalue("a");
	RETURN_ON_FAIL(n == 1);
	s = tbT1["c"];
	RETURN_ON_FAIL(s == "fdsa");
	s = tbT1.getvalue("c");
	RETURN_ON_FAIL(s == "fdsa");
	return true;
}

//test table variables w - string index
bool test4(luaenvironment &e)
{
	int n;
	string s;
	luatable tbT1 = e.table("tbT1");
	tbT1["a"] = 10;
	n = tbT1["a"];
	RETURN_ON_FAIL(n == 10);

	tbT1.setvalue("a", 20);
	n = tbT1["a"];
	RETURN_ON_FAIL(n == 20);

	tbT1["c"] = "aaa";
	s = tbT1["c"];
	RETURN_ON_FAIL(s == "aaa");

	tbT1.setvalue("c", "bbb");
	s = tbT1["c"];
	RETURN_ON_FAIL(s == "bbb");
	return true;
}

//test table variables r - int index
bool test5(luaenvironment &e)
{
	int n;
	string s;
	luatable tbT2 = e.table("tbT2");
	n = tbT2[1];
	RETURN_ON_FAIL(n == 2);
	n = tbT2.getvalue(3);
	RETURN_ON_FAIL(n == 3);

	s = tbT2[2];
	RETURN_ON_FAIL(s == "aaa");
	s = tbT2.getvalue(4);
	RETURN_ON_FAIL(s == "bbb");
	return true;
}

//test table variables w - int index
bool test6(luaenvironment &e)
{
	int n;
	string s;
	luatable tbT2 = e.table("tbT2");
	tbT2[1] = 10;
	n = tbT2[1];
	RETURN_ON_FAIL(n == 10);

	tbT2.setvalue(3, 20);
	n = tbT2[3];
	RETURN_ON_FAIL(n == 20);

	tbT2[2] = "ccc";
	s = tbT2[2];
	RETURN_ON_FAIL(s == "ccc");

	tbT2.setvalue(4, "qqq");
	s = tbT2[4];
	RETURN_ON_FAIL(s == "qqq");
	return true;
}

// test access table in table
bool test7(luaenvironment &e)
{
	luatable tbT3T1 = e.table("tbT3.tbT3T1");
	luatable tbT3T1T1 = e.table("tbT3.tbT3T1.tbT3T1T1");
	int n;
	n = tbT3T1["a"];
	RETURN_ON_FAIL(n == 11);
	n = tbT3T1T1["a"];
	RETURN_ON_FAIL(n == 22);
	return true;
}
//test create table
bool test8(luaenvironment &e)
{
	luatable tb = e.newtable();
	luatable tb1 = e.newtable("tbT3.tbT3T1.tbT3T1T2");
	luafunc f = e.func("test_getlen");
	int n;
	tb[1] = 1;
	tb[2] = 2;
	tb[3] = 3;
	tb1[1] = 1;
	tb1[2] = 2;
	tb1[3] = 3;
	n = f(tb);
	RETURN_ON_FAIL(n == 3);
	n = f(tb1);
	RETURN_ON_FAIL(n == 3);
	tb.setnil();
	RETURN_ON_FAIL(tb.nil());
	tb1.setnil();
	n = tb1.type();
	RETURN_ON_FAIL(tb1.nil());
	return true;
}

//test return multiple values
bool test9(luaenvironment &e)
{
	int n = 0, nn = 0;
	luafunc f = e.func("test_rettable", 4);
	luarets rets = f();
	luatable tab = rets[0], tab1;
	//rets.get(tab, n);
	n = tab[1];
	RETURN_ON_FAIL(n == 1);
	n = rets[2];
	RETURN_ON_FAIL(n == 10);
	string s = rets[3];
	RETURN_ON_FAIL(s == "hehe");
	s = "";
	rets.get(tab, tab1, nn, s);
	n = 0;
	n = tab1[1];
	RETURN_ON_FAIL(n == 2);
	RETURN_ON_FAIL(nn == 10);
	RETURN_ON_FAIL(s == "hehe");
	return true;
}
bool test10(luaenvironment &e)
{
	luafunc f = e.func("print");
	f("successful!");
	return true;
}
bool (*testfunc[])(luaenvironment&) = {test0, test1, test2, test3, test4, test5, test6, test7, test8, test9, test10};
void test()
{
	luaenvironment e;
	int n;
	e.init();
	n = e.dofile("e:\\temp\\test.lua");
	/*time_t t = clock();
	for (int i = 0; i < 10000; ++i)
	{
		test10(e);
	}
	time_t t1 = clock() - t;*/
	for (int i = 0; i <= 10; i++)
	{
		ASSERT(testfunc[i](e));
		n = e.gettop();
		ASSERT(n == 0);
	}
	//cout << "Succeed!" << endl;
	//system("pause");
}
int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < 1000; ++i)
	{
		test();
	}
	return 0;
}