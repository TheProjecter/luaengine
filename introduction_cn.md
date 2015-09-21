# 简介 #
Standard Lua Engine（简称SLE）提供了一组Lua与C++进行交互的标准接口，其规范与STL统一。

它与luaplus，luabind等Lua库都不同，通过SLE，能在C++中像访问C++函数、变量、对象一样访问Lua的函数、变量及table。由于Lua本身就是弱类型的语言，所以本库可以做到\*自动识别\*Lua支持的所有类型，而\*无需声明模板对象**。**

本库与平台和编译器无关。
# 示例 #
## 1、创建一个lua环境 ##
```
#include "sle.h"
using namespace sle;
luaenvironment e;
e.dofile("c:\\test.lua");
```
## 2、Table操作 ##
```
luatable t1 = e.table("T1");
luatable t2 = e.newtable("T1.T2");
t1.setvalue("x", 10); //set table via key
t2[1] = "i love you"; //set table via index
t1["y"] = 20; //set table value
double d = t1.value("x"); //get table value via key
d = t1["y"]; //get table value via key
//注：使用setvalue/getvalue比使用[]访问Table效率高，因为[]会创建临时对象
```
## 3、直接操作变量 ##
```
luavar var = e.variable("T1.x");// get a variable
var = t1["x"]; //also can get a variable
var = "a string"; //set a value
const char *szStr = var; // get the value
```
## 3、函数调用 ##
```
luafunc func = e.func("T1.AddNumber");
double dRet = func(var, 10, 20);//函数参数可以使luatable，luavar，luafunc及c++中的各种数据类型
```
## 示例说明 ##
可以发现以上赋值和调用均不用模板，但如果出现不正确的调用，比如返回string却用double来接收，则会报错。

本示例代码中所使用的接口与最新版本可能存在不同，一切以最新版本为准。

# 其他说明 #
## 使用注意 ##
本lua引擎正在开发中，以上示例功能已经实现，但还未经过大规模数据覆盖的测试。bug可能很多。

## 更多功能开发中 ##
  * 支持userdata
  * 在lua中注册c++函数和对象
  * 函数支持多返回值
  * 错误处理
  * ……