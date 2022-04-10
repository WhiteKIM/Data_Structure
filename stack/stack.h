#ifndef STACK_H
#define STACK_H

typedef int element;

typedef struct
{
	int top;
	int capacity;
	element *data;
}Stack;

void init_stack(Stack* s);
int is_empty(Stack* s);
int is_full(Stack* s);
void push(Stack* s, element item);
element pop(Stack* s);

#endif