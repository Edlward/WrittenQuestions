#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
	#include <windows.h>
#else
	#include <pthread.h>
#endif

#ifdef _MSC_VER
	#define mysleep(n)  Sleep(n)
#else
	#define mysleep(n)  sleep(n/1000)
#endif

using namespace std;


class xiabo_C{
public:
	xiabo_C():a(10),d(8)
	{
		printf("I am xiabo_C() function\n");
	}
	static int sfunc();	//��̬��Ա����Ҳ��ѭpublic,private,protected���ʹ���
	int func(void);

public:
	int a;
	static int b ;		//�˴����ܳ�ʼ��
	static const int c = 9;//ֻ�о�̬��������ֱ�ӳ�ʼ��
	const  int d;
};

int  xiabo_C::b = 11;	//��̬��Ա�����ĳ�ʼ��ֻ�������������ڹ����г�ʼ��

int xiabo_C::sfunc(){   //!!!��̬��Ա���������ⲿʵ��ʱ��ǧ��Ҫ��static����Ҫд����static int sfunc(){},�������ⲿ�ľ�̬C����
	//xiabo::a = 11;    //error   ��̬��Ա��������Ӧ�÷Ǿ�̬��Ա
	xiabo_C::b = 12;
	printf("I am static member function,b = %d\n",xiabo_C::b );
	return 0;
}
static int sfunc1(){
	printf("I am static function, not member function \n" );

	return 0;
}
int xiabo_C::func(void){
	xiabo_C::b = 12;
	xiabo_C::sfunc();
	sfunc1();
	return 0;
}
void test_statichunc(void){
	xiabo_C xiabo;
	xiabo.func();
	xiabo_C::sfunc();  //��̬��Ա��������ģ�����ĳ������ģ����ñ���ͨ������������
	
}
//-------------
class xiabo2_C{
public:
	typedef int (*pcb)(int a);
	typedef struct parameter{
		int a ;
		pcb callback;
	}parameter; 
	xiabo2_C():m_a(1){
	
	}
	//��ͨ����
	void GetCallBack(parameter* p) 	// д�ص���ʵ�ֵĻص�����
	{
		m_a = 2;
		//do something
		while(1)
		{
			printf("GetCallBack print! \n");
			mysleep(2000);
			p->callback(p->a);
		}
	}
	int SetCallBackFun(int a, pcb callback)
	{
		printf("SetCallBackFun print! \n");
		parameter *p = new parameter ; 
		p->a  = 10;
		p->callback = callback;
		GetCallBack(p);
		return 0;
	}

public:
	int m_a;
};

class xiabo2Test_C{
public:
	xiabo2Test_C():m_b(1){
	
	}
	static int fCallBack(int a)			// Ӧ����ʵ�ֵĻص���������̬��Ա���������ǲ��ܷ������зǾ�̬��Ա�ˣ��ƻ�����Ľṹ
	{
		//do something
		//m_b = a;		// ���ܷ������зǾ�̬��Ա�ˣ��ƻ�����Ľṹ,Ӧ����ʹ�ú��鷳
		printf("a = %d\n",a);
		printf("fCallBack print! \n");
		return 0;
	}
public:
	int m_b;
};

//-------------------
template<typename Tobject,typename Tparam>
class xiabo3_C{
	typedef void (Tobject::*Cbfun)(Tparam* );
public:
	bool Exec(Tparam* pParam);
	void Set(Tobject *pInstance,Cbfun pFun,Tparam* pParam);

private:
	Cbfun pCbfun;
	Tobject* m_pInstance;
};

template<typename Tobject,typename Tparam>
void xiabo3_C<Tobject,Tparam>::Set(Tobject *pInstance,Cbfun pFun,Tparam* pParam){
	printf("Set print!\n");
	m_pInstance = pInstance;
	(pInstance->*pFun)(pParam);		//����ֱ��������ص��������ĺ���ָ��
	pCbfun = pFun;
}
template<typename Tobject,typename Tparam>
bool xiabo3_C<Tobject,Tparam>::Exec(Tparam* pParam){
	printf("Exec print!\n");
	(m_pInstance->*pCbfun)(pParam);//Ҳ����������ص��������ĺ���ָ��
	return true;
}

class xiabo3Test_C{
public:
	xiabo3Test_C():m_N(13){
		
	}
	void fCallBack(int *p){
		printf("fCallBack : Sum = m_N + *p = %d\n",*p + m_N);
		printf("fCallBack print! I am a member function! I can access all the member ,HaHa...\n");
	}

private:
	int m_N;

};

//--------------
//���ж����̣߳���ʵ�ֻص�
class  xiabo4_C{
public:
	struct ThreadParam{
		xiabo4_C* pthis;
		int a ;
		int b ;
	};//�����̲߳����Զ���ṹ
	
public:
	xiabo4_C():m_N(1){
		
	}
	void print(void){
		printf("print : m_N = %d \n",m_N);
	}
	//��̬ʵ��
	void CreatAlgorithmThread(void);
	static void *funThreadAlgorithm(void* p);  //��̬��Ա����ʵ���߳�Wrapper
	//�Ǿ�̬ʵ��
	void CreatAlgorithm2Thread(int a ,int b);
	static void *funThreadAlgorithm2(void* param);  //�Ǿ�̬��Ա����ʵ���߳�Wrapper
	void ThreadFunc(int a ,int b){
		printf("ThreadFunc : I am ThreadFunc,I am a member function! I can access all the member ,HaHa...\n");
		printf("ThreadFunc : m_N = %d \n",m_N);
	}
	
private:
	int m_N;
};

void xiabo4_C::CreatAlgorithmThread(void){  //��̬ʵ��
#ifdef _MSC_VER
	HANDLE handle1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)funThreadAlgorithm,0,0,NULL);	
	CloseHandle(handle1);
#else
	pthread_t thing1;
	pthread_create(&thing1,NULL,&funThreadAlgorithm,(void *) 0);
	pthread_join(thing1,NULL);
#endif
}
void* xiabo4_C::funThreadAlgorithm(void* p){
	while(1)
	{
		mysleep(2000);
		printf("I am a static meeber function! I can not access the member\n");
	}
}

void xiabo4_C::CreatAlgorithm2Thread(int a ,int b){
	ThreadParam* p = new ThreadParam;
	p->pthis = this;
	p->a	 = a;
	p->b	 = b;
#ifdef _MSC_VER
	HANDLE handle2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)funThreadAlgorithm2,p,0,NULL);	
	CloseHandle(handle2);
#else
	pthread_t thing1;
	pthread_create(&thing1,NULL,&funThreadAlgorithm2,(void *) p);
	pthread_join(thing1,NULL);
#endif
}
void* xiabo4_C::funThreadAlgorithm2(void* param){
	ThreadParam* p = (ThreadParam*)param;

	printf("I am a static meeber function! I can not access the member\n");
	printf("But I can call a member func ,I can instigate ThreadFunc ,ThreadFunc can access all member\n");
	printf("ThreadParam p->a = %d, p->b = %d \n",p->a,p->b);
	p->pthis->ThreadFunc(p->a,p->b);
	return 0;
}

//--------------
//���ж����̣߳���ʵ�ֻص�
//A����Ա
template<typename Tobject,typename Tparam>
class  xiabo5_C{
public:
	struct ThreadParam{
		xiabo5_C* pthis;
		Tparam a ;
	};//�����̲߳����Զ���ṹ
	typedef void (Tobject::*Cbfun)(Tparam );
public:
	xiabo5_C():m_N(1){
		printf("xiabo5_C : xiabo5_C()\n");
	}
	void print(void){
		printf("print : m_N = %d \n",m_N);
	}
	//�Ǿ�̬ʵ��
	void CreateCallbackThread(Tobject *pInstance,Cbfun pFun,Tparam a );
	static void* funCallbackThread(void* param);  //�Ǿ�̬��Ա����ʵ���߳�Wrapper
	void ThreadFunc(Tparam a );  //�߳�ִ�к���
	
private:
	int m_N;
	Cbfun pCbfun;
	Tobject* m_pInstance;
};
template<typename Tobject,typename Tparam>
void xiabo5_C<Tobject,Tparam>:: CreateCallbackThread(Tobject *pInstance,Cbfun pFun,Tparam a ){
	ThreadParam* p = new ThreadParam;
	p->pthis = this;
	p->a	 = a;
	m_pInstance = pInstance;
	pCbfun = pFun;

#ifdef _MSC_VER
	HANDLE handle2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)funCallbackThread,p,0,NULL);	
	CloseHandle(handle2);
#else
	pthread_t thing1;
	pthread_create(&thing1,NULL,&funCallbackThread,(void *) p);
	//pthread_join(thing1,NULL); //warning !! can not be join !!!
#endif
}
template<typename Tobject,typename Tparam>
void* xiabo5_C<Tobject,Tparam>::funCallbackThread(void* param){
	ThreadParam* p  = (ThreadParam*)param;
	printf("I am a static meeber function! I can not access the member\n");
	printf("But I can call a member func ,I can instigate ThreadFunc ,ThreadFunc can access all member\n");
	printf("ThreadParam p->a = %d\n",p->a);
	p->pthis->ThreadFunc(p->a);
	return 0;
}
template<typename Tobject,typename Tparam>
void xiabo5_C<Tobject,Tparam>::ThreadFunc(Tparam a ){
	printf("I am ThreadFunc,I am a member function and access all the member ,HaHa...\n");
	//printf("%d ThreadFunc : m_N = %d \n",m_N);
	while(1)
	{
		const pthread_t me = pthread_self();
		mysleep(a*1000);
		(m_pInstance->*pCbfun)(me);
	}
}
//B����Ա
class xiabo5Test_C{
public:
	xiabo5Test_C():m_N(0){
	
	}
	void fCallBack(int p){
		printf("Thread ID = %d fCallBack : Sum = m_N + *p = %d\n",p,p + m_N);
		//printf("fCallBack print! I am a member function! I can access all the member ,HaHa...\n");
	}
public:

private:
	int m_N;
};


int main(void ){
	//���Ծ�̬��Ա����
	//test_statichunc();

	//���Ծ�̬��Ա���������ڻص�
	//xiabo2_C xiabo2;
	//xiabo2.SetCallBackFun(5,xiabo2Test_C::fCallBack);

	//���ԷǾ�̬��Ա���������ڻص���good
	//xiabo3_C<xiabo3Test_C,int> xiabo3;
	//xiabo3Test_C xiabo3Test;
	//int p = 13;
	//xiabo3.Set(&xiabo3Test,&xiabo3Test_C::fCallBack,&p); //
	//xiabo3.Exec(&p);

	//���ж����߳�
	//xiabo4_C xiabo4;
	//xiabo4.CreatAlgorithm2Thread(1,2);

	//���ж����̣߳���ʵ�ֻص�
	xiabo5_C<xiabo5Test_C,int> xiabo5;
	xiabo5Test_C xiabo5Test;
	int p = 2;
	xiabo5.CreateCallbackThread(&xiabo5Test,&xiabo5Test_C::fCallBack,p);


	xiabo5_C<xiabo5Test_C,int> xiabo51;
	xiabo5Test_C xiabo5Test1;
	int p1 = 4;
	xiabo51.CreateCallbackThread(&xiabo5Test1,&xiabo5Test_C::fCallBack,p1);
	getchar();
	return 0;
}