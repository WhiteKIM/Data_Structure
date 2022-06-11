/*
* 정렬 및 관련되어 필요한 함수를 정의한 헤더파일
* 2022.03.26 whitekim
*/
#ifndef sorting
#define sorting

#include <stdio.h>

#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))	//swap기능을 위해 구현한 매크로기능

/*
* 두 정수값 중에서 큰 값을 반환하는 함수
* param(int, int)
* return int
*/
int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

/*
* 정렬 알고리즘 선택정렬
*/
void selectSort(int arr[], int search_len)
{
	int min_num = 100;
	int temp = 0;
	int index = 0;
	
	for (int i = 0; i < search_len-1; i++)
	{
		index = i;
		min_num = arr[i];
		for (int j = i + 1; j < search_len; j++)
		{
			if (arr[j] < min_num)
			{
				min_num = arr[j];
				index = j;
			}
		}
		temp = arr[index];
		arr[index] = arr[i];
		arr[i] = temp;
	}
}

/*
* 분할한 배열을 정렬하고 합치는 함수
*/
void merge(int arr[], int a, int pivot, int b, int length)
{
	int* list = malloc(length * sizeof(int));
	int left_index, right_index, index, l;
	left_index = a;
	right_index = pivot + 1;
	index = a;

	while (left_index <= pivot && right_index <= b)
	{

		if (arr[left_index] <= arr[right_index])
			list[index++] = arr[left_index++];
		else
			list[index++] = arr[right_index++];
	}

	if (left_index > pivot)
		for (l = right_index; l <= b; l++)
			list[index++] = arr[l];
	else
		for (l = left_index; l <= pivot; l++)
			list[index++] = arr[l];
	
	for (l = a; l <= b; l++)
		arr[l] = list[l];
	free(list);
}

/*
* 분할정복 합병 정렬 알고리즘
* a = 최좌측, b= 최우측
*/
void mergeSort(int arr[], int a, int b)
{
	int length = b + 1;
	if (a < b)
	{
		int pivot = (a + b) / 2;
		mergeSort(arr, a, pivot);
		mergeSort(arr, pivot + 1, b);
		merge(arr, a, pivot, b, length);
	}
}

/*
* 중간값을 찾는 함수
* 가장 큰 값과 작은 값을 더하여 중간값을 산출한 후 배열에서 그 값이 존재하는 지 확인
* param integer array integer
*/void find_median(int arr[], int length)
{
	int min = 100000000;
	int max = 0;
	int median = 0;
	int index = 0;
	int temp = 0;
	for (int i= 0; i < length; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}

		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	median = (max + min) / 2;
	for (median; median > 0; median--)
	{
		for (int i = 0; i < length; i++)
		{
			if (arr[i] == median)
			{
				index = i;
				SWAP(arr[0], arr[i], temp);
				return;
			}
		}
	}
}

/*
* 분할정복 퀵 정렬 알고리즘
* 배열의 좌우측에서부터 pivot값과 비교하여 값들을 정렬
* 정렬이 끝나면 현재 right_index값을 반환
* param integer array, integer, integer
* return integer
*/
int quick(int arr[], int left, int right, int length)
{
	int left_index = left;
	int right_index = right+1;
	int temp;
	int pivot;

	pivot = arr[left]; //첫번째 배열값을 pivot으로 결정
	left_index++;
	right_index--;

	while (left_index < right_index)
	{
		while (arr[left_index] < pivot)
		{
			left_index++;
		}
		while (arr[right_index] > pivot)
		{
			right_index--;
		}
		if (left_index < right_index)
		{
			SWAP(arr[left_index], arr[right_index], temp);
		}
	}
	SWAP(arr[left], arr[right_index], temp);
	return right_index;
}

/*
* 분할정복 퀵정렬 알고리즘
* a는 최좌측 b는 최우측, arr은 정렬할 대상
* param integer array, integer, integer , integer
*/
void quickSort(int arr[], int a, int b, int length)
{
	if (a < b)
	{
		int pivot = quick(arr,a,b, length);
		quickSort(arr, a, pivot-1, length);
		quickSort(arr, pivot+1, b, length);
	}
}
 

int select_divide(int arr[], int left, int right)
{
	int pivot = left+rand()%(right-left+1);
	int temp;
	int left_index = left+1;
	int right_index = right;
	int pivot_data = arr[pivot];
	SWAP(arr[left], arr[pivot], temp);
	
	while (left_index <= right_index)
	{
		while (arr[left_index] <= pivot_data && left_index <= right)
		{
			left_index++;
		}
		while (arr[right_index] >= pivot_data && right_index >= left+1)
		{
			right_index--;
		}
		if (left_index <= right_index)
		{
			SWAP(arr[left_index], arr[right_index], temp);
		}
	}
	SWAP(arr[left], arr[right_index], temp);
	return right_index;
}

int selection(int arr[], int left, int right, int target)
{
	if (left == right)
		return arr[left];
	else
	{
		int pivot = select_divide(arr, left, right);
		int small = pivot - left;
		if (small >= target)
		{
			return selection(arr, left, pivot - 1, target);
		}
		else if (small + 1 == target)
		{
			return arr[pivot];
		}
		else
		{
			return selection(arr, pivot + 1, right, target - small-1);
		}
	}
	return -1;
}

#endif // !
