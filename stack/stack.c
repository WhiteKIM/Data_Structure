/*
* stack source 
*/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void init_stack(stack* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (char*)malloc(s->capacity * sizeof(char));
}

int is_empty(stack* s)
{
	return (s->top == -1);
}

int is_full(stack* s)
{
	return (s->top == (s->capacity - 1));
}

void push(stack* s, char item)
{
	if (is_full)
	{
		s->capacity *= 2;
		s->data = (char*)realloc(s->data,s->capacity * sizeof(char));
	}
	s->top++;
	s->data = item;
}

char pop(stack* s)
{
	if (is_empty)
	{
		fprintf(stderr, "스택이 비었습니다");
		exit(1);
	}
	else
	{
		return s->data;
		s->top--;
	}
}

char peek(stack* s, int num)
{
	if (is_empty)
	{
		fprintf(stderr, "스택이 비었습니다");
		exit(1);
	}
	s->top == num;
	return s->data[num];
}

