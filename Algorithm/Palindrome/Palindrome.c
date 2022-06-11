/*
@ 2020.06.12
@ ���Ḯ��Ʈ ���� ȸ�� �м�
*/

#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char element;	// element�� char���� �����͸� ����
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
@ ���ÿ��Ḯ��Ʈ �ʱ�ȭ
@ Liststack�� �Է¹���
@ stacknode�� top�� null�� �ʱ�ȭ
@ ��ȯ�� void
*/
void init(LinkedStack* s)
{
	s->top = NULL;
}

/*
@ ���ÿ��Ḯ��Ʈ ���� �˻�
@ ListStack�� �Է� ����
@ top�� ���� null�� ��� ������ ��ȯ
*/
int is_empty(LinkedStack* s)
{
	return (s->top == NULL);
}

/*
@ ���ÿ��Ḯ��Ʈ ��ȭ���� �˻�
@ �� �Լ��� ������ �ʽ��ϴ� -> �޸𸮸� �Ҵ������ν� ��ȭ���°� ���� ����
@ Liststack�� �Է� ����
@ ������ 0�� ��ȯ
*/
int is_full(LinkedStack* s)
{
	return 0;
}

/*
@ ���ÿ��Ḯ��Ʈ�� element���� �����͸� ����
@ stacknode�� ũ�⸸ŭ �޸� �Ҵ�
@ ����� data������ �Է¹��� �����͸� ������ top�� ����Ű���� ��
@ ��ȯ�� void
*/
void push(LinkedStack* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

/*
@ ���ÿ��Ḯ��Ʈ���� �����͸� �����ϴ� �Լ�
@ listStack�� �Է¹���
@ is_empty�Լ��� ȣ���Ͽ� ����˻� �����Ͻ� ���α׷� ���� �ڵ� 1
@ stacknode�� temp�� ������ �ֻ���� ��带 ����
@ s->top�� �� ������ ��ġ�� ����Ű���� �� �� temp�� �޸𸮸� ����
@ element�� temp->data�� ����Ű�� ���� ��ȯ
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
@ ���� �ֻ�� ����� �����͸� ����ϴ� �Լ�
@ Liststack�� �Է¹���
@ is_empty�Լ��� ȣ���Ͽ� ����˻� �����Ͻ� ���α׷� ���� �ڵ�1
@ �ֻ�� ����� data�� char���� ������ ��ȯ
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
@ �Է¹��� ���� ����� ���� ���ÿ��Ḯ��Ʈ�� �Է¹޴� �Լ�
@ ���Ͽ��� ���ڿ��� �Է¹޾� �յڰ� ���� ȸ������ �˻�
@ �˻��� ����� ���Ͽ� �Է¹��� ���ڿ��� ���ڿ��� ȸ���˻� ������� �Բ� ���
@ push�Լ��� ȣ���Ͽ� �Է¹��� ���ÿ��Ḯ��Ʈ�� char���� ������ comp���� ����
@ pop�Լ��� ȣ���Ͽ� �Է¹��� ���ÿ��Ḯ��Ʈ���� �ֻ�� �����͸� ������ ���ڿ� ��
@ ȸ���� ��� bool���� true �ƴҰ�� false�� ����
@ bool ���� true�� ��� ���ڿ��� "ȸ���Դϴ�"��� ���ڿ��� �Բ� output���Ͽ� ���
@ bool ���� false�� ��� ���ڿ��� "ȸ���� �ƴմϴ�"��� ���ڿ��� �Բ� output���Ͽ� ���
@ ��ȯ�� void
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
		
		if (comp[strlen(comp) - 1] == '\n')	// ������ ���ڴ� ���๮�ڰ� �����Ƿ� ����X
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

		for (int i=0; i < (int)(sizeof(comp)) / 2 - 1; i++) // ���ڿ����̸� 2�� ������ 1�� �� �� ��ŭ �ݺ��� ����
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
			fprintf(output, ": ȸ���Դϴ� \n");
			printf("%s : ȸ���Դϴ� \n", comp);
		}
		else
		{
			fprintf(output, "%s", comp);
			fprintf(output, ": ȸ���� �ƴմϴ� \n");
			printf("%s : ȸ���� �ƴմϴ� \n", comp);
		}
	}
}

/*
@ Main �Լ� �κ�
@ void�� �Է¹ް� �������� ���� ��ȯ
*/
int main(void)
{
	LinkedStack s;
	FILE* input = fopen("input.txt", "r");
	FILE * output= fopen("output.txt", "w");

	if (input == NULL)
	{
		fprintf(stderr, "���� �б� ����");
		exit(1);
	}

	if (output == NULL)
	{
		fprintf(stderr, "���� �б� ����");
		exit(1);
	}

	init(&s);
	Palindrome(input, output, &s);

	fclose(input);
	fclose(output);

	return 0;
}