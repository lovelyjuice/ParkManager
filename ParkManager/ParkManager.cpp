// ParkManager.cpp : 定义控制台应用程序的入口点。//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 3
#define PRICE 5


typedef struct
{
	char number[8];
	int minute;
}Car;

typedef struct
{
	Car data[MaxSize];
	int top;
}SqStack;

typedef struct node
{
	Car data;
	struct node *next;
}QNode;

typedef struct
{
	QNode *front;
	QNode *rear;
}LiQueue;

//栈操作
void initStack(SqStack *&s)
{
	s = (SqStack *)malloc(sizeof(SqStack));
	s->top = -1;
}

bool push(SqStack *s, Car e)
{
	if (s->top == MaxSize - 1)return false;
	s->data[++s->top] = e;
	return true;
}

bool pop(SqStack *s,Car &e)
{
	if (s->top == -1)return false;
	e = s->data[s->top--];
	return true;
}

bool isFull(SqStack *s)
{
	if (s->top == MaxSize - 1)return true;
	return false;
}

int searchCar(SqStack *stack,char *s)
{
	//返回需要弹栈的汽车数量(不包括离开停车场的那一辆)
	Car *temp = (Car *)stack;
	int order = 0;
	while (strcmp(stack->data[order].number, s)!=0 && order <= stack->top)order++;
	if (order < stack->top)return stack->top - order;       //order<top说明找到了
	if (strcmp(stack->data[stack->top].number, s)!=0)return -1;     //否则看栈顶元素是否是要找的车辆
	else return stack->top-order;
}

void s2s(SqStack *source, SqStack *destination,int times)
{
	Car temp;
	for (; times > 0; times--)
	{
		pop(source, temp);
		push(destination, temp);
	}
}

char *convert(int timestamp)
{
	time_t t;
	struct tm *p;
	t = timestamp;
	p = gmtime(&t);
	static char s[100];
	strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
	return s;
}
void printStack(SqStack *stack)
{
	printf("\n------------------\n 车牌号\t停车时间\n");
	printf("------停车场-----\n");
	for (int i = 0; i <= stack->top; i++)
	{
		printf(" %s\t%s\n", stack->data[i].number,convert(stack->data[i].minute));
	}
	printf("------停车场-----\n");
}


//队列操作
void initQueue(LiQueue *&q)
{
	q = (LiQueue *)malloc(sizeof(LiQueue));
	q->front = q->rear = NULL;
}

void enQueue(LiQueue *q, Car e)
{
	QNode *p;
	p = (QNode *)malloc(sizeof(QNode));
	p->data = e;
	p->next = NULL;
	if (q->rear == NULL)
		q->front = q->rear = p;
	else
	{
		q->rear->next = p;
		q->rear = p;
	}
}

bool deQueue(LiQueue *q, Car &e)
{
	if (q->front == NULL)return false;
	e = q->front->data;
	QNode *temp = q->front;
	if (q->front == q->rear)q->front = q->rear = NULL;
	else q->front = q->front->next;
	free(temp);
	return true;
}

void printQueue(LiQueue *queue)
{
	QNode *t = queue->front;
	printf("-------便道------\n");
	while (t != NULL)
	{
		printf(" %s\t%s\n", t->data.number,convert(t->data.minute) );
		t = t->next;
	}
	printf("-------便道------\n");
}


int main()
{
	LiQueue *queue;
	initQueue(queue);
	SqStack *stack;
	initStack(stack);
	Car leave;
	while (true)
	{
		char option;
		char s[8];
		int mytime;
		char c;
		printf("\n请输入操作（I.进入车库/ O.离开车库/ P.查看停车情况）: ");
		scanf("%c", &option);
		if (option == 'p' || option == 'P')
		{
			printStack(stack);
			printQueue(queue);
			continue;
		}
		printf("请输入车牌号: ");
		while ((c = getchar()) != EOF && c != '\n');
		scanf("%s", s);
		while ((c = getchar()) != EOF && c != '\n');
		Car aCar  ;
		for (int i=0; i < 8; i++)aCar.number[i] = s[i];
		aCar.minute = time(NULL);
		if (option == 'i' || option == 'I')
		{
			if(!push(stack, aCar))enQueue(queue, aCar);
		}
		else if (option == 'o' || option == 'O')
		{
			SqStack *tempStack;
			initStack(tempStack);
			int times=searchCar(stack, s);
			if (times == -1)
			{
				printf("车辆不存在\n");
				continue;
			}
			s2s(stack, tempStack, times);
			pop(stack, leave);
			int nowtime = time(NULL);
			printf("%s车停留了%d小时（不足一小时按一小时计费），每小时%d元，需要交费%d元\n", leave.number, (nowtime - leave.minute)/3600+1, PRICE, ((nowtime- leave.minute)/3600+1)*PRICE);
			s2s(tempStack, stack, times);
			if(deQueue(queue, leave))push(stack, leave);
		}
	}
    return 0;
}


 