/*
* @ 5413970 ��ǻ�Ͱ��а� ����
* @ ������ �ڵ� ���� �����Լ�
* @ 2022.04.21
*/

#include <stdio.h>
#include "Heap.h"

int main(void)
{
	char list[] = {'A', 'T','G','C'};
	int freq[] = { 450,90,120,270};
	huffmanTree(freq, list, 4);
	return 0;
}