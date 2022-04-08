/*
@ 큐 구현 함수
@ 기능 설명은 헤더파일로
*/

#include <stdio.h>
#include "Queue.h"

//문자열 배열을 입력받음
void error(char* message)
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

//QueueType구조체를 입력받음
void queue_init(QueueType* Q)
{
	Q->front = Q->rear = 0;
}

//QueueType구조체를 입력받음
int is_empty(QueueType* Q)
{
	return (Q->front == Q->rear);
}

//QueueType구조체를 입력받음
//반환형 int형 정수
int is_full(QueueType* Q)
{
	return ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front);
}

//QueueType구조체와 int형 정수를 입력받음
void enqueue(QueueType* Q, int item)
{
	if (is_full(Q))
	{
		error("포화상태");
	}

	Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
	Q->Queue[Q->rear] = item;
}

//QueueType구조체를 입력받음
//element형=(int)을 반환함
element dequeue(QueueType* Q)
{
	if (is_empty(Q))
	{	
		error("공백상태");
	}

	Q->front=(Q->front + 1) % MAX_QUEUE_SIZE;
	
	return Q->Queue[Q->front];
}
