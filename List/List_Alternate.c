#pragma warning(disable:4996)

/*
@ 2020.05.21
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ���ڿ��迭�� Listnode�� ���� ����ü ����

typedef char element[20];
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

/*
@ int���� size�� Listnode���� head tail�� ���±���ü ����
*/
typedef struct ListType {
	int size;
	ListNode* head;
	ListNode* tail;
}ListType;

/*
@ ���ڿ��� �Է¹޴� �Լ� ȣ��� ȭ�鿡 ���ڿ� ����� ���α׷����� �ڵ�1
*/
void error(char* message)
{
	fprintf(stderr, "%s \n", message);
	exit(1);
}

/*
@ ListType�� ��ȯ�ϴ� �Լ�
@ Listtype�� ũ�⸸ŭ�� �޸𸮸� �Ҵ��Ͽ� ����
@ ListType�� plist�� ��ȯ��
*/
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

/*
@ Listnode�� ũ�⸸ŭ�� �޸𸮸� �Ҵ��Ͽ� temp ����
@ ���ڿ��� temp�� data������ ����
@ Listnode�� ù�κ��� ��� head�� tail�� temp�� ����Ŵ
@ Listnode�� size�� 1 ������Ű�� �Լ� ����
*/
void insert_last(ListType* plist, char* item)
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL)
		error("�޸� �Ҵ� ����");
	
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
@ ���������Ϳ� Listtype�� �����͸� 2�� �Է¹޴� �Լ�
@ ������ ������ �ݺ��Ͽ� ���Ͽ��� ���ڿ��� �޾ƿ� item������ ������ END���� ������ ������
@ input1�� END�� ���´ٸ� input2�� ���� �����ϴ� �Լ�
*/
void read_to_file(FILE* name, ListType* input1, ListType* input2)
{
	char item[20] = {0};
	bool checker = true;
	
	if(name==NULL)
	{
		error("������ ���� ���߽��ϴ�");
	}

	while (!feof(name))
	{
		fgets(item, sizeof(item), name);
		if (item[strlen(item) - 1] == '\n')	// ������ ���ڴ� ���๮�ڰ� �����Ƿ� ����X
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
@ Listtype�� input1, input�� data�� output�� �����ϴ� �Լ�
@ �ݺ����� ���� �ΰ� �� �ϳ��� ����Ʈ�� null���� ����ų������ �ݺ�
@ �����ʹ� �����ư��� �ѹ��� ������ �ݺ��� ������ ���� �����͸� �ٽ� �ݺ����� ���� output�� ����
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
@ ���������Ϳ� output�� �����͸� �����ϴ� �Լ�
@ output�����͸� �Է��� ->�� �Բ� �Է�
*/
void write_to_file(FILE* outname, ListType* output)
{
	ListNode* out = output->head;

	if (outname == NULL)
	{
		error("���� �б� ����");
	}

	for(; out; out= out->link)
	{
		fprintf(outname, out->data);
		fprintf(outname, "->");
	}
}

/*
@ ȭ�鿡 output�� ����ϴ� �Լ�
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
@ Main�Լ� �κ�
@ ��� �Լ��� ȣ���ѵ� 0�� ��ȯ�ϸ� ���α׷� ����
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
