#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <Windows.h>
#include <limits.h>
#include <conio.h>

void task9()
{
	FILE *f = fopen("f.txt", "r");
    FILE *g = fopen("g.txt", "w");

    char symbol;
    char *string = (char *)calloc(CHAR_MAX, sizeof(char));
    
    int k = 0;
    if (f == NULL) printf("File is close\n");
    else
    {
    	while (!feof(f))
    	{
    		symbol = fgetc(f);
    		string[k] = symbol;
    		k ++;
    	}
        // if (gets(string) != NULL)
        // {
        //     fputs(string, f);
        //     fputs("\n", f);
        // }
    }
    string[strlen(string) - 1] = '\0';
    // printf("%d\n", strlen(string));
    // puts(string);

    char *new_str = (char *)calloc(CHAR_MAX, sizeof(char));
    int j = 0;
    for (int i = strlen(string) - 1; i > -1; i --)
    {
        // printf("j = %d\n", j);
        // printf("i = %d\n", i);
        // printf("str[i] = %c\n", string[i]);
        if (i % 2 == 1)
        {
            // printf("str[i] = %c\n", string[i]);
            new_str[j] = string[i];
            // printf("new = %c\n", new_str[j]);
            j ++;
        }
    }

    // printf("len(s) = %d\n", strlen(s));
    // puts(new_str);
    j = 0;
    int len = strlen(new_str);
    for (int i = strlen(string) - 1; i > -1; i --)
    {
        // printf("j = %d\tj + strlen(s) = %d\n", j, (j + strlen(s)));
        if (i % 2 == 0)
        {
            // printf("str[i] = %c\n", str[i]);
            new_str[j + len] = string[i];
            // printf("s[j + strlen(s)] = %c\n", s[j + strlen(s)]);
            j ++;
        }
    }
    // printf("\n\n%d", strlen(s));
    // printf("\n");
    // puts(new_str);

    fputs(new_str, g);
}



int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	task8();
	
	return 0;
}
