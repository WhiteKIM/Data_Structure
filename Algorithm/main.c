/*
* @ 5413970 컴퓨터공학과 김경규
* @ 허프만 코드 구현 메인함수
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