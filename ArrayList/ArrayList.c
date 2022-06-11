/*
@ ���� ���� ����
*/

#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#pragma warning(disable:6387)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 30	//�迭 ����Ʈ ũ�� ����

typedef int element;

/*
@ ArrayList ����ü ����
@ int�� size, element �迭 array�� ������ �ִ�
@ �迭 array�� BUF_SIZE�� ���ǵ� ũ�⸦ ������
*/
typedef struct arraylist
{
	element array[BUF_SIZE];
	int size;
}ArrayList;

/*
@ ȣ��� ���ڿ� �迭�� �Է¹޴� �Լ�
@ ȣ��� ���α׷� �۵� ����
@ ���α׷��� ���۵� ����
*/
void error(char* message)
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

/*
@ �迭����Ʈ�� �ʱ�ȭ �Լ�
@ ȣ��� �迭����Ʈ�� size�� 0���� �ʱ�ȭ
*/
void init(ArrayList* L)
{
	L->size = 0;
}

/*
@ �迭����Ʈ�� ����˻�
@ �迭����Ʈ�� size�� 0�� ��� ��ȯ
*/
int is_empty(ArrayList* L)
{
	return L->size == 0;
}

/*
@ �迭����Ʈ�� ������ ������ �˻�
@ �迭����Ʈ�� size�� �ʱ� ����� �迭����Ʈ�� ���� ���� ��� ��ȯ
*/
int is_full(ArrayList* L)
{
	return L->size == BUF_SIZE;
}

/*
@ �迭����Ʈ�� int�� pos���� �޾� �迭����Ʈ���� pos���� ����Ű�� �� ��ȯ
@ pos�� 0���� ���� ���� ������ �迭 ����Ʈ�� size���� �۾ƾ���
*/
element get_entry(ArrayList* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("��ġ ����");
	return L->array[pos];
}

/*
@ �迭����Ʈ�� ����� ��� �� ���
@ ��� �� ��� �� ���๮�� ���
*/
void print_list(ArrayList* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d ->", L->array[i]);
	printf("\n");
}

/*
@ �迭����Ʈ�� element���� item�� �޴� �Լ�
@ item���� �޾Ƽ� �迭����Ʈ L�� ������ L�� size ����
*/
void insert_last(ArrayList* L, element item)
{
	if (L->size >= BUF_SIZE)
	{
		error("����Ʈ�� ���� �����ϴ�");
	}
	L->array[L->size++] = item;
}

/*
@ �迭����Ʈ��int�� pos, element�� item�� �޴� �Լ�
@ pos ���� item���� �޾� �迭����Ʈ L�� pos���� ��ġ�� item�� ������ L�� size�� 1����
*/
void insert(ArrayList* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size))
	{
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];

		L->array[pos] = item;
		L->size++;
	}
}

/*
@ �迭����Ʈ�� int�� pos ���� ����
@ element�� item�� ������ �迭����Ʈ L��pos ��ġ���� item�� ����
@ �ݺ����� ���� pos���� �迭����Ʈ�� L�� size -1��ŭ �ݺ�
@ �迭����Ʈ L-pos �� �迭����Ʈ L+pos+1�� ����
@ L�� size�� 1��ŭ ������ item�� ����� ���� ��ȯ
*/
element delete(ArrayList* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
	{
		error("��ġ ����");
	}

	item = L->array[pos];

	for (int i = pos; i < (L->size - 1); i++)
	{
		L->array[i] = L->array[i + 1];
	}
	L->size--;
	return item;
}

/*
@ �迭����Ʈ�� ����
@ FILE���� input�� input.txt�� �ؽ�Ʈ�б�� ����� ����
@ int�� compare�� ������ input���� �������� ������ ����
@ print_list�� ���� �Լ� ���ۿ� ���� input_array�� ���
*/
void read_array(ArrayList* input_array)
{
	FILE* input = fopen("input.txt", "rt");
	int compare = 0;
	if (input == NULL)
	{
		error("���� �б� ����");
	}
	while (1)
	{
		fscanf(input, "%d", &compare);

		if (compare == -1)
		{
			break;
		}
		else
			insert_last(input_array, compare);
	}

	print_list(input_array);
}

/*
@ Main�Լ�
@ �迭����Ʈ input_Array�� ������ init�Լ��� ���� �� read_array �Լ��� ����
@ 0�� ��ȯ �� ���α׷� ����
*/
int main(void)
{
	ArrayList Input_Array;

	init(&Input_Array);

	read_array(&Input_Array);
	
	return 0;
}