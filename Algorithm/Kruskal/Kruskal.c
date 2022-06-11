#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//arr은 각 정점에 대한 대표값, node는 화면에 어떤 선이 연결되었는지 표시
int arr[] = {0,1,2,3,4,5,6};
int** node;

//구조체 선언 간선부분
typedef struct {
	int weight;	//가중치
	int start;	//시작점
	int end;	//종점
}element;

//구조체 힙 선언
typedef struct
{
	element heap[MAX_SIZE];	//간선 배열
	int size;	//힙의 크기
}Heap;

//힙 동적 생성
Heap* create()
{
	return (Heap*)malloc(sizeof(Heap));
}

//사용하지 않음, 힙 크기 변경
Heap* changeSize(int size)
{
	return (Heap*)malloc(sizeof(Heap));
}

//힙 초기화, 힙의 크기는 0에서부터 시작
void init(Heap* h)
{
	h->size = 0;
}

//힙에 값 넣기, element를 받아 힙에 저장함
//element의 가중치와 비교하여 작은 값이 앞에 옴
void insert(Heap* h, element item)
{
	int count = 0;
	count = ++(h->size);

	while ((count != 1) && (item.weight < h->heap[count / 2].weight))
	{
		h->heap[count] = h->heap[count / 2];
		count /= 2;
	}
	h->heap[count] = item;
}

//힙에 값을 넣기전element에 각 값을 저장
//각 점과 가중치를 받은 후 힙에 저장하는 함수 실행
void insert_edge(Heap* h, int u, int v, int weight)
{
	element ment;
	ment.start = u;
	ment.end = v;
	ment.weight = weight;
	insert(h, ment);
}

//값을 힙에서 빼오는 함수
//값의 가중치를 비교하여 작은 값부터 나옴
element delete(Heap* h)
{
	int parent;
	int child;

	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->size)];
	h->size = h->size - 1;
	parent = 1;
	child = 2;

	while (child <= h->size)
	{
		if ((child < h->size) && (h->heap[child].weight) > h->heap[child + 1].weight)
			child++;
		if (temp.weight <= h->heap[child].weight)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//사용하지 않음, 힙 정렬 함수
//값이 제대로 정렬되지 않아 사용하지 않았음
Heap* heapsort(Heap* h)
{
	Heap* temp_heap;
	temp_heap = create();
	element data;
	init(temp_heap);

	element list[10];
	int index = 0;

	while (h->size != 0)
	{
		data = delete(h);
		list[index] = data;
		index++;
	}
	for (int i = index-1; i >= 0; i--)
	{
		insert(temp_heap, list[i]);
	}

	return temp_heap;
}

//점이 루트의 대표값과 동일한지 비교 맞다면 대표값 반환 아니면 재귀적으로 호출
int find(int u)
{
	if (u != arr[u])
	{
		arr[u] = find(arr[u]);
	}
	return arr[u];
}

//U,V값을 받아와 대표값을 비교하며
//대표값이 같다면 연결되어있음
void Union(int u, int v)
{
	int root1 = find(u);
	int root2 = find(v);
	arr[root2] = root1;
}


/*
* 최소신장트리 연산 시작
*/
void kruskal(Heap * h, int N)
{
	int tree_nodes = 0;
	int cost = 0;
	int u, v, wt;
	int index = 0;
	element ment;

	while (tree_nodes < N - 1)
	{
		ment = delete(h);
		u = ment.start;
		v = ment.end;
		wt = ment.weight;
		if (find(u) != find(v))
		{
			Union(u, v);
			node[index][0] = u;
			node[index][1] = v;
			cost += wt;
			tree_nodes++;
			index++;
		}
	}
	printf("가중치는 %d \n", cost);
}

int main(void)
{
	Heap* heap;
	heap = create();
	init(heap);
	insert_edge(heap, 0, 1, 8);
	insert_edge(heap, 0, 4, 4);
	insert_edge(heap, 0, 3, 2);
	insert_edge(heap, 1, 3, 4);
	insert_edge(heap, 1, 2, 1);
	insert_edge(heap, 1, 5, 2);
	insert_edge(heap, 2, 5, 1);
	insert_edge(heap, 3, 4, 3);
	insert_edge(heap, 3, 5, 7);
	insert_edge(heap, 4, 5, 9);

	//heap = heapsort(heap);

	node = (int**)malloc(sizeof(int*) * 5);
	for (int i = 0; i < 6; i++)
	{
		node[i] = (int*)malloc(sizeof(int) * 2);
	}
	kruskal(heap, 6);
	for (int i = 0; i < 5; i++)
	{
		printf("%d번째 ", i+1);
		for (int j = 0; j < 2; j++)
		{
			printf(" %d ", node[i][j]);
		}
		printf("\n");
	}

	free(heap);
	return 0;
}
