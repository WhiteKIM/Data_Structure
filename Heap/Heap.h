/*
* @ 2020.4.21 
* @ 최소 우선순위 큐 및 허프만 연산 정의 헤더
*/
#ifndef HEAP_H
#define HEAP_H

#define MAX_SIZE 100

typedef struct TreeNode
{
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;

}TreeNode;

typedef struct
{
	TreeNode* ptree;
	char ch;
	int key;
}element;

typedef struct
{
	element heap[MAX_SIZE];
	int heap_size;
}Heap;

Heap* create();
void init(Heap* h);
void insert_min_heap(Heap* h, element item);
element delete_min_heap(Heap* h);
TreeNode* makeTree(TreeNode* left, TreeNode* right);
void destoryTree(TreeNode* root);
int is_leaf(TreeNode* root);
void printArray(int code[], int n);
void printCode(TreeNode* root, int code[], int top);
void huffmanTree(int freq[], char list[], int n);

#endif
