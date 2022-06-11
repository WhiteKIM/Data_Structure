/*
* @ ��������ä��� �˰���
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define max(x, y) (x>y)?x:y

typedef struct
{
	int weight; //�������� ����
	int value; //�������� ��ġ
}item;//������ ����ü

char* calc_result[MAX_SIZE][MAX_SIZE] = { " ", };

int Knapsack(int bag_weight, item* list, int item_count)
{
	int** arr =NULL;
	int return_value = 0;
	arr = (int**)malloc(sizeof(int*) * (item_count+1));
	for (int i = 0; i < (item_count+1); i++)
	{
		arr[i] = (int*)malloc(sizeof(int) * (bag_weight + 1));
	}

	for (int i = 0; i < item_count + 1; i++)
	{
		arr[i][0] = 0;
	}
	for (int i = 0; i < bag_weight + 1; i++)
	{
		arr[0][i] = 0;
	}

	for (int i = 1; i < item_count + 1; i++)
	{
		for (int w = 1; w < bag_weight + 1; w++)
		{
			if (list[i - 1].weight > w)
			{
				arr[i][w] = arr[i - 1][w];
			}
			else
			{
				arr[i][w] = max(arr[i - 1][w], arr[i - 1][w - list[i - 1].weight] + list[i - 1].value);//���� �賶�� ���ο� �������� �߰��� ���� ����� ��
			}
		}
	}
	return_value = arr[item_count][bag_weight];
	for (int i = 0; i < item_count; i++)
	{
		free(arr[i]);
	}
	free(arr);
	return return_value;
}

int main(void)
{
	int count = 0; // ���� ����
	int bag_weight = 0;
	item* list;
	printf("���� ������ �Է��Ͻÿ� : ");
	scanf("%d", &count);
	printf("���� �뷮�� �Է��Ͻÿ� : ");
	scanf("%d", &bag_weight);
	list = (item*)malloc(sizeof(item) * count);
	for (int i = 0; i < count; i++)
	{
		int item_value = 0;
		int item_weight = 0;
		printf("�������� ��ġ�� �Է��Ͻÿ� : ");
		scanf("%d", &item_value);
		printf("�������� ���Ը� �Է��Ͻÿ� : ");
		scanf("%d", &item_weight);
		list[i].value = item_value;
		list[i].weight = item_weight;
	}
	int result = Knapsack(bag_weight, list, count);
	printf("����� %d �Դϴ� \n", result);
	return 0;
}