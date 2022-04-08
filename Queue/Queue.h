/*
@ ť �������
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#define MAX_QUEUE_SIZE 10	//�ִ� ť ������

typedef int element;

typedef struct {
	element Queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char*);	//�����߻��� �޼��� ����Լ�
void queue_init(QueueType*);	//ť�� �ʱ�ȭ�ϴ� �Լ�
int is_empty(QueueType*);	// ť�� ������� Ȯ���ϴ� �Լ�
int is_full(QueueType*);	//ť�� �������ִ��� Ȯ���ϴ� �Լ�
void enqueue(QueueType*, int);	//ť�� �����͸� �����ϴ� �Լ�
element dequeue(QueueType*);	//ť���� �����͸� �̾� ��ȯ�ϴ� �Լ�



#endif
