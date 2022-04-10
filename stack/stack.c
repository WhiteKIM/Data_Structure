#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_stack(Stack* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(sizeof(element) * s->capacity);
}

int is_empty(Stack* s)
{
	return (s->top == -1);
}

int is_full(Stack* s)
{
	return (s->top == s->capacity-1);
}

void push(Stack* s, element item)
{
	if (is_full(s))
	{
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, sizeof(element) * s->capacity);
	}
	s->data[++(s->top)] = item;
}

element pop(Stack* s)
{
	if (is_empty(s))
	{
		perror("stack is empty");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}
