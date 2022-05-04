/*
* @ 5413970 ��ǻ�Ͱ��а� ����
* @ 2020.4.21
* @ �ּ� �켱���� ť �� ������ ���� ���� ����
*/
#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

//Heap �����Լ�
Heap* create()
{
	return (Heap*)malloc(sizeof(Heap));
}

//Heap �ʱ�ȭ, �� ����� 0���� ����
void init(Heap* h)
{
	h->heap_size = 0;
}

//�ּҿ켱���� ť�� �����͸� �ִ� �Լ�
//���� ���Ͽ� �Էµ� �����Ͱ� ������ ���� �迭�� ������ ��ġ ����
//������ ������ ���� ������ �Է�
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


//������ �����͸� �����ϴ� �Լ�
//�����Ͱ� ���ŵǸ� ���� ������ ���� �� �����Ƿ� �׿� ���� ���� ����
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

//Ʈ�� ����
TreeNode* makeTree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

//������ ���� ����
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

//Ʈ���� ���ĸ� ����� �� ��ȯ
int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}

//������ �ڵ� ���
void printArray(int code[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d", code[i]);
	}
	printf("\n");
}

//�ڵ带 �����ϰ� ����ϴ� �Լ�
//���� ���� 0, ���� ���� 1�� �����Ͽ� �������� �ڵ带 ����
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

//������ Ʈ���� �����ϴ� ������ ������ �Լ�
//Ʈ���� ���� �����ϰ� �迭�� ������ �����͸� �Է�
//���������� ������ �ڵ带 ����ϰ� Ʈ�� ����
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
