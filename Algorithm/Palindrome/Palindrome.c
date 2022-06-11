/*
@ 2020.06.12
@ 연결리스트 스택 회문 분석
*/

#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char element;	// element는 char형의 데이터를 가짐
typedef struct Stack
{
	element data;
	struct StackNode* link;
}StackNode;

typedef struct
{
	StackNode* top;
}LinkedStack;

/*
@ 스택연결리스트 초기화
@ Liststack을 입력받음
@ stacknode의 top을 null로 초기화
@ 반환값 void
*/
void init(LinkedStack* s)
{
	s->top = NULL;
}

/*
@ 스택연결리스트 공백 검사
@ ListStack을 입력 받음
@ top의 값이 null일 경우 정수형 반환
*/
int is_empty(LinkedStack* s)
{
	return (s->top == NULL);
}

/*
@ 스택연결리스트 포화상태 검사
@ 이 함수는 사용되지 않습니다 -> 메모리를 할당함으로써 포화상태가 오지 않음
@ Liststack을 입력 받음
@ 정수형 0을 반환
*/
int is_full(LinkedStack* s)
{
	return 0;
}

/*
@ 스택연결리스트에 element형의 데이터를 저장
@ stacknode의 크기만큼 메모리 할당
@ 노드의 data영역에 입력받은 데이터를 저장후 top이 가리키도록 함
@ 반환갑 void
*/
void push(LinkedStack* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

/*
@ 스택연결리스트에서 데이터를 제거하는 함수
@ listStack을 입력받음
@ is_empty함수를 호출하여 공백검사 공백일시 프로그램 종료 코드 1
@ stacknode인 temp를 선언후 최상단의 노드를 저장
@ s->top은 그 이전의 위치를 가르키도록 한 후 temp의 메모리를 해제
@ element형 temp->data가 가르키는 값을 반환
*/
char pop(LinkedStack* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "stack is empty \n");
		exit(1);
	}
	else
	{
		StackNode* temp = s->top;
		element data= temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

/*
@ 가장 최상단 노드의 데이터를 출력하는 함수
@ Liststack을 입력받음
@ is_empty함수를 호출하여 공백검사 공백일시 프로그램 종료 코드1
@ 최상단 노드의 data를 char형의 값으로 반환
*/
char peek(LinkedStack* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "stack is empty \n");
		exit(1);
	}
	else
	{
		return s->top->data;
	}
}

/*
@ 입력받을 파일 출력할 파일 스택연결리스트를 입력받는 함수
@ 파일에서 문자열을 입력받아 앞뒤가 같은 회문인지 검사
@ 검사후 출력할 파일에 입력받은 문자열과 문자열의 회문검사 결과값을 함께 출력
@ push함수를 호출하여 입력받은 스택연결리스트에 char형의 데이터 comp값을 저장
@ pop함수를 호출하여 입력받은 스택연결리스트에서 최상단 데이터를 가져와 문자열 비교
@ 회문일 경우 bool값이 true 아닐경우 false를 가짐
@ bool 값이 true일 경우 문자열과 "회문입니다"라는 문자열을 함께 output파일에 출력
@ bool 값이 false일 경우 문자열과 "회문이 아닙니다"라는 문자열과 함께 output파일에 출력
@ 반환값 void
*/
void Palindrome(FILE * input,FILE * output, LinkedStack * s)
{
	char origin[20];
	char *comp=NULL;
	char compare = 0;

	while (!feof(input))
	{
		bool checker = true;
		fgets(origin, 20, input);
		comp = strlwr(origin);
		
		if (comp[strlen(comp) - 1] == '\n')	// 마지막 문자는 개행문자가 없으므로 제거X
		{
			comp[strlen(comp) - 1] = '\0';
		}

		for (int i = 0; comp[i]!='\0'; i++)
		{
			if ('a' <= comp[i] <= 'z')
			{
				push(s, comp[i]);
			}
		}

		for (int i=0; i < (int)(sizeof(comp)) / 2 - 1; i++) // 문자열길이를 2로 나누고 1을 뺀 값 만큼 반복문 진행
		{
			compare = pop(s);
			if ('a' <= comp[i] <= 'z' && 'a'<= compare <'z')
			{
				if (comp[i] != compare)
				{
					checker = false;
					break;
				}
			}
			else
			{
				continue;
			}
		}

		if (checker == true)
		{
			fprintf(output, "%s", comp);
			fprintf(output, ": 회문입니다 \n");
			printf("%s : 회문입니다 \n", comp);
		}
		else
		{
			fprintf(output, "%s", comp);
			fprintf(output, ": 회문이 아닙니다 \n");
			printf("%s : 회문이 아닙니다 \n", comp);
		}
	}
}

/*
@ Main 함수 부분
@ void를 입력받고 정수형의 값을 반환
*/
int main(void)
{
	LinkedStack s;
	FILE* input = fopen("input.txt", "r");
	FILE * output= fopen("output.txt", "w");

	if (input == NULL)
	{
		fprintf(stderr, "파일 읽기 실패");
		exit(1);
	}

	if (output == NULL)
	{
		fprintf(stderr, "파일 읽기 실패");
		exit(1);
	}

	init(&s);
	Palindrome(input, output, &s);

	fclose(input);
	fclose(output);

	return 0;
}