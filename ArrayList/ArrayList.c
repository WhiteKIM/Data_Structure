/*
@ 각종 오류 무시
*/

#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#pragma warning(disable:6387)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 30	//배열 리스트 크기 설정

typedef int element;

/*
@ ArrayList 구조체 선언
@ int형 size, element 배열 array를 가지고 있다
@ 배열 array는 BUF_SIZE로 정의된 크기를 가진다
*/
typedef struct arraylist
{
	element array[BUF_SIZE];
	int size;
}ArrayList;

/*
@ 호출시 문자열 배열을 입력받는 함수
@ 호출시 프로그램 작동 종료
@ 프로그램의 오작동 방지
*/
void error(char* message)
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

/*
@ 배열리스트의 초기화 함수
@ 호출시 배열리스트의 size를 0으로 초기화
*/
void init(ArrayList* L)
{
	L->size = 0;
}

/*
@ 배열리스트의 공백검사
@ 배열리스트의 size가 0일 경우 반환
*/
int is_empty(ArrayList* L)
{
	return L->size == 0;
}

/*
@ 배열리스트에 공간이 없는지 검사
@ 배열리스트의 size가 초기 선언된 배열리스트와 비교후 같을 경우 반환
*/
int is_full(ArrayList* L)
{
	return L->size == BUF_SIZE;
}

/*
@ 배열리스트와 int형 pos값을 받아 배열리스트에서 pos값이 가르키는 값 반환
@ pos는 0보다 양의 값을 가지고 배열 리스트의 size보다 작아야함
*/
element get_entry(ArrayList* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}

/*
@ 배열리스트에 저장된 모든 값 출력
@ 모든 값 출력 후 개행문자 출력
*/
void print_list(ArrayList* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d ->", L->array[i]);
	printf("\n");
}

/*
@ 배열리스트와 element형의 item을 받는 함수
@ item값을 받아서 배열리스트 L에 저장후 L의 size 증가
*/
void insert_last(ArrayList* L, element item)
{
	if (L->size >= BUF_SIZE)
	{
		error("리스트가 가득 찻습니다");
	}
	L->array[L->size++] = item;
}

/*
@ 배열리스트와int형 pos, element형 item을 받는 함수
@ pos 값과 item값을 받아 배열리스트 L의 pos값의 위치에 item을 저장후 L의 size를 1증가
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
@ 배열리스트와 int형 pos 값을 받음
@ element형 item을 선언후 배열리스트 L의pos 위치값을 item에 저장
@ 반복문을 통해 pos부터 배열리스트의 L의 size -1만큼 반복
@ 배열리스트 L-pos 에 배열리스트 L+pos+1을 저장
@ L의 size를 1만큼 감소후 item에 저장된 값을 반환
*/
element delete(ArrayList* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
	{
		error("위치 오류");
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
@ 배열리스트를 받음
@ FILE형의 input를 input.txt를 텍스트읽기로 열기로 선언
@ int형 compare를 선언후 input에서 정수값을 가져와 저장
@ print_list를 통해 함수 시작에 받은 input_array를 출력
*/
void read_array(ArrayList* input_array)
{
	FILE* input = fopen("input.txt", "rt");
	int compare = 0;
	if (input == NULL)
	{
		error("파일 읽기 실패");
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
@ Main함수
@ 배열리스트 input_Array를 선언후 init함수를 실행 후 read_array 함수를 실행
@ 0을 반환 후 프로그램 종료
*/
int main(void)
{
	ArrayList Input_Array;

	init(&Input_Array);

	read_array(&Input_Array);
	
	return 0;
}