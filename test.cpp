#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdint.h>
using namespace std;

//---1---
void test1(void)
{
	int *p1 = new int[100]; 
	int *p2 = new int[100]();
	
	
	for(int i=0;i<100;i++){
		cout << p1[i] << "  " << p2[i] << endl;
	}
}
//---4---
enum string{    
		x1,    
		x2,    
		x3=10,    
		x4,    
		x5,    
	} x;
void test4()
{
	cout << "x is " << x << endl;
}
//---5---
void test5(void)
{
	unsigned char *p1 = new unsigned char[10] ;
	unsigned long *p2 = new unsigned long[10] ;
	//p1=(unsigned char *)0x801000;
	//p2=(unsigned long *)0x810000;
	cout << "p1 is " << p1 << endl;
	cout << "p1+5 is " << p1+5 << endl;
	cout << "p2 is " << p2 << endl;
	cout << "p2+5 is " << p2+5 << endl;
	
}
//---6---
void example(char acWelcome[]){
    printf("%d\n",sizeof(acWelcome));
    return;
}
void test6(){
    char acWelcome[]="Welcome to Huawei Test";
    example(acWelcome);
}
//---9---
void Func(char str_arg[100])
{
    printf("%d\n",sizeof(str_arg));
	char str_arg1[100];
	printf("%d\n",sizeof(str_arg1));
}
void test9(void)
{
	char str[]="Hello";
    printf("%d\n",sizeof(str));
    printf("%d\n",strlen(str));
    char*p=str;
    printf("%d\n",sizeof(p));
    Func(str);
}
//---10---
void test10()
{
	char str[] = "glad to test something";
	char *p = str;
	p++;
	int *p1 = reinterpret_cast<int *>(p);
	p1++;
	p = reinterpret_cast<char *>(p1); 
	printf("result is %s\n", p);
}
//---12---
class CTest
	{
		public:
			CTest():m_chData('\0'),m_nData(0)
			{
			}
			virtual void mem_fun(){}
		private:
			char m_chData;
			int m_nData;
			static char s_chData;
	};
char CTest::s_chData='\0';

void test12(void)
{
	CTest C;
	cout <<  sizeof(C) << endl;
}
//---15---
class A
{
public:
	 void FuncA()
	 {
		 printf( "FuncA called\n" );
	 }
	 virtual void FuncB()
	 {
		 printf( "FuncB called\n" );
	 }
};
class B : public A
{
public:
	 void FuncA()
	 {
		 A::FuncA();
		 printf( "FuncAB called\n" );
	 }
	 virtual void FuncB()
	 {
		 printf( "FuncBB called\n" );
	 }
};
void test15( void )
{
	 B  b;
	 A  *pa;
	 pa = &b;
	 A *pa2 = new A;
	 pa->FuncA(); 
	 pa->FuncB(); 
	 pa2->FuncA(); 
	 pa2->FuncB();
	 delete pa2;
}
//---16---
int FindSubString( char* pch )
{
    int   count  = 0;
    char  * p1   = pch;
    while ( *p1 != '\0' )
    {   
        if ( *p1 == p1[1] - 1 )
        {
            p1++;
            count++;
        }else  {
            break;
        }
    }
    int count2 = count;
    while ( *p1 != '\0' )
    {
        if ( *p1 == p1[1] + 1 )
        {
            p1++;
            count2--;
        }else  {
            break;
        }
    }
    if ( count2 == 0 )
        return(count);
    return(0);
}
void ModifyString( char* pText )
{
    char  * p1   = pText;
    char  * p2   = p1;
    while ( *p1 != '\0' )
    {
        int count = FindSubString( p1 );
        if ( count > 0 )
        {
            *p2++ = *p1;
            sprintf( p2, "%i", count );
            while ( *p2 != '\0' )
            {
                p2++;
            }
            p1 += count + count + 1;
        }else  {
            *p2++ = *p1++;
        }
    }
}
void test16( void )
{
    char text[32] = "XYBCDCBABABA";
    ModifyString( text );
    printf( text );
	printf("\n");
} 
//---19---
class C
{
public:
	C(int i = 0)
	{
		cout << i ; 
	}
	C(const C &x)		//拷贝赋值函数
	{
		cout << 7;
	}
	C &operator=(const C &x )	//重载=操作
	{
		cout << 3;
		return *this;
	}
	~C()  
	{
		cout << 4;
	} 
};
void test19()
{
	C obj(1),obj2(5);
	C obj3 = obj2;	//此时调用的是拷贝赋值函数
	//obj3 = obj2;	//此时调用的是重载=操作，也就是深拷贝操作
}
//---20---
char *myString()
{
    char buffer[6] = {0};
    char *s = "Hello World!";
    for (int i = 0; i < sizeof(buffer) - 1; i++)
    {
        buffer[i] = *(s + i);
    }
	return buffer;			//没有返回，因为函数返回的是局部指针指向的数组，在函数退出的时候就已经销毁了
}
int test20()
{
	
    printf("%s\n", myString());
    return 0;
}
//-------
struct st_task
{
    uint16_t id;
    uint32_t value;
    uint64_t timestamp;
};
void fool()
{
    st_task task = {};
    uint64_t a = 0x00010001;
    memcpy(&task, &a, sizeof(uint64_t));
    printf("%11u,%11u,%11u\n", task.id, task.value, task.timestamp);
	printf("add is 0x%x  0x%x  0x%x \n",&task.id,&task.value,&task.timestamp);
}
//------
void test_forknum(void)
{
	//i=0时，主进程和其创建的子进程分别打印'-',  打印2个
	//i=1时，之前两个进程打印'-', 每个进程又创建新的子进程， 共打印4个'-'
	//i=2时，之前的四个进程分别打印'-', 并创建新的子进程, 故共打印8个'-'
	//i=3时，之前的8个进程分别打印'-', 并创建新的子进程,故共打印16个'-'
	//综上所述, 共打印2+4+8+16=30个
	int i;
	for(i=0;i<4;i++){
	  fork();
	  printf("-\n");
	}
}
int test_forknum2(){ 
	//i=0时，共有两个进程: 主进程和主进程创建的第一个进程
	//i=1时，以上两个进程分别创建新的进程，此时共有四个进程
	//i=2时，以上四个进程分别创建新的进程，此时共有8个进程
	//....
	//依次类推, 当i=n时，共创建2^(n+1)个进程
     int i; 
     for(i = 0; i<5;i++){ 
        int pid = fork(); 
        if(pid == 0){ 
            //do something 
        } else { 
        //do something 
        } 
        }
    // do somthing,sleep
    return 0;
}

//------
void test_sizeof(void)
{
	char a[]="ABCDEF";
	char dog[]="wang\0miao";
	char cat[]="wang00miao";
	printf("size is %d   %d   %d\n",sizeof(a),sizeof(dog),strlen(dog));  //7 10 4  sizeof 中\0被当成一个字符，而strlen遇到\0就停止了
	printf("size is %d   %d   %d\n",sizeof(a),sizeof(cat),strlen(cat));  //7 11 10
}



void testali(void)
{
	
	
	
	
}

//------
int uniquePaths(int m, int n) {
int *r = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
            if(0==j || 0 == i)
                r[j] = 1;
            else
                r[j] = r[j] + r[j-1];
        }
    int r1 = r[n-1];
    free(r);
    return r1;
}
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize) {
    int m = obstacleGridRowSize;
    int n = obstacleGridColSize;
    int** path =(int**)malloc(sizeof(int*) * m);
    for(int i=0;i<m;i++)
        path[i] = (int*)malloc(sizeof(int)*n);

    for(int i=0;i<m;i++)
    {
        if(1 == obstacleGrid[i][0])
        {
            for(int j=i;j<m;j++)
                path[j][0] = 0;
            break;
        }
        else
            path[i][0] = 1;
    }  

    for(int i=0;i<n;i++)
    {
        if(1 == obstacleGrid[0][i])
        {
            for(int j=i;j<n;j++)
                path[0][j] = 0;
            break;
        }
        else
            path[0][i] = 1;
    }

    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            if(1 == obstacleGrid[i][j])
                path[i][j] = 0;
            else
                path[i][j] = path[i-1][j] + path[i][j-1];
        }
    }

    int r = path[m-1][n-1];

    for(int i=0;i<m;i++)
        free(path[i]);
    free(path);

    return r;
}

void testuniquepath(void)
{
	int  _obstacleGrid[6][8]  = {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,1,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
	int *obstacleGrid[8];
	obstacleGrid[0] = _obstacleGrid[0];
	obstacleGrid[1] = _obstacleGrid[1];
	obstacleGrid[2] = _obstacleGrid[2];
	obstacleGrid[3] = _obstacleGrid[3];
	obstacleGrid[4] = _obstacleGrid[4];
	obstacleGrid[5] = _obstacleGrid[5];
	int n = uniquePathsWithObstacles(obstacleGrid,6,8);
	printf("n = %d\n",n);
	
}
//------
//test fprintf
//fprintf是C/C++中的一个格式化写—库函数；其作用是格式化输出到一个流/文件中；
//原型是int fprintf( FILE *stream, const char *format, [ argument ]...)，
//fprintf()函数根据指定的format(格式)发送信息(参数)到由stream(流)指定的文件。
void test_fprintf(void)
{
	char* s = "ABCDEFGH";
	s += 2;
	//stderr :【unix】标准输出(设备)文件，对应终端的屏幕。
	fprintf(stderr,"%d\n",s);   //输出的是s的地址
	fprintf(stderr,"%s\n",s);   //输出的是s字符串  CDEFGH
	printf("s address is : %d\n",s);
}
//------
void test_while(void)
{
	int a = 100 ; 
	while(a>0){
		--a;
	}
	printf("a = %d\n",a);
}
//------
int foo(int x,int y )
{
	if(x<=0 || y<=0)
			return 1;
	return 3*foo(x-1,y/2);
}
void test_digui(void)
{
	int n = foo(3,5);
	printf("n = %d\n",n);
}
//------
class Base
{
	int x;
public:
	Base(int b):x(b){
		
	}
	Base(){
		cout <<"Base()" << endl;
	}
	virtual void display(){
		cout << x << endl;
	}
	
};
class Derived : public Base
{
	int y;
public:
	Derived(int d):Base(d),y(d){
		
	}
	void display()
	{
		cout << y << endl;
	}
};

void test_virtual(void)
{
	Base b(2);
	Derived d(3);
	b.display();
	d.display();
	Base* p = &d;
	p->display();
	
}
void test_Base(void)
{
	Base a[5],*b[6];
}
//------
void test_pk()
{
	int a[5] = {1,2,3,4,5};
	int *p ,**k;
	p = a;
	k = &p;
	printf("%d   ",*(++p));
	p++;
	printf("%d \n",**k);
}
//------
typedef struct {
	double 	a;
	short   c;
	char   	d;
	int   	b;
	char   	e;
	char   	f;
	char    g;
	char    h;

}Bb;
void test_structsize(){
	Bb bb;
	printf("0x%x   \n",&bb.a);
	printf("0x%x   \n",&bb.c);
	printf("0x%x   \n",&bb.d);
	printf("0x%x   \n",&bb.b);
	printf("0x%x   \n",&bb.e);
	printf("0x%x   \n",&bb.f);
	printf("0x%x   \n",&bb.g);
	printf("0x%x   \n",&bb.h);
	printf("%d     \n",sizeof(bb));
}
void test_bit(){
	
	unsigned int temp = 0x11530828;
    temp = (temp & 0x55555555) + ((temp & 0xaaaaaaaa) >> 1);
    temp = (temp & 0x33333333) + ((temp & 0xccccccccc) >> 2);
    temp = (temp & 0x0f0f0f0f) + ((temp & 0xf0f0f0f0 >> 4));
    temp = (temp & 0xff00ff) + ((temp & 0xff00ff00) >> 8);
    temp = (temp & 0xffff) + ((temp & 0xffff0000) >> 16);
    //return temp;
	printf("%d \n",temp);

}
int main(void)
{
    //test1();
	//test4();		//枚举在函数内部定义 则x是随机值，如果在外部定义则x为0
	//test5();
	//test6();   	//output 4
	//test9();
	//test10();
	//test12();
	//test15();
	//test16();
	//test19();
	//test20();		//没有输出，因为函数返回的是局部指针指向的数组，在函数退出的时候就已经销毁了
	//fool();
	//test_forknum();
	//test_sizeof();
	//testuniquepath();
	//test_fprintf();
	//test_while(); 
	//test_digui();
	//test_virtual();
	//test_Base();
	//test_pk();
	//test_structsize();
	test_bit();
	return 0;
}

	
	
	
