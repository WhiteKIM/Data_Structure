/*
* @ Prim�� �̿��Ͽ� MST�� ������ �� �ߺ��Ǵ� ���� �����Ͽ� �ذ�
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10	//�׷����� �ִ� ũ��
#define INF 1000L	//���Ѵ븦 ǥ��

int D[MAX_SIZE];	//����ġ�� �����ϴ� �迭
int T[MAX_SIZE];	//�湮�� ���� ����ϴ� �迭

//�׷��� ����ü ����
typedef struct
{
	int v;	//���� ����
	int map[MAX_SIZE][MAX_SIZE];	//�׷����� 2�����迭�� �̷����
}Graph;

//���� ���� ���� ����ġ�� ã�� �Լ�
int min_vertex(int num)
{
	int v = 0;
	for (int i = 0; i < num; i++)
	{
		if (T[i] == -1)
		{
			v = i;
			break;
		}
	}
	for (int i = 0; i < num; i++)
	{
		if (T[i] == -1 && (D[i] < D[v]))
			v = i;
	}
	return (v);
}

/*
* Prim �˰��� �Լ�
* ���ڰ� (�׷��� ����ü�� ������)
*/
int (*Prim(Graph* g, int p))[3]
{
	int v;
	static int node[MAX_SIZE][3];
	for (int i = 0; i < g->v; i++)
	{
		D[i] = INF;	//���� ���� ���� ����ġ�� ���Ѵ�
		T[i] = -1;	//�湮���� �ʾҴٴ� ǥ�÷� -1�� ����
	}

	D[p] = 0;	//�������� ����ġ�� 0���� ����
	for (int i = 0; i < g->v; i++)
	{
		v = min_vertex(g->v);	//���� ���� ����ġ�� ������ ����
		T[v] = 1;	//�湮ǥ��

		if (D[v] == INF)//�Լ��� ������ �� ���� ���
			return;
		printf("���� ���� : %d \n", v);	//�湮�� ������ ȭ�鿡 ���
		for (int j = 0; j < g->v; j++)
		{
			if (g->map[v][j] != INF)
			{
				if (T[j] == -1 && g->map[v][j] < D[j])	//�湮���� �ʾҰ� �׷����� ����ġ�� ��ϵ� ����ġ���� ���� ���
				{
					D[j] = g->map[v][j];	//����ġ ������Ʈ
					node[j][0] = j;
					node[j][1] = v;
					node[j][2] = g->map[v][j];
				}
			}
		}
	}
	return node;
}

void TSP(int(*arr)[3])
{
	int path[MAX_SIZE];
	int TSP_Tree[MAX_SIZE];
	int count = 0;
	int index = 1;
	int i, j;
	for (int i = 0; i < 5; i++)
	{
		path[count++] = arr[i][0];
		path[count++] = arr[i][1];
	}
	printf("path \n");
	for (int i = 0; i < count; i++)
	{
		printf("%d ", path[i]);
	}
	printf("\n");
	TSP_Tree[0] = path[0];
	for (i = 1; i < count; i++)
	{
		for (j = 0; j < index; j++)
		{
			if (path[i] == TSP_Tree[j])
			{
				break;
			}
		}
		if (j == index)
		{
			TSP_Tree[index++] = path[i];
		}
	}
	TSP_Tree[index++] = TSP_Tree[0];
	printf("TSP_TREE \n");
	for (i = 0; i < index; i++)
	{
		printf("%d ", TSP_Tree[i]);
	}
}

/*
* �����Լ�
*/
int main(void)
{
	Graph g = { 6,
		{{0, 3, INF, 2, 4, INF},
		{3, 0, 1, 4, INF, 2},
		{INF, 1, 0, INF, INF, 1},
		{2, 4, INF, 0, 5, 7},
		{4, INF, INF, 5, 0, 9},
		{INF, 2, 1, 7, 9, 0}}
	};
	int pivot = (rand() % 6 + 1) - 1;	//�������� ������ ���� ����
	int (*node)[3] = Prim(&g, pivot);
	int cost = 0;	//����ġ ���� ������ ����

	//����ġ ���� ����
	for (int i = 0; i < 6; i++)
	{
		cost += D[i];
	}
	printf("MST�� \n");
	for (int i = 0; i < 5; i++)
	{
		printf("%d %d %d \n", node[i][0], node[i][1], node[i][2]);
	}
	printf("cost is %d \n", cost);
	TSP(node);
	return 0;
}