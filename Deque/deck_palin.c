/*
@ 2020.4.26
@ Deque�� �̿��� ȸ�� �˻�
*/

#define _CRT_SECURE_NO_WARNINGS  //_s ��������;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50   //�� ũ�� ����
#define diff 32 //��ҹ��� ����

typedef int element;
typedef struct Deque
{
	element data[MAX_SIZE];
	int front, rear;
}DequeType;

void error(char* message)  //�����޽��� ���
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

void init_Deque(DequeType* q) //�� �ʱ�ȭ
{
	q->front = q->rear = 0;
}

int is_empty(DequeType* q)		//�� ���� �˻�
{
	return (q->front == q->rear);
}

int is_full(DequeType* q)		//�� ��ȭ���� �˻�
{
return ((q->rear + 1) % MAX_SIZE == q->front);
}

void add_rear(DequeType* q, element item)		// rear �ڿ������� ���� ����
{
	if (is_full(q))
	{
		error("ť�� ��ȭ�����Դϴ�");
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType* q) //���ʿ������� �����͸� ����
{
	if (is_empty(q))
	{
		error("ť�� ������ϴ�");
	}
	q->front = (q->front + 1) % MAX_SIZE;
	return q->data[q->front];
}

void add_front(DequeType* q, element item)		//���ʿ��� ���� �����͸� ����
{
	if (is_full(q))
	{
		error("ť�� ��ȭ�����Դϴ�");
	}
	q->front = (q->front - 1 + MAX_SIZE) % MAX_SIZE;
	q->data[q->front] = item;
}

element delete_rear(DequeType* q)		//���ʿ������� �����͸� ����
{
	int prev = q->rear;

	if (is_empty(q))
	{
		error("ť�� ������ϴ�");
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
		error("������ ���� ���߽��ϴ�");
	}

	if (fp2 == NULL)
	{
		error("������ ���� ���߽��ϴ�");
	}

	while (!feof(fp1)) //������ ���� �ƴ϶�� �ݺ��� ����
	{
		fgets(string, MAX_SIZE, fp1);
		cut = strtok(string, "\n"); //\n�� �������� ���ڸ� �߶� cut�� ����

			for (int i = 0; i < (int)strlen(cut); i++)  //i�� cut�� ���̺��� ������ �ݺ�
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

			for (int i = 0; i < ((int)strlen(cut)/2); i++) //ȸ�� �˻�
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
			if (checker==true) // ȸ���� ������ �߶� ���ڿ��� fp2�� ������ ȸ�����
			{
				fprintf(fp2, cut, "ȸ��");
			}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}
