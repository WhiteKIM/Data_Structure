#pragma warning(disable:4996)

/*
@ 2020.05.21
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 문자열배열과 Listnode를 갖는 구조체 선언

typedef char element[20];
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

/*
@ int형의 size와 Listnode형의 head tail를 갖는구조체 선언
*/
typedef struct ListType {
	int size;
	ListNode* head;
	ListNode* tail;
}ListType;

/*
@ 문자열을 입력받는 함수 호출시 화면에 문자열 출력후 프로그램종료 코드1
*/
void error(char* message)
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

/*
@ ListType를 반환하는 함수
@ Listtype의 크기만큼의 메모리를 할당하여 생성
@ ListType의 plist를 반환함
*/
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

/*
@ Listnode의 크기만큼의 메모리를 할당하여 temp 생성
@ 문자열을 temp의 data변수에 저장
@ Listnode의 첫부분일 경우 head와 tail은 temp를 가르킴
@ Listnode의 size를 1 증가시키고 함수 종료
*/
void insert_last(ListType* plist, char* item)
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL)
		error("메모리 할당 오류");
	
	strcpy(temp->data, item);
	temp->link = NULL;

	if (plist->tail == NULL)
	{
		plist->head = plist->tail = temp;
	}
	else
	{
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

/*
@ 파일포인터와 Listtype의 포인터를 2개 입력받는 함수
@ 파일의 끝까지 반복하여 파일에서 문자열을 받아와 item변수에 저장후 END값이 나오지 않으면
@ input1에 END가 나온다면 input2에 각각 저장하는 함수
*/
void read_to_file(FILE* name, ListType* input1, ListType* input2)
{
	char item[20] = {0};
	bool checker = true;
	
	if(name==NULL)
	{
		error("파일을 읽지 못했습니다");
	}

	while (!feof(name))
	{
		fgets(item, sizeof(item), name);
		if (item[strlen(item) - 1] == '\n')	// 마지막 문자는 개행문자가 없으므로 제거X
		{
			item[strlen(item) - 1] = '\0';
		}
		
		if (strncmp(item, "END", 3)==0)
		{
			checker = false;
			continue;
		}
		
		if (checker == true)
		{
			insert_last(input1, item);
		}
		else if (checker == false)
		{
			insert_last(input2, item);
		}
	}
}

/*
@ Listtype의 input1, input의 data를 output에 저장하는 함수
@ 반복문을 통해 두개 중 하나의 리스트가 null값을 가르킬때까지 반복
@ 데이터는 번갈아가면 한번씩 저장후 반복문 종료후 남은 데이터를 다시 반복문을 통해 output에 저장
*/
void alternate(ListType* input1, ListType* input2, ListType* output)
{
	ListNode* comp1 = input1->head;
	ListNode* comp2 = input2->head;

	char *temp;

	while(comp1 != NULL &&comp2 != NULL)
	{
		temp = comp1->data;
		insert_last(output, temp);
		comp1 = comp1->link;
		
		temp = comp2->data;
		insert_last(output, temp);
		comp2 = comp2->link;

	}

	for (; comp1 != NULL; comp1 = comp1->link)
		insert_last(output, comp1->data);
	for (; comp2 != NULL; comp2 = comp2->link)
		insert_last(output, comp2->data);
}

/*
@ 파일포인터에 output의 데이터를 저장하는 함수
@ output데이터를 입력후 ->를 함께 입력
*/
void write_to_file(FILE* outname, ListType* output)
{
	ListNode* out = output->head;

	if (outname == NULL)
	{
		error("파일 읽기 오류");
	}

	for(; out; out= out->link)
	{
		fprintf(outname, out->data);
		fprintf(outname, "->");
	}
}

/*
@ 화면에 output를 출력하는 함수
*/
void write_to_screen(ListType* output)
{
	ListNode* out = output->head;

	for (; out; out = out->link)
	{
		printf("%s -> ", out->data);
	}
}

/*
@ Main함수 부분
@ 모든 함수를 호출한뒤 0을 반환하며 프로그램 종료
*/
int main(void)
{
	ListType* list1, * list2, * list3;
	FILE* insertFile= fopen("Input_Node.txt", "rt");
	FILE* outputFile=fopen("Output_Node.txt", "wt");

	list1 = create();
	list2 = create();
	list3 = create();

	read_to_file(insertFile, list1, list2);
	alternate(list1, list2, list3);
	write_to_file(outputFile, list3);
	write_to_screen(list3);

	fclose(insertFile);
	fclose(outputFile);

	return 0;
}
