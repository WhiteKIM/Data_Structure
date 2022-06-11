#include <stdio.h>
#include <limits.h>

int matrix_Chain(int array[4][2])
{
	int result[4][4] = {
		{100000, 100000, 100000, 100000},
		{100000, 100000, 100000, 100000},
		{100000, 100000, 100000, 100000},
		{100000, 100000, 100000, 100000},
	}; //결과값을 저장하는 배열


	for (int L = 0; L < 4; L++)
	{
		for (int i = 0; i < 4 - L; i++)
		{
			int j = i + L;
			if(i==j)
				result[i][i] = 0;
			else
			{
				result[i][j] = INT_MAX;
				for (int k = i; k < j; k++)
				{
					int temp = result[i][k] + result[k + 1][j] + (array[i][0] * array[k][1] * array[j][1]);
					if (temp < result[i][j]) //값을 비교하여 최소값을 저장
					{
						result[i][j] = temp;
					}
				}
			}
		}
	}

	//수행된 결과가 저장된 2차원 배열 출력
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}

	//우리가 원하는 결과값의 위치
	return result[0][3];
}

int main(void)
{
	//수행할 행렬의 크기가 저장됨
	int arr[4][2] = {
		{10, 20},
		{20, 5},
		{5, 15},
		{15, 30},
	};
	printf("결과는 %d \n", matrix_Chain(arr));
	return 0;
}