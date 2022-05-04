#include <stdio.h>
#include <climits>

#define INF 1000L

int get_min(int D[10], int T[10], int n)
{
	int min = 0;
	int min_v = 0;
	min = INT_MAX;
	min_v = -1;
	for (int i = 0; i < n; i++)
	{
		if ((D[i] < min) && T[i] == -1)	//���� ������� �ʰ� min������ ������
		{
			min = D[i];
			min_v = i;
		}
	}
	return min_v;//�ּ� ���� ��ȯ
}

void dijkstra(int map[][10], int D[], int T[])
{
	int v;
	for (int i = 0; i < 10; i++)
	{
		D[i] = map[0][i];
		T[i] = -1;
	}
	D[0] = 0;	//������ ����ġ �ʱ�ȭ
	T[0] = 1;	//������ ����

	for(int x = 0; x<9; x++)
	{
		v = get_min(D, T, 10);
		T[v] = 1;
		for (int i = 0; i < 10; i++)
		{
			if (T[i] == -1 && (map[v][i] + D[v] < D[i]))
			{
				D[i] = map[v][i] + D[v];	//����� ����ġ�� ��������ġ�� ��� ����ġ ���� ���Ѱź��� ũ�� ���������� ��ü
			}
		}
	}
}

int main(void)
{
	//���� ���� ���� õ�� ���� �뱸 ���� ��� ���� �λ�
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

	int d[10] = {0,0,0,0,0,0,0,0,0,0};
	int t[10] = {0,0,0,0,0,0,0,0,0,0};
	int target = 0;

	dijkstra(map, d, t);

	printf("���� 0 ���� 1 ���� 2 õ�� 3 ���� 4 �뱸 5 ���� 6 ��� 7 ���� 8 �λ� 9 \n");
	printf("ã�� ���� ���� ���ڷ� �Է��Ͽ��ּ��� : ");
	scanf_s("%d", &target);
	if (0 <= target <= 9)
		printf("�������� ���� ��� ����ġ�� %d �Դϴ� \n", d[target]);
	else
		printf("�׷� ���� �����ϴ� \n");
	printf("���� 0 ���� 1 ���� 2 õ�� 3 ���� 4 �뱸 5 ���� 6 ��� 7 ���� 8 �λ� 9 \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", d[i]);
	}
	return 0;
}