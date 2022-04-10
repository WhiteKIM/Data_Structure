#include <stdio.h>
#include "stack.h"

int main(void)
{
	Stack s;
	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("1 : %d \n", pop(&s));
	printf("2 : %d \n", pop(&s));
	printf("3 : %d \n", pop(&s));

	free(s.data);
	return 0;
}