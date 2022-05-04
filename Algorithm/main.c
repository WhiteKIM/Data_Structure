#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//arr�� �� ������ ���� ��ǥ��, node�� ȭ�鿡 � ���� ����Ǿ����� ǥ��
int arr[] = {0,1,2,3,4,5,6};
int** node;

//����ü ���� �����κ�
typedef struct {
	int weight;	//����ġ
	int start;	//������
	int end;	//����
}element;

//����ü �� ����
typedef struct
{
	element heap[MAX_SIZE];	//���� �迭
	int size;	//���� ũ��
}Heap;

//�� ���� ����
Heap* create()
{
	return (Heap*)malloc(sizeof(Heap));
}

//������� ����, �� ũ�� ����
Heap* changeSize(int size)
{
	return (Heap*)malloc(sizeof(Heap));
}

//�� �ʱ�ȭ, ���� ũ��� 0�������� ����
void init(Heap* h)
{
	h->size = 0;
}

//���� �� �ֱ�, element�� �޾� ���� ������
//element�� ����ġ�� ���Ͽ� ���� ���� �տ� ��
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

//���� ���� �ֱ���element�� �� ���� ����
//�� ���� ����ġ�� ���� �� ���� �����ϴ� �Լ� ����
void insert_edge(Heap* h, int u, int v, int weight)
{
	element ment;
	ment.start = u;
	ment.end = v;
	ment.weight = weight;
	insert(h, ment);
}

//���� ������ ������ �Լ�
//���� ����ġ�� ���Ͽ� ���� ������ ����
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

//������� ����, �� ���� �Լ�
//���� ����� ���ĵ��� �ʾ� ������� �ʾ���
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

//���� ��Ʈ�� ��ǥ���� �������� �� �´ٸ� ��ǥ�� ��ȯ �ƴϸ� ��������� ȣ��
int find(int u)
{
	if (u != arr[u])
	{
		arr[u] = find(arr[u]);
	}
	return arr[u];
}

//U,V���� �޾ƿ� ��ǥ���� ���ϸ�
//��ǥ���� ���ٸ� ����Ǿ�����
void Union(int u, int v)
{
	int root1 = find(u);
	int root2 = find(v);
	arr[root2] = root1;
}


/*
* �ּҽ���Ʈ�� ���� ����
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
	printf("����ġ�� %d \n", cost);
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
		printf("%d��° ", i+1);
		for (int j = 0; j < 2; j++)
		{
			printf(" %d ", node[i][j]);
		}
		printf("\n");
	}

	free(heap);
	return 0;
}