/*
@ 2020.4.26
@ Deque를 이용힌 회문 검사
*/

#define _CRT_SECURE_NO_WARNINGS  //_s 오류무시;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50   //덱 크기 설정
#define diff 32 //대소문자 차이

typedef int element;
typedef struct Deque
{
	element data[MAX_SIZE];
	int front, rear;
}DequeType;

void error(char* message)  //에러메시지 출력
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

void init_Deque(DequeType* q) //덱 초기화
{
	q->front = q->rear = 0;
}

int is_empty(DequeType* q)		//덱 공백 검사
{
	return (q->front == q->rear);
}

int is_full(DequeType* q)		//덱 포화상태 검사
{
return ((q->rear + 1) % MAX_SIZE == q->front);
}

void add_rear(DequeType* q, element item)		// rear 뒤에서부터 값을 저장
{
	if (is_full(q))
	{
		error("큐가 포화상태입니다");
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType* q) //앞쪽에서부터 데이터를 삭제
{
	if (is_empty(q))
	{
		error("큐가 비었습니다");
	}
	q->front = (q->front + 1) % MAX_SIZE;
	return q->data[q->front];
}

void add_front(DequeType* q, element item)		//앞쪽에서 부터 데이터를 저장
{
	if (is_full(q))
	{
		error("큐가 포화상태입니다");
	}
	q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
	q->data[q->front] = item;
}

element delete_rear(DequeType* q)		//뒤쪽에서부터 데이터를 삭제
{
	int prev = q->rear;

	if (is_empty(q))
	{
		error("큐가 비었습니다");
	}
	q->rear = (q->rear - 1 + MAX_SIZE) % MAX_SIZE;
	return q->data[prev];

}

int main(void)
{
	FILE* fp1 = fopen("input.dat", "rt");
	FILE* fp2 = fopen("output.dat", "wt");

	char string[MAX_SIZE];
	char* cut;

	bool checker = true;

	DequeType dq;
	init_Deque(&dq);


	if (fp1 == NULL)
	{
		error("파일을 열지 못했습니다");
	}

	if (fp2 == NULL)
	{
		error("파일을 열지 못했습니다");
	}

	while (!feof(fp1)) //파일의 끝이 아니라면 반복문 진행
	{
		fgets(string, MAX_SIZE, fp1);
		cut = strtok(string, "\n"); //\n을 기준으로 문자를 잘라 cut에 저장

			for (int i = 0; i < (int)strlen(cut); i++)  //i가 cut의 길이보다 작으면 반복
			{
				if (cut[i] == '\0')
					continue;

				if (cut[i] >= 'A' && cut[i] <= 'Z')
					cut[i] += diff;
			}

			for (int i = 0; i < (int)strlen(cut); i++)
			{
				if (cut[i] == '\0')
					continue;
				else
					add_rear(&dq, cut[i]);
			}

			for (int i = 0; i < ((int)strlen(cut)/2); i++) //회문 검사
			{
				char first=delete_front(&dq);
				char last = delete_rear(&dq);
				if (first != last)
				{
					checker = false;
					break;
				}
				else
					continue;
			}
			if (checker==true) // 회문이 맞으면 잘라낸 문자열을 fp2에 저장후 회문기록
			{
				fprintf(fp2, cut, "회문");
			}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}
