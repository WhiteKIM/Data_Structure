/*
* @ 편집거리문제
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

char* result[MAX_SIZE][MAX_SIZE] = {"", };

char* concat(const char* s1, const char* s2) {
	char* res = malloc(strlen(s1) + strlen(s2) + 1);
	strcpy(res, s1);
	strcat(res, ", ");
	strcat(res, s2);
	return res;
}

int get_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return a;
	else if (b <= a && b <= c)
		return b;
	else
		return c;
}

int get_edit(int a, int b, int c)
{
	if (a <= b && a <= c)
		return 1;
	else if (b <= a && b <= c)
		return 2;
	else
		return 3;
}

int editDistance(int ** arr, int width, int height, char S[], char T[])
{
	int a = 0;
	for (int i = 0; i < width; i++)
		arr[0][i] =i;

	for (int i = 0; i < height; i++)
		arr[i][0] = i;

	for (int i = 1; i < height; i++)
	{
		for (int j = 1; j < width; j++)
		{
			a = 1;
			if (S[i-1]==T[j-1])//문자열이 같으면 편집X, 다르면 편집
				a = 0;
			arr[i][j] = get_min(arr[i][j-1] + 1, arr[i-1][j] + 1, arr[i-1][j-1] + a);

			if (a == 1)//편집된 결과에 대한 문자열을 보여줌
			{
				if (get_min(arr[i][j - 1] + 1, arr[i - 1][j] + 1, arr[i - 1][j - 1] + a) == arr[i][j - 1] + 1)
				{
					char x[100];
					char y[100];
					sprintf(x, "%d", i);
					sprintf(y, "%d", j);
					char* message1;
					message1 = concat(x, y);
					char* message2;
					message2 = concat(message1, " insert ");
					char* message3;
					message3 = concat(result[i][j - 1], message2);
					if (result[i][j] == NULL)
						result[i][j] = message3;
					else
						strcat(result[i][j], message3);
				}
				else if (get_min(arr[i][j - 1] + 1, arr[i - 1][j] + 1, arr[i - 1][j - 1] + a) == arr[i - 1][j] + 1)
				{
					char x[100];
					char y[100];
					sprintf(x, "%d", i);
					sprintf(y, "%d", j);
					char* message1;
					message1 = concat(x, y);
					char* message2;
					message2 = concat(message1, " delete ");
					char* message3;
					message3 = concat(result[i - 1][j], message2);
					if (result[i][j] == NULL)
						result[i][j] = message3;
					else
						strcat(result[i][j], message3);
				}
				else
				{
					char x[100];
					char y[100];
					sprintf(x, "%d", i);
					sprintf(y, "%d", j);
					char* message1;
					message1 = concat(x, y);
					char* message2;
					message2 = concat(message1, " replace ");
					char* message3;
					message3 = concat(result[i - 1][j - 1], message2);
					if (result[i][j] == NULL)
						result[i][j] = message3;
					else
						strcat(result[i][j], message3);
				}
			}
			else
			{
				if (get_min(arr[i][j - 1] + 1, arr[i - 1][j] + 1, arr[i - 1][j - 1] + a) == arr[i][j - 1] + 1)
				{
					char x[100];
					char y[100];
					sprintf(x, "%d", i);
					sprintf(y, "%d", j);
					char *message1;
					message1 = concat(x, y);
					char *message2;
					message2 =concat(message1, " insert ");
					char* message3;
					message3 = concat(result[i][j - 1], message2);
					if (result[i][j] == NULL)
						result[i][j] = message3;
					else
						strcat(result[i][j], message3);
				}
				else if (get_min(arr[i][j - 1] + 1, arr[i - 1][j] + 1, arr[i - 1][j - 1] + a) == arr[i - 1][j] + 1)
				{
					char x[100];
					char y[100];
					sprintf(x, "%d", i);
					sprintf(y, "%d", j);
					char * message1;
					message1= concat(x, y);
					char *message2;
					message2 =concat(message1, " delete ");
					char* message3;
					message3 = concat(result[i - 1][j], message2);
					if (result[i][j] == NULL)
						result[i][j] = message3;
					else
						strcat(result[i][j], message3);
				}
				else
				{
					char x[100];
					char y[100];
					sprintf(x, "%d", i);
					sprintf(y, "%d", j);
					char *message1;
					message1 = concat(x, y);
					char *message2;
					message2 = concat(message1, " keep ");
					char* message3;
					message3 = concat(result[i - 1][j - 1], message2);
					if (result[i][j] == NULL)
						result[i][j] = message3;
					else
						strcat(result[i][j], message3);
				}
			}
		}
	}

	printf("최종 수정 결과 : %s \n", result[height - 1][width - 1]);
	return arr[height-1][width-1];
}

int main(void)
{
	char S[20];
	char T[20];
	printf("S 입력 : ");
	scanf_s("%s", S, sizeof(char) * 20);
	printf("T 입력 : ");
	scanf_s("%s", T, sizeof(char) * 20);
	int S_length = 0;
	S_length = strlen(S);
	int T_length = 0;
	T_length = strlen(T);

	int ** arr = NULL; 
	arr= (int**)malloc(sizeof(int*) * (S_length + 1));
	for (int i = 0; i < S_length + 1; i++)
	{
		arr[i] = (int*)malloc(sizeof(int) * (T_length + 1));
		if (NULL == arr[i])
			exit(-1);
	}
	int result = editDistance(arr, T_length + 1, S_length + 1, S, T);

	for (int i = 0; i < S_length+1; i++)
	{
		for (int j = 0; j < T_length+1; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("결과는 %d \n", result);

	for (int i = 0; i < (S_length + 1); i++)
	{
		free(arr[i]);
	}
	free(arr);

	return 0;
}