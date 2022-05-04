/*
* @ 5413970 컴퓨터공학과 김경규
* @ 2020.4.21
* @ 최소 우선순위 큐 및 허프만 연산 정의 구현
*/
#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

//Heap 생성함수
Heap* create()
{
	return (Heap*)malloc(sizeof(Heap));
}

//Heap 초기화, 힙 사이즈를 0으로 설정
void init(Heap* h)
{
	h->heap_size = 0;
}

//최소우선순위 큐에 데이터를 넣는 함수
//값을 비교하여 입력된 데이터가 작으면 현재 배열의 데이터 위치 조정
//조정이 끝나면 힙에 데이터 입력
void insert_min_heap(Heap* h, element item)
{
	int i = ++(h->heap_size);
	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}


//힙에서 데이터를 제거하는 함수
//데이터가 제거되면 힙의 구조과 변할 수 있으므로 그에 대한 연산 진행
element delete_min_heap(Heap* h)
{
	int parent;
	int child;
	element item;
	element temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while(child <= h->heap_size)
	{
		if ((child <= h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
		{
			child++;
		}
		if (temp.key < h->heap[child].key)
		{
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//트리 생성
TreeNode* makeTree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

//생성된 츠리 제거
void destoryTree(TreeNode* root)
{
	if (root == NULL)
	{
		return;
	}
	destoryTree(root->left);
	destoryTree(root->right);
	free(root);
}

//트리의 이파리 노드일 때 반환
int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}

//생성된 코드 출력
void printArray(int code[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d", code[i]);
	}
	printf("\n");
}

//코드를 생성하고 출력하는 함수
//좌측 노드는 0, 우측 노드는 1로 설정하여 내려가며 코드를 생성
void printCode(TreeNode * root, int code[], int top)
{
	if (root->left)
	{
		code[top] = 0;
		printCode(root->left, code, top + 1);
	}
	if (root->right)
	{
		code[top] = 1;
		printCode(root->right, code, top + 1);
	}
	if (is_leaf(root))
	{
		printf("%c: ", root->ch);
		printArray(code, top);
	}
}

//허프만 트리를 구성하는 연산을 진행할 함수
//트리를 먼저 생성하고 배열에 저장한 데이터를 입력
//최종적으로 생성된 코드를 출력하고 트리 제거
void huffmanTree(int freq[], char list[], int n)
{
	TreeNode* node;
	TreeNode* x;
	Heap* h;
	element e;
	element e1;
	element e2;
	int code[100];
	int top = 0;

	h = create();
	init(h);

	for (int i = 0; i < n; i++)
	{
		node = makeTree(NULL, NULL);
		e.ch = node->ch = list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(h, e);
	}

	for (int i = 1; i < n; i++)
	{
		e1 = delete_min_heap(h);
		e2 = delete_min_heap(h);
		x = makeTree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		insert_min_heap(h, e);
	}
	e = delete_min_heap(h);
	printCode(e.ptree, code, top);
	destoryTree(e.ptree);
	free(h);
}
