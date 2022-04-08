/*
@ �迭�� ������ �׷���
@ 2020.11.23
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"

int DFS_Visit[100];	//DFS�Լ����� �̿�Ǵ� �迭
int BFS_Visit[100];	//BFS�Լ����� �̿�Ǵ� �迭

typedef struct Graph {
	int V;
	int E;
	int** Adj;
}Graph;

/*
@ Graph�� �����ϴ� �Լ�
@ rand�Լ��� ���� ������ �׷����� ������
@ �׷����� �ּ� 5���� ũ�� 11���ٴ� ���� �׷����� ������
*/
Graph* AdjMatrix()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	int v, e;

	if (!G)
	{
		printf("�޸� ����");
		exit(0);
	}

	while (1) 
	{
		v = rand() % 11;
		e = rand() % 11;

		if (v < 5 && e < 5)
		{
			continue;
		}
		else
			break;
	}

	G ->V = v;
	G->E = e;
	G->Adj = (int**)malloc(sizeof(int*) * G->V);

	for (int i = 0; i < G->V; i++)
	{
		G->Adj[i] = malloc(sizeof(int) * G->V);
	}

	for (int i = 0; i < G->V; i++)
	{
		for (int j = 0; j < G->V; j++)
		{
			G->Adj[i][j] = 0;
		}
	}

	return G;
}

/*
@  �׷����� ���� �����ϴ� �Լ�
@ int�� ���� 2���� �Է¹޾� �� ���� ���� ���߹迭�� ��ġ�� ����
@ 2�߹迭�� ������ ��ġ���� 1�� ����
*/
Graph* insert(Graph* G, int u, int v)
{
	if (u >= G->V || v >= G->V)
	{
		printf("No vertex");
		exit(0);
	}

	G->Adj[u][v] = 1;

	return G;
}

//�⺻���� �׷��� ����Լ�
void print_adj_mat(Graph* G)
{
	for (int i = 0; i < G->V; i++)
	{
		for (int j = 0; j < G->V; j++)
		{
			printf(" %d ", G->Adj[i][j]);
		}
		printf("\n");
	}
}

//�׷����� �����ϴ� �Լ�
void deleteMatrix(Graph* G)
{
	for (int i = 0; i < G->V; i++)
	{
		free(G->Adj[i]);
	}

	free(G->Adj);
	free(G);
}

/*
@ DFSŽ�� �Լ�
@ ���߹迭�� ���� DFS_Visit�� ���� null�� �ƴ϶��
@ ���������� Ž���� ������
*/
void DFS(Graph* G, int v)
{

	DFS_Visit[v] = true;

	printf("���� %d ->", v);

	for (int i = 0; i < G->V; i++)
	{
		if (G->Adj[v][i] && !DFS_Visit[i])
		{
			DFS(G, i);
		}
	}
}


/*
@ BFSŽ�� �Լ�
@ ť�� ����ϸ� Ž���� �ݺ����� ���� �� ���� Ž��
*/
void BFS(Graph* G, int v)
{
	QueueType Q;

	queue_init(&Q);
	BFS_Visit[v] = true;

	printf("%d �湮 -> ", v);
	enqueue(&Q, v);

	while (!is_empty(&Q))
	{
		v = dequeue(&Q);

		for (int i = 0; i < G->V; i++)
		{
			if (G->Adj[v][i] && !BFS_Visit[i])
			{
				BFS_Visit[i] = true;
				printf("%d �湮 -> ", i);
				enqueue(&Q, i);
			}
		}
	}
}

//�����Լ�
int main(void)
{
	Graph* mygraph;
	mygraph = AdjMatrix();

	for (int i = 0; i < mygraph->V; i++)
	{
		for (int j = 0; j < mygraph->V; j++)
		{
		
			if(rand()%2==0)	//������ �׷��� ���� ������
			{
				insert(mygraph, i, j);
			}
		}
	}

	print_adj_mat(mygraph);

	printf("���� �켱 Ž�� \n");
	DFS(mygraph, 0);

	printf("�ʺ� �켱 Ž�� \n");
	BFS(mygraph, 0);

	deleteMatrix(mygraph);

	return 0;
}
