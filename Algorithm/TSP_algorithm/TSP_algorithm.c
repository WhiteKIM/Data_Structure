/*
* @ Prim을 이용하여 MST을 생성한 후 중복되는 점을 제거하여 해결
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10	//그래프의 최대 크기
#define INF 1000L	//무한대를 표시

int D[MAX_SIZE];	//가중치를 저장하는 배열
int T[MAX_SIZE];	//방문한 곳을 기록하는 배열

//그래프 구조체 선언
typedef struct
{
	int v;	//점의 개수
	int map[MAX_SIZE][MAX_SIZE];	//그래프는 2차원배열로 이루어짐
}Graph;

//현재 가장 작은 가중치를 찾는 함수
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
* Prim 알고리즘 함수
* 인자값 (그래프 구조체와 시작점)
*/
int (*Prim(Graph* g, int p))[3]
{
	int v;
	static int node[MAX_SIZE][3];
	for (int i = 0; i < g->v; i++)
	{
		D[i] = INF;	//갈수 없는 곳의 가중치는 무한대
		T[i] = -1;	//방문하지 않았다는 표시로 -1을 저장
	}

	D[p] = 0;	//시작점의 가중치를 0으로 설정
	for (int i = 0; i < g->v; i++)
	{
		v = min_vertex(g->v);	//가장 작은 가중치를 가지는 정점
		T[v] = 1;	//방문표시

		if (D[v] == INF)//함수를 진행할 수 없는 경우
			return;
		printf("현재 정점 : %d \n", v);	//방문한 정점을 화면에 출력
		for (int j = 0; j < g->v; j++)
		{
			if (g->map[v][j] != INF)
			{
				if (T[j] == -1 && g->map[v][j] < D[j])	//방문하지 않았고 그래프의 가중치가 기록된 가중치보다 작은 경우
				{
					D[j] = g->map[v][j];	//가중치 업데이트
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
* 메인함수
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
	int pivot = (rand() % 6 + 1) - 1;	//랜덤으로 시작할 점을 선택
	int (*node)[3] = Prim(&g, pivot);
	int cost = 0;	//가중치 합을 저장할 변수

	//가중치 합을 구함
	for (int i = 0; i < 6; i++)
	{
		cost += D[i];
	}
	printf("MST값 \n");
	for (int i = 0; i < 5; i++)
	{
		printf("%d %d %d \n", node[i][0], node[i][1], node[i][2]);
	}
	printf("cost is %d \n", cost);
	TSP(node);
	return 0;
}