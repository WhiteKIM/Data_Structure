#include <stdio.h>
#include <stdlib.h>

/*
@ 2020.10.18
@ AVLƮ���� ����, ���� ���� ����
*/

//AVLNode ����ü����
//int���� �����Ϳ� AVLNode����ü left right�� ����
typedef struct AVLNode
{
	int key;
	struct AVLNode* left, * right;
}AVLNode;

/*
@ ������ ���� ���� ū ������ ��ȯ��
*/
int MAX(int a, int b)
{
	return (a > b) ? a : b;
}

/*
@ Ʈ���� ���̸� ��ȯ�ϴ� �Լ�
@ �ڱ��ڽſ� node->left����� node->right������ �Է��ϴ� ����Լ�
@ ���������� height�� �¿� ���� ���� ���� ������ ���� 1�� ���Ͽ� ����
@ ��ȯ�� �������� height
*/
int get_height(AVLNode *node)
{
	int height = 0;

	if (node != NULL)
	{
		height = 1 + MAX(get_height(node->left), get_height(node->right));
	}
	return height;
}

/*
@ Ʈ���� �������� ��ȯ�ϴ� �Լ�
@ ����� �¿� ���̰��� �� ����ŭ�� ��ȯ
*/
int get_balance(AVLNode* node)
{
	if (node == NULL)
		return 0;
	
	return get_height(node->left) - get_height(node->right);
}

/*
@ Ʈ����带 �����ϴ� �Լ�
@ ȣ��� key���� �Է¹޾� ����� key���� ����
*/
AVLNode* create_Node(int key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

/*
@ Ʈ���� ���� ���������� ȸ�������ִ� �Լ�
@ parent����� ���ʳ�带 child���� ������ child�� ������ ��带 ����
@ ����� child�� ������ ��尪�� �θ����� ���� ������ child��� ��ȯ
*/
AVLNode* rotate_right(AVLNode* parent)
{
	AVLNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child;
}

/*
@ Ʈ���� ���� �������� ȸ����Ű�� �Լ�
@ child��带 ������ parent->right �� ����
@ parent->right��忡 child�� left��尪�� ������
@ child->left��忡 parent���� ������ child�� ��ȯ
*/
AVLNode* rotate_left(AVLNode* parent)
{
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

/*
@ AVLƮ���� ���� ����
@ ���� key���� �Է¹޾� ����
@ �������� ���Ͽ� ������ ���� ������ ȸ�� ������� ���� ������ ����
@ ������ ������ node�� ��ȯ��
*/
AVLNode* insert(AVLNode* node, int key)
{
	if (node == NULL)	//��尡 ������� ����
	{
		return (create_Node(key));
	}

	if (key < node->key)	//key�� node�� key������ ���� ��� �������� �̵�
	{
		node->left = insert(node->left, key);
	}
	else if (key > node->key)	//key���� node�� key������ Ŭ ��� ���������� �̵��Ͽ� ����
	{
		node->right = insert(node->right, key);
	}
	else	//key���� ����� key���� ������ �������� ���� �ߺ��� ���� X
	{
		return node;
	}

	int balance = get_balance(node);

	if (balance > 1 && key < node->left->key)	//�������� ġ��ģ ���
		return rotate_right(node);

	if (balance < -1 && key > node->right->key)	//���������� ġ��ģ ���
		return rotate_left(node);

	if (balance > 1 && key > node->left->key)	//���� �ڽĳ���� ���� ���������� ġ��ģ ���
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && key < node->right->key)	// ������ �ڽ� ����� ���� �������� ġ��ģ ���
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

/*
@ AVLNodeƮ���� ���� ���� �Լ�
@ ������ key���� �޾� node���� ã�� �� ����
@ ���Ű� ������ �ٽ� �������� Ʈ���� ����
@ ������ ������ node�� ��ȯ
*/
AVLNode* Delete(AVLNode* node, int key)
{
	AVLNode* temp=NULL;	//�ӽ÷� ���� AVLNode��

	if (node == NULL)	//��尡 ����ٸ� ��ȯ
	{
		return node;
	}
	if (key < node->key)	//key���� node�� ����� key���� ������node�� ���ʰ��� ���ȣ���� 
	{
		Delete(node->left, key);
	}

	if (key > node->key)	//key���� ��忡 ����� key���� ũ�� node�� �����ʰ��� ���ȣ��
	{
		Delete(node->right, key);
	}

	if (key == node->key)	//key���� node�� key���� ���� ���
	{
		if (node->left == NULL || node->right == NULL)	//node�� ���ʰ��� �����ʰ� �� �ϳ��� �������
		{
			if (node->left==NULL)	//������ ����� ��� �����ʰ��� temp�� ����
			{
				temp = node->right;
			}
			else	//�������� ������� ��� ���ʰ��� temp�� ����
			{
				temp = node->left;
			}

			if (temp == NULL)	//���� ��� ������� ��� node���� temp�� ������ node�� null�� ����
			{
				temp = node;
				node = NULL;
			}
			else //������� �ʾҴٸ� temp���� node�� ����
			{
				node = temp;
			}
		}
		else	//������ tempkey ������ node�� �����ʰ��� ���� ������ ã�� ������ ���� ��� ����
		{
			int tempkey = FindValue(node->right);
			node->key = tempkey;
			node->right = Delete(node->right, tempkey);
		}
	}
	
	if (node == NULL)
	{
		return node;
	}

	//insert������ ����� ����

	int balance = get_balance(node);

	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	if (balance < -1 && key > node->right->key)
		return rotate_left(node);

	if (balance > 1 && key > node->left->key)
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

//������ȸ�Լ�
void preorder(AVLNode* node)
{
	if (node != NULL)
	{
		printf(" [%d] ", node->key);
		preorder(node->left);
		preorder(node->right);
	}
}

/*
@ ������ ��带 ����� ��带 ã�� �Լ�
@ ��忡�� ���� ���� ���� ã�� low�� �����Ͽ� ��ȯ
*/
int FindValue(AVLNode* node)
{
	int low = 0;
	if (node != NULL)
	{
		if (node->left != NULL)
		{
			FindValue(node->left);
		}
		else
		{
			low = node->key;
		}
	}
	return low;
}

/*
@ Main�Լ� �κ�
*/
int main(void)
{
	AVLNode* root = NULL;

	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 29);

	preorder(root);
	printf("\n Delete \n");
	Delete(root, 30);
	preorder(root);

	return 0;
}