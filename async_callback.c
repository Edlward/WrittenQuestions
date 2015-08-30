//gcc async_callback.c -o async_callback -lpthread
//by  xiabo 2015.8.26
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//-----------------------底层实现-----------------------------
typedef void (*pcb)(int a);
typedef struct parameter{
	int a ;
	pcb callback;
}parameter; 

//普通函数
void GetCallBack(parameter* p) 	// 写回调者实现的回调函数
{
	//do something
	while(1)
	{
		printf("GetCallBack print! \n");
		sleep(3);
		p->callback(p->a);
	}
}


//线程函数实现
void* callback_thread(void *p1)
{
	//do something
	parameter* p = (parameter*)p1 ;
	while(1)
	{
		printf("GetCallBack print! \n");
		sleep(3);
		p->callback(p->a); //函数指针执行函数，这个函数来自于应用层
	}
}

SetCallBackFun(int a, pcb callback)
{
	printf("SetCallBackFun print! \n");
	parameter *p = malloc(sizeof(parameter)) ; 
	p->a  = 10;
	p->callback = callback;
	//GetCallBack(p);
	pthread_t thing1;
	pthread_create(&thing1,NULL,callback_thread,(void *) p);
	//pthread_join(thing1,NULL);
}

//-----------------------应用者-------------------------------
void fCallBack(int a)			// 应用者实现的回调函数
{
	//do something
	printf("a = %d\n",a);
	printf("fCallBack print! \n");
}

void* thing2_thread(void *message)
{
	//do something
	while(1)
	{
		sleep(1);
		printf("%s\n",(const char*)message);
	}
}

void* thing3_thread(void *message)
{
	//do something
	while(1)
	{
		sleep(1);
		printf("%s\n",(const char*)message);
	}
}

int main(void)
{
	SetCallBackFun(4,fCallBack);
	
	pthread_t thing2;
	const char *message2 = "thing 2";	
	pthread_create(&thing2,NULL,thing2_thread,(void *) message2);
	//pthread_join(thing2,NULL);//!!!warning  if join here,next thread can not run
	
	pthread_t thing3;
	const char *message3 = "thing 3";	
	pthread_create(&thing3,NULL,thing3_thread,(void *) message3);
	pthread_join(thing2,NULL);
	pthread_join(thing3,NULL);
	
	printf("return \n");  //nerver run this!!
	return 0;
}