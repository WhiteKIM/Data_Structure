/*
* Stack Header
*/

#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

typedef struct Stack
{
	char data;
	int top;
	int capacity;
}stack;

void init_stack(stack* s);
int is_empty(stack* s);
int is_full(stack* s);
void push(stack* s, char item);
char pop(stack* s);
char peek(stack* s, int num);

#endif
