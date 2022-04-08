/*
@ 큐 헤더파일
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#define MAX_QUEUE_SIZE 10	//최대 큐 사이즈

typedef int element;

typedef struct {
	element Queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char*);	//에러발생시 메세지 출력함수
void queue_init(QueueType*);	//큐를 초기화하는 함수
int is_empty(QueueType*);	// 큐가 비었는지 확인하는 함수
int is_full(QueueType*);	//큐가 가득차있는지 확인하는 함수
void enqueue(QueueType*, int);	//큐에 데이터를 저장하는 함수
element dequeue(QueueType*);	//큐에서 데이터를 뽑아 반환하는 함수



#endif
