/*
@ ť ���� �Լ�
@ ��� ������ ������Ϸ�
*/

#include <stdio.h>
#include "Queue.h"

//���ڿ� �迭�� �Է¹���
void error(char* message)
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

//QueueType����ü�� �Է¹���
void queue_init(QueueType* Q)
{
	Q->front = Q->rear = 0;
}

//QueueType����ü�� �Է¹���
int is_empty(QueueType* Q)
{
	return (Q->front == Q->rear);
}

//QueueType����ü�� �Է¹���
//��ȯ�� int�� ����
int is_full(QueueType* Q)
{
	return ((Q->rear + 1) % MAX_QUEUE_SIZE == Q->front);
}

//QueueType����ü�� int�� ������ �Է¹���
void enqueue(QueueType* Q, int item)
{
	if (is_full(Q))
	{
		error("��ȭ����");
	}

	Q->rear = (Q->rear + 1) % MAX_QUEUE_SIZE;
	Q->Queue[Q->rear] = item;
}

//QueueType����ü�� �Է¹���
//element��=(int)�� ��ȯ��
element dequeue(QueueType* Q)
{
	if (is_empty(Q))
	{	
		error("�������");
	}

	Q->front=(Q->front + 1) % MAX_QUEUE_SIZE;
	
	return Q->Queue[Q->front];
}
