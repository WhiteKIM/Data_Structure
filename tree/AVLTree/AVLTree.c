#include <stdio.h>
#include <stdlib.h>

/*
@ 2020.10.18
@ AVL트리의 삽입, 삭제 연산 구현
*/

//AVLNode 구조체선언
//int형의 데이터와 AVLNode구조체 left right가 선언
typedef struct AVLNode
{
	int key;
	struct AVLNode* left, * right;
}AVLNode;

/*
@ 정수값 비교후 값이 큰 변수를 반환함
*/
int MAX(int a, int b)
{
	return (a > b) ? a : b;
}

/*
@ 트리의 높이를 반환하는 함수
@ 자기자신에 node->left연산과 node->right연산을 입력하는 재귀함수
@ 최종적으로 height에 좌우 둘중 가장 높은 높이의 값에 1을 더하여 저장
@ 반환값 정수형인 height
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
@ 트리의 균형도를 반환하는 함수
@ 노드의 좌우 높이값을 뺀 값만큼을 반환
*/
int get_balance(AVLNode* node)
{
	if (node == NULL)
		return 0;
	
	return get_height(node->left) - get_height(node->right);
}

/*
@ 트리노드를 생성하는 함수
@ 호출시 key값을 입력받아 노드의 key값에 저장
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
@ 트리의 값을 오른쪽으로 회전시켜주는 함수
@ parent노드의 왼쪽노드를 child노드로 선언후 child의 오른쪽 노드를 저장
@ 저장된 child의 오른쪽 노드값에 부모노드의 값을 저장후 child노드 반환
*/
AVLNode* rotate_right(AVLNode* parent)
{
	AVLNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child;
}

/*
@ 트리의 값을 왼쪽으로 회전시키는 함수
@ child노드를 선언후 parent->right 값 저장
@ parent->right노드에 child의 left노드값을 저장함
@ child->left노드에 parent값을 저장후 child값 반환
*/
AVLNode* rotate_left(AVLNode* parent)
{
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

/*
@ AVL트리의 삽입 연산
@ 노드와 key값을 입력받아 저장
@ 균형값을 비교하여 균형이 맞지 않으면 회전 연산들을 통해 균형을 맞춤
@ 균형이 잡히면 node를 반환함
*/
AVLNode* insert(AVLNode* node, int key)
{
	if (node == NULL)	//노드가 없을경우 생성
	{
		return (create_Node(key));
	}

	if (key < node->key)	//key가 node의 key값보다 작을 경우 왼쪽으로 이동
	{
		node->left = insert(node->left, key);
	}
	else if (key > node->key)	//key값이 node의 key값보다 클 경우 오른쪽으로 이동하여 수행
	{
		node->right = insert(node->right, key);
	}
	else	//key값과 노드의 key값이 같으면 저장하지 않음 중복값 저장 X
	{
		return node;
	}

	int balance = get_balance(node);

	if (balance > 1 && key < node->left->key)	//왼쪽으로 치우친 경우
		return rotate_right(node);

	if (balance < -1 && key > node->right->key)	//오른쪽으로 치우친 경우
		return rotate_left(node);

	if (balance > 1 && key > node->left->key)	//왼쪽 자식노드의 값이 오른쪽으로 치우친 경우
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && key < node->right->key)	// 오른쪽 자식 노드의 값이 왼쪽으로 치우친 경우
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

/*
@ AVLNode트리의 삭제 연산 함수
@ 삭제할 key값을 받아 node에서 찾은 후 제거
@ 제거가 끝나면 다시 균형잡힌 트리로 정렬
@ 동작이 끝나면 node값 반환
*/
AVLNode* Delete(AVLNode* node, int key)
{
	AVLNode* temp=NULL;	//임시로 사용될 AVLNode값

	if (node == NULL)	//노드가 비었다면 반환
	{
		return node;
	}
	if (key < node->key)	//key값이 node에 저장된 key보다 작으면node의 왼쪽값을 재귀호출함 
	{
		Delete(node->left, key);
	}

	if (key > node->key)	//key값이 노드에 저장된 key보다 크면 node의 오른쪽값을 재귀호출
	{
		Delete(node->right, key);
	}

	if (key == node->key)	//key값과 node의 key값이 같을 경우
	{
		if (node->left == NULL || node->right == NULL)	//node의 왼쪽값과 오른쪽값 중 하나라도 비었으면
		{
			if (node->left==NULL)	//왼쪽이 비었을 경우 오른쪽값을 temp에 저장
			{
				temp = node->right;
			}
			else	//오른쪽이 비어있을 경우 왼쪽값을 temp에 저장
			{
				temp = node->left;
			}

			if (temp == NULL)	//양쪽 모두 비어있을 경우 node값을 temp에 저장후 node에 null값 저장
			{
				temp = node;
				node = NULL;
			}
			else //비어있지 않았다면 temp값을 node에 저장
			{
				node = temp;
			}
		}
		else	//정수형 tempkey 선언후 node의 오른쪽값중 가장 낮은값 찾아 저장후 원본 노드 삭제
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

	//insert연산의 연산과 동일

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

//전위순회함수
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
@ 삭제된 노드를 대신할 노드를 찾는 함수
@ 노드에서 가장 작은 값을 찾아 low에 저장하여 반환
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
@ Main함수 부분
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