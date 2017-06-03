// ParkManager.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#define MaxSize 100


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
	if (s->top == MaxSize - 1)return false;
	return false;
}

int searchCar(SqStack *stack,char *s)
{
	//返回需要弹栈的汽车数量(不包括离开停车场的那一辆)
	Car *temp = (Car *)stack;
	int order = 0;
	while (!strcmp(stack->data[order].number, s) && order <= stack->top)order++;
	if (order < stack->top)return stack->top - order;       //order<top说明找到了
	if (!strcmp(stack->data[stack->top].number, s))return -1;     //否则看栈顶元素是否是要找的车辆
	else return stack->top-order;
}

int s2s(SqStack *source, SqStack *destination,int times)
{
	Car temp;
	for (; times > 0; times--)
	{
		pop(source, temp);
		push(destination, temp);
	}
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


int main()
{
	LiQueue *queue;
	initQueue(queue);
	SqStack *stack;
	initStack(stack);
	while (true)
	{
		char option;
		char *s;
		int time;
		printf("请输入操作（I/O，车牌号，时间）\n");
		scanf("%c", &option);
		scanf("%s", s);
		scanf("%d", &time);
		Car aCar = { *s,time };
		if (option == 'i' || option == 'I')
		{
			if (isFull(stack))
				enQueue(queue, aCar);
			else
				push(stack, aCar);
		}
		else if (option == 'o' || option == 'O')
		{
			SqStack *tempStack;
			initStack(tempStack);

		}

	}
    return 0;
}


 