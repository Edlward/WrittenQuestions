//by xiabodan
//2015百度校园招聘笔试题目 使用两个栈实现队列
//分析：使用栈来模拟队列，需要借助两个栈A、B来实现，
//A栈负责入队，B栈负责出队，空值判断时需要判断两个栈均为空。
//需要注意的是，从A栈向B栈移动元素时要注意只有当B栈为空时，
//把A栈内所有元素一次性移入B栈，若B栈有元素，那么不可移动，
//需要等待B栈为空时才可以移动。
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "xiabodan_stack.h"

typedef int elementtype;

typedef struct node *stack;
typedef struct node *position;
struct node {
	elementtype data;
	position next;
};

static int isempty(stack S);
static void delete_stack(stack S);
static stack create_stack(void);
static elementtype top(stack S);
static elementtype pop(stack S);
static void push(stack S,elementtype data);


 
int isempty(stack S)
{
	return (S->next == NULL);
}
stack create_stack(void)
{
	stack S;
	S = (position)malloc(sizeof(struct node));
	if( S == NULL)
	{	
		printf("create_stack : out of space");
		return ;
	}
	S->next = NULL; // S->next is top of stack ,because header can't store element, have list header
	return  S;
}
void delete_stack(stack S)
{
	 if(S == NULL)
	 	printf("S is a empty stack!\n");
	 else 
	 {
	 	while( !isempty( S))
			pop(S);
	 }
}

elementtype pop(stack S)
{
	elementtype data;
	if(!isempty(S))
	{
		position tem;
		tem = S->next;//tem  point to the top node
		data = S->next->data;
		S->next = tem->next;//also S->next = S->next->next
		free(tem);
		return data;
	}
	else 
		printf("pop : empty stack!\n");
	return 0;
}

elementtype top(stack S)
{
	if(!isempty(S))
		return (S->next->data);
	printf("top : empty stack!\n");
	return 0;
}

void push(stack S,elementtype data)
{
	position P;
	P = (position)malloc(sizeof(struct node));
	if( P == NULL)
	{	
		printf("push : out of space");
		return ;
	}
	P->data = data;    
	P->next = S->next;  //compare list , insert node location the first node here,but insert node anywhere in list
	S->next = P;
}

//两个栈实现队列
typedef struct Queue{
	stack A; // 负责入队列
	stack B; // 负责出队列
}Queue;

Queue*  CreatQueue(void){
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->A = create_stack();
	Q->B = create_stack();
	
	return Q;
}

bool Qisempty(Queue* Q){
	if(isempty(Q->A) && isempty(Q->B))
		return true;
	
	return false;
}

void EnQueue(Queue* Q,elementtype value[],int len){
	
	for(int i=0;i<len;i++){
		push(Q->A,value[i]);
	}
	if(isempty(Q->B)){
		while(!isempty(Q->A)){
			push(Q->B,top(Q->A));
			pop(Q->A);
		}
	}
}

elementtype DeQueue (Queue* Q){
	elementtype value = 0;
	if(isempty(Q->B)){
		while(!isempty(Q->A)){
			push(Q->B,top(Q->A));
			pop(Q->A);
		}
	}
	if(!isempty(Q->B)){
		value = top(Q->B);
		pop(Q->B);
	}
	
	return value;
}

int main(int argc ,char** argv)
{
	/*
	stack S;
	int i = 0 ;
	elementtype data;
	S = create_stack();
	printf("push 10 datas from 0 to 9 \n");
	for(i=0;i<10;i++)
	{
		push(S,i);
	}
	printf("S is empty? %d \n",isempty( S));

	printf("pop 5 datas \n");
	for(i=0;i<5;i++)
	{
		data = pop(S);
		printf("pop data is : %d\n",data);
	}
	printf("push 2 datas 11,12\n");
	push(S,11);
	push(S,12);
	printf("pop all remain datas \n");
	while(!isempty( S))
	{
		data = pop(S);
		printf("pop data is : %d\n",data);
	}
	printf("S is empty? %d \n",isempty( S));
	delete_stack(S);
	*/
	
	Queue* Q = CreatQueue();
	int a[20]= {1,2,3,4,5,6,7,8,9,10,11,12,13};
	EnQueue(Q,a,10);
	printf("Dequeue is empty %d \n",Qisempty(Q));
	for(int i=0;i<5;i++){
		printf("Dequeue data is %d \n",DeQueue(Q));
	}

	EnQueue(Q,&a[10],3);
	printf("Dequeue is empty %d \n",Qisempty(Q));
	for(int i=0;i<8;i++){
		printf("Dequeue data is %d \n",DeQueue(Q));
	}
	printf("Dequeue is empty %d \n",Qisempty(Q));
}

	

