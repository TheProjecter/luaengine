gVar1 = 10;
gVar2 = "asdf";
function test1(a, b)
	return a+b;
end
function test2(s1, s2)
	return s1 .. s2;
end

tbFunc = {};
function tbFunc.test1(a, b)
	return a+b;
end
function tbFunc.test2(s1, s2, s3)
	return s1 .. s2 .. s3;
end
function tbFunc.test3(tb)
	return #tb;
end
tbT1 = {a=1, b=2, c="fdsa" };
tbT2 = {2,"aaa",3,"bbb"};
tbT3 = { tbT3T1={a=11, tbT3T1T1={a=22}} };

function test_retnil()
	
end
function test_rettab()
	return { 1,2,3 };
end
function test_getlen(tb)
	return #tb;
end