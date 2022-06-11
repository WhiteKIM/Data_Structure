/*
@ ������
@ 2020.12.10
*/

#include <stdio.h>
#include <time.h>

#define SIZE 10 //�迭 ũ��


/*
@ �Է� �迭, ����, ����
@ ��ȯ ����
*/
void swap(int* arr, int num1, int num2)
{
	int temp = arr[num1];
	arr[num1] = arr[num2];
	arr[num2] = temp;
}

/*
@ �߰��� ����
@ �迭���� 3���� �����ͼ� �߰����� ������ ���� ��ȯ��
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
@ ������ �ϰ��� ������ ��ġ�� ������
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
@ �迭�� �ΰ��� ������ ���ȣ���ϸ� �����
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