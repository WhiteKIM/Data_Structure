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
		if ((D[i] < min) && T[i] == -1)	//점이 저장되지 않고 min값보다 작으면
		{
			min = D[i];
			min_v = i;
		}
	}
	return min_v;//최소 정점 반환
}

void dijkstra(int map[][10], int D[], int T[])
{
	int v;
	for (int i = 0; i < 10; i++)
	{
		D[i] = map[0][i];
		T[i] = -1;
	}
	D[0] = 0;	//시작점 가중치 초기화
	T[0] = 1;	//시작점 저장

	for(int x = 0; x<9; x++)
	{
		v = get_min(D, T, 10);
		T[v] = 1;
		for (int i = 0; i < 10; i++)
		{
			if (T[i] == -1 && (map[v][i] + D[v] < D[i]))
			{
				D[i] = map[v][i] + D[v];	//저장된 가중치가 정점가중치와 경로 가중치 합을 더한거보다 크면 작은값으로 교체
			}
		}
	}
}

int main(void)
{
	//서울 원주 강릉 천안 대전 대구 포항 논산 광주 부산
	int map[10][10] = {
		{0,15,INF,12,INF,INF,INF,INF,INF,INF},//서울
		{15 , 0, 21, INF, INF,7,INF,INF,INF,INF},//원주
		{INF,21,0,INF,INF,INF,25,INF,INF, INF},//강릉
		{12,INF,INF,0,10,INF,INF,4,INF,INF},//천안
		{INF,INF,INF,10, 0, 10, INF, 3, INF, INF},//대전
		{INF, 7, INF, INF, 10, 0, 19, INF, INF, 9},//대구
		{INF,INF,25,INF,INF,19,0, INF,INF,5},//포항
		{INF,INF,INF,4,3,INF,INF,0,13,INF},//논산
		{INF,INF,INF,INF,INF,INF,INF,13,0,15},//광주
		{INF, INF, INF, INF, INF, 9, 5, INF, 15, 0}//부산
	};

	int d[10] = {0,0,0,0,0,0,0,0,0,0};
	int t[10] = {0,0,0,0,0,0,0,0,0,0};
	int target = 0;

	dijkstra(map, d, t);

	printf("서울 0 원주 1 강릉 2 천안 3 대전 4 대구 5 포항 6 논산 7 광주 8 부산 9 \n");
	printf("찾는 곳에 대해 숫자로 입력하여주세요 : ");
	scanf_s("%d", &target);
	if (0 <= target <= 9)
		printf("목적지에 대한 경로 가중치는 %d 입니다 \n", d[target]);
	else
		printf("그런 곳은 없습니다 \n");
	printf("서울 0 원주 1 강릉 2 천안 3 대전 4 대구 5 포항 6 논산 7 광주 8 부산 9 \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", d[i]);
	}
	return 0;
}