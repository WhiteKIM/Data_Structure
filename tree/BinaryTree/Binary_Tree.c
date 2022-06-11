#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RandBig() (rand() *rand())

typedef struct BSTree
{
	int key;
	struct BSTree* left, *right;
}BSTree;

BSTree* create_Tree(int key)
{
	BSTree* node = (BSTree*)malloc(sizeof(BSTree));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

BSTree* insert(BSTree* node, int key)
{
	if (node == NULL)
	{
		return create_Tree(key);
	}

	if (key < node->key)
	{
		node->left = insert(node->left, key);
	}
	if (key > node->key)
	{
		node->right = insert(node->right, key);
	}

	return node;
}

BSTree *Search(BSTree* node, int key, int count)
{
	clock_t t1, t2;
	t1 = clock();
	if (node == NULL)
	{
		return NULL;
	}
	
	if (key = node->key)
	{
		t2 = clock();
		printf("%lf ns %d \n",(double)((t1 - t2) / CLOCKS_PER_SEC), count);
		return node;
	}
	else if (key < node->key)
	{
		return	Search(node->left, key, count);
	}
	else
	{
		return Search(node->right, key, count);
	}
}

int main(void)
{
	BSTree* root = NULL;
	int num = 500;
	
	for (int i = 0; i < 10000; i++)
	{
		if (num ==10000)
			break;

		for (int j = 0; j < num; j++)
		{
			root=insert(root, RandBig());
		}
		Search(root, rand(), num);
		num += 500;
	}
	return 0;
}