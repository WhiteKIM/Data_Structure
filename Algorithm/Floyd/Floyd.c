/*
* @ �÷��̵�-���� �˰���
* @ �Է¹����� ���縦 �����Ͽ���
*/

#include <stdio.h>
#include <time.h>
#include <Windows.h>

#define INF 1000L
#define WIDTH 10
#define HEIGHT 10

int get_min(int D[][HEIGHT], int T[][HEIGHT], int n)
{
	int min = 0;
	int min_v = 0;
	min = INT_MAX;
	min_v = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((D[i][j] < min) && T[i][j] == -1)	//���� ������� �ʰ� min������ ������
			{
				min = D[i][j];
				min_v = i;
			}
		}
	}
	return min_v;//�ּ� ���� ��ȯ
}

void dijkstra(int map[][HEIGHT], int D[][HEIGHT], int T[][HEIGHT])
{
	int v;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			D[i][j] = map[i][j];
			T[i][j] = -1;
		}
	}
	D[0][0] = 0;	//������ ����ġ �ʱ�ȭ
	T[0][0] = 1;	//������ ����

	for (int k = 0; k < HEIGHT; k++)
	{
		for (int x = 0; x < HEIGHT; x++)
		{
			v = get_min(D, T, HEIGHT);
			T[x][v] = 1;
			for (int i = 0; i < HEIGHT; i++)
			{
				if (T[x][i] == -1 && (map[v][i] + D[x][v] < D[x][i]))
				{
					D[x][i] = map[v][i] + D[x][v];	//����� ����ġ�� ��������ġ�� ��� ����ġ ���� ���Ѱź��� ũ�� ���������� ��ü
				}
			}
		}
	}
}

int min_num(int x, int y)
{
	if (x >= y)
		return y;
	else
		return x;
}

int* floyd(int arr[][HEIGHT], int num)
{
	int (*destination)[HEIGHT] = arr;
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			for (int k = 0; k < num; k++)
			{
				destination[j][k] = min_num(destination[j][k], (destination[j][i] + destination[i][k]));
			}
		}
	}
	return (int*)destination;
}

int main(void)
{
	clock_t start, end;
	clock_t start1, end1;
	int map[10][10] = {
		{0,15,INF,12,INF,INF,INF,INF,INF,INF},//����
		{15 , 0, 21, INF, INF,7,INF,INF,INF,INF},//����
		{INF,21,0,INF,INF,INF,25,INF,INF, INF},//����
		{12,INF,INF,0,10,INF,INF,4,INF,INF},//õ��
		{INF,INF,INF,10, 0, 10, INF, 3, INF, INF},//����
		{INF, 7, INF, INF, 10, 0, 19, INF, INF, 9},//�뱸
		{INF,INF,25,INF,INF,19,0, INF,INF,5},//����
		{INF,INF,INF,4,3,INF,INF,0,13,INF},//���
		{INF,INF,INF,INF,INF,INF,INF,13,0,15},//����
		{INF, INF, INF, INF, INF, 9, 5, INF, 15, 0}//�λ�
	};
	int d[WIDTH][HEIGHT] = { 
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};
	int t[WIDTH][HEIGHT] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};
	int target = 0;
	start = clock();
	int (*graph)[HEIGHT] = (void*)floyd(map, HEIGHT);
	end = clock();
	start1 = clock();
	dijkstra(map, d, t);
	end1 = clock();
	printf("floyd result \n");
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			printf("%d ", graph[x][y]);
		}
		printf("\n");
	}
	printf("dijk result \n");
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			printf("%d ", d[x][y]);
		}
		printf("\n");
	}
}