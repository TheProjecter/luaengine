# Introduction #
Standard Lua Engine (abbreviated as **SLE**) provides a library of standard interface for interact with Lua in C++. And its naming convention conforms to STL.
Not similar to other Lua Librarys(luaplus, luabind...), via SLE  we can use the syntax like C++ to access Lua functions, variables and tables. Lua is weakly typed language, so SLE also can **automatically identify the types supported by Lua, without using templates**.
# Examples #
## 1、Create a  Lua Environment ##
```
#include "sle.h"
using namespace sle;
luaenvironment e;
e.dofile("c:\\test.lua");
```
## 2、Table Operations ##
```
luatable t1 = e.table("T1");
luatable t2 = e.newtable("T1.T2");
t1.setvalue("x", 10); //set table via key
t2[1] = "i love you"; //set table via index
t1["y"] = 20; //set table value
double d = t1.value("x"); //get table value via key
d = t1["y"]; //get table value via key
//Notes：use setvalue/getvalue method to access Lua Table is more effective than operator[], because operator[] will create temp object.
```
## 3、Lua Variables Operations ##
```
luavar var = e.variable("T1.x");// get a variable
var = t1["x"]; //also can get a variable
var = "a string"; //set a value
const char *szStr = var; // get the value
```
## 3、Function Invoke ##
```
luafunc func = e.func("T1.AddNumber");
double dRet = func(var, 10, 20); //the params can be luatable，luavar，luafunc and any base type in C++
```
## NOTES ##
We can found that all the code above never use templates. But if write a invalid assignment such as use a variable of double to receive a string value returned by a Lua function, it will tigger an exception.

The example code shown in this article may be little different to the new version, all the usage fallow the new version.
## More Features ##
  * Userdata support
  * Register C++ functions & objects to Lua
  * Multiple function returns support
  * Script error handling
  * ……