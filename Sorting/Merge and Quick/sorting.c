/*
* ��ǻ�;˰���_01
* �����б� ��ǻ�Ͱ��а� 5413970 ����
* �������� 2022.03.26
*/

#include <stdio.h>
#include <time.h>
#include "sorting.h"

#define size 60000

int main(void)
{
	clock_t start, end;
	float cal_time;
	int arr[12] = { 6,3,11,9,12,2,8,15,18,10,7,14};
	int search_len = sizeof(arr) / sizeof(int);
	int search;
	int find;

	//int arr[60000];
	/*
	for (int i = 0; i < 8; i++)
	{
		arr[i] = (rand() % 100 + 1);
	}
	*/
	
	
	//int search_len = size;

	printf("length : %d \n", search_len);
	//selectSort(arr, search_len);
	//mergeSort(arr, 0, search_len - 1);
	//find_median(arr, search_len);	//�߰����� ã�Ƽ� ���
	//quickSort(arr, 0, search_len - 1, search_len);
	printf("�� ��° ���� ���� ã����� :");
	scanf_s("%d", &search);
	start = clock();
	find = selection(arr, 0, search_len-1, search);
	end = clock();
	cal_time = (float)(end - start);
	printf("�ҿ� �ð� : %.3f \n", cal_time);
	for (int i = 0; i < 12; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("����� ã�� ���� %d�Դϴ� \n", find);
	return 0;
}