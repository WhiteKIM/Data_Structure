/*
@ 퀵정렬
@ 2020.12.10
*/

#include <stdio.h>
#include <time.h>

#define SIZE 10 //배열 크기


/*
@ 입력 배열, 정수, 정수
@ 반환 없음
*/
void swap(int* arr, int num1, int num2)
{
	int temp = arr[num1];
	arr[num1] = arr[num2];
	arr[num2] = temp;
}

/*
@ 중간값 선정
@ 배열에서 3개의 가져와서 중간값을 가지는 수를 반환함
*/
int getMid(int* arr, int left, int right)
{
	int temp[3] = { left, (left + right) / 2, right };

	if (arr[temp[0]] > arr[temp[1]])
		swap(temp, 0, 1);

	if (arr[temp[1]] > arr[temp[2]])
		swap(temp, 1, 2);

	if (arr[temp[0]] > arr[temp[1]])
		swap(temp, 0, 1);

	return temp[1];
}

/*
@ 분할을 하고나서 값들을 위치를 조정함
*/
int partition(int* arr, int left, int right)
{
	int low, high, mid;
	mid = getMid(arr, left, right);
	int pivot = arr[mid];

	low = left+1;
	high = right;

	swap(arr, left, mid);

	while (low<=high)
	{
		while (arr[low] <= pivot)
		{
			low++;
		}

		while (arr[high] >= pivot)
		{
			high--;
		}

		if (low<=high)
		{
			swap(arr, low, high);
		}
	}
	swap(arr, left, high);
	return high;
}

/*
@ 배열을 두개로 나눈후 재귀호출하며 진행됨
*/
void Quick_Sort(int* arr, int left, int right)
{
	if (left <= right)
	{
		int pivot = partition(arr, left, right);
		Quick_Sort(arr, left, pivot - 1);
		Quick_Sort(arr, pivot+1, right);
	}
}

int main(void)
{
	int arr[SIZE] = {5,7,9,1,8,6,3,4,2};

	Quick_Sort(arr, 0, SIZE-1);
	
	for (int i = 0; i < SIZE; i++)
	{
		printf(" %d ",arr[i]);
	}

	return 0;
}