/*
* 컴퓨터알고리즘_01
* 계명대학교 컴퓨터공학과 5413970 김경규
* 최종수정 2022.03.26
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
	//find_median(arr, search_len);	//중간값을 찾아서 사용
	//quickSort(arr, 0, search_len - 1, search_len);
	printf("몇 번째 작은 값을 찾을까요 :");
	scanf_s("%d", &search);
	start = clock();
	find = selection(arr, 0, search_len-1, search);
	end = clock();
	cal_time = (float)(end - start);
	printf("소요 시간 : %.3f \n", cal_time);
	for (int i = 0; i < 12; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("당신이 찾는 값은 %d입니다 \n", find);
	return 0;
}