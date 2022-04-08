/*
@ 배열로 구현된 그래프
@ 2020.11.23
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"

int DFS_Visit[100];	//DFS함수에서 이용되는 배열
int BFS_Visit[100];	//BFS함수에서 이용되는 배열

typedef struct Graph {
	int V;
	int E;
	int** Adj;
}Graph;

/*
@ Graph를 생성하는 함수
@ rand함수를 통해 랜덤한 그래프를 생성함
@ 그래프는 최소 5보다 크고 11보다는 작은 그래프로 생성됨
*/
Graph* AdjMatrix()
{
	Graph* G = (Graph*)malloc(sizeof(Graph));
	int v, e;

	if (!G)
	{
		printf("메모리 에러");
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
@  그래프에 값을 저장하는 함수
@ int형 정수 2개를 입력받아 그 값을 통해 이중배열의 위치를 결정
@ 2중배열의 지정된 위치값은 1로 저장
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

//기본적인 그래프 출력함수
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

//그래프를 제거하는 함수
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
@ DFS탐색 함수
@ 이중배열의 값과 DFS_Visit의 값이 null이 아니라면
@ 다음값으로 탐색을 진행함
*/
void DFS(Graph* G, int v)
{

	DFS_Visit[v] = true;

	printf("정점 %d ->", v);

	for (int i = 0; i < G->V; i++)
	{
		if (G->Adj[v][i] && !DFS_Visit[i])
		{
			DFS(G, i);
		}
	}
}


/*
@ BFS탐색 함수
@ 큐를 사용하며 탐색시 반복문을 통해 각 값을 탐색
*/
void BFS(Graph* G, int v)
{
	QueueType Q;

	queue_init(&Q);
	BFS_Visit[v] = true;

	printf("%d 방문 -> ", v);
	enqueue(&Q, v);

	while (!is_empty(&Q))
	{
		v = dequeue(&Q);

		for (int i = 0; i < G->V; i++)
		{
			if (G->Adj[v][i] && !BFS_Visit[i])
			{
				BFS_Visit[i] = true;
				printf("%d 방문 -> ", i);
				enqueue(&Q, i);
			}
		}
	}
}

//메인함수
int main(void)
{
	Graph* mygraph;
	mygraph = AdjMatrix();

	for (int i = 0; i < mygraph->V; i++)
	{
		for (int j = 0; j < mygraph->V; j++)
		{
		
			if(rand()%2==0)	//랜덤한 그래프 값을 설정함
			{
				insert(mygraph, i, j);
			}
		}
	}

	print_adj_mat(mygraph);

	printf("깊이 우선 탐색 \n");
	DFS(mygraph, 0);

	printf("너비 우선 탐색 \n");
	BFS(mygraph, 0);

	deleteMatrix(mygraph);

	return 0;
}
