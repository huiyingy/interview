#include "qh_vector.h"

#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <climits>

void test1()
{

    qh::vector<int> v(2,9);
    assert(v.size() == 2);
   	
   	v.push_back(1);
    assert(v.size() == 3);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    assert(v.size() == 6);
    
    /* for (size_t i = 0; i < v.size(); ++i)
    {
    	printf("%d ",v[i] );
    }printf("\n");*/
    v.push_back(5);

    v.pop_back();
    v.pop_back();
    assert(v.size() == 5);
    v.clear();
	assert(v.empty());
}

void test2(){
	qh::vector<int> v;
	try{
		v.pop_back();
	}
	catch(int n){
		printf("oops\n");
	}
	if(v.empty()){
		v.resize(6);
		assert(v.size()==6);

		v[4 ] = INT_MAX;
		v.pop_back();
		v[4] ++;
		assert(v[4] ==INT_MIN );

		/*for (int i = 0; i < 6; ++i)
		{
			printf("%d ",v[i] );
		}printf("\n");*/
	}
}

void test3(){
	qh::vector<char> v;
	v.reserve(1233333);
	assert(v.size()==0 );

	v.resize(10,'5');
	assert(v[2]=='5');

	v.push_back('~');
	v.push_back('\n');
	v.push_back('\t');
	v.push_back(',');
	assert(v.size()==14 );

	qh::vector<char> v2(12,'@');
	assert(v2[0]='@' );
	assert(v2[11]='@' );
	assert(v2.size()==12 );

	v = v2;
	assert(v.size()==12 );
	assert(v[3]=='@' );

	v.clear();
	assert(v.empty() );

}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
test1();
test2();
test3();


#ifdef WIN32
    system("pause");
#endif

	return 0;
}

