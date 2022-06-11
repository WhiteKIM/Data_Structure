#include <stdio.h>
#include <limits.h>

int matrix_Chain(int array[4][2])
{
	int result[4][4] = {
		{100000, 100000, 100000, 100000},
		{100000, 100000, 100000, 100000},
		{100000, 100000, 100000, 100000},
		{100000, 100000, 100000, 100000},
	}; //������� �����ϴ� �迭


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
					if (temp < result[i][j]) //���� ���Ͽ� �ּҰ��� ����
					{
						result[i][j] = temp;
					}
				}
			}
		}
	}

	//����� ����� ����� 2���� �迭 ���
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", result[i][j]);
		}
		printf("\n");
	}

	//�츮�� ���ϴ� ������� ��ġ
	return result[0][3];
}

int main(void)
{
	//������ ����� ũ�Ⱑ �����
	int arr[4][2] = {
		{10, 20},
		{20, 5},
		{5, 15},
		{15, 30},
	};
	printf("����� %d \n", matrix_Chain(arr));
	return 0;
}