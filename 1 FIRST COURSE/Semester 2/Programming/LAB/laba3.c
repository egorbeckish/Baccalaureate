#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <string.h>



                                                // 3.1. Даны строки S и S0. Удалить из строки S первую подстроку, совпадающую с S0.
                                                // Если совпадающих подстрок нет, то вывести строку S без изменений.


                                                // 3.2. Даны строки S и S0. Удалить из строки S все подстроки, совпадающие с S0. Если
                                                // совпадающих подстрок нет, то вывести строку S без изменений.


                                                // 3.3. Даны строки S, S1 и S2. Заменить в строке S первое вхождение строки S1 на
                                                // строку S2.


                                                // 3.4. Дана строка, содержащая, по крайней мере, один символ пробела. Вывести
                                                // подстроку, расположенную между первым и вторым пробелом исходной
                                                // строки. Если строка содержит только один пробел, то вывести пустую строку.





void delete_first_input(char *s, char	*s0)
{
	char *temp = strstr(s, s0);

	if (temp == NULL) return;

	int i = 0;
	int lenght = strlen(s0);
	while (temp[i + lenght] != '\0')
	{
		temp[i] = temp[i + lenght];
		i ++;
	}

	temp[i] = '\0';

	return;
}

void delete_all_input(char *s, char *s0)
{
	char *temp = strstr(s, s0);

	if (temp == NULL) return;

	while(temp != NULL)
	{
		delete_first_input(s, s0);
		temp = strstr(s, s0);
	}

	return;
}


void change_substring(char *s, char *s1, char *s2)
{
	int lenght_s = strlen(s),
		lenght_s1 = strlen(s1),
		lenght_s2 = strlen(s2);

	int i, j;
	for (int start = 0; start <= lenght_s - lenght_s1; start ++)	// основная строка
	{
		for (i = start, j = 0; j < lenght_s1; i ++, j ++)
		{
			if (s[i] != s1[j]) { break; }
			// нашли одно несовпадение, то выходим
		}

		if (j == lenght_s1)		// дошли до конца подстроки, следовательно нашли
		{
			j = lenght_s2 - lenght_s1;	// корректируем длину двух строк

			if (j > 0)	// если заменяемое слово больше
			{
				lenght_s += j;	// расширяем длину слова
				s = (char *)realloc(s, (lenght_s + 1) * sizeof(char));

				for (i = lenght_s + j; i > start + j; i --)
				{
					s[i] = s[i - j];
					// перезаписываем оставшиеся части строк
				}
			}

			else if (j < 0)		// если заменяемое слово меньше
			{
				for (i = start + lenght_s1 + j; i < lenght_s; i ++)
				{
					s[i] = s[i - j];
					// копируем строку к началу
				}

				lenght_s += j;
				// // расширяем длину слова
			}

			for (i = 0; i < lenght_s2; i ++, start ++)
			{
				s[start] = s2[i];
				// меняем на вторую подстроку
			}
		}

	}

	s[lenght_s + 1] = '\0';
	return;
}




char *substring_between_whitespace(char *s)
{
	int first_whitespace = 0,
		second_whitespace = 0;

	for (int i = 0; i < strlen(s); i ++)
	{
		if (first_whitespace != 0 && s[i] == ' '){ second_whitespace = i; break; }
		if (first_whitespace == 0 && s[i] == ' '){ first_whitespace = i; }
	}

	if (second_whitespace == 0) { char *str = (char *)calloc(1, sizeof(char)); str[0] = '\0'; return str; }
	
	int lenght = second_whitespace - first_whitespace;
	char *str = (char *)calloc(lenght + 1, sizeof(char));

	int j = 0;
	for (int i = first_whitespace + 1; i < second_whitespace; i ++)
	{
		str[j] = s[i];
		j ++;
	}

	str[j + 1] = '\0';
	return str;
}	





int main(int argc, char const *argv[])
{
	int choice;
	printf("Select an action:\n\t"
		"1 - Remove the first substring from the string\n\t"
		"2 - Remove the all substring from the string\n\t"
		"3 - Change the first of a substring to the second\n\t"
		"4 - Print substring between first and second whitespace\n");
	
	scanf("%i", &choice);
	fflush(stdin);



	if (choice == 1)
	{
		char *s = (char *)calloc(CHAR_MAX, sizeof(char));
		char *s0 = (char *)calloc(CHAR_MAX, sizeof(char));

		printf("Input original string: ");
		fflush(stdin);
		gets(s);

		printf("Enter substring: ");
		fflush(stdin);
		gets(s0);

		delete_first_input(s, s0);
		puts(s);

		free(s);
		free(s0);
	}


	if (choice == 2)
	{
		char *s = (char *)calloc(CHAR_MAX, sizeof(char));
		char *s0 = (char *)calloc(CHAR_MAX, sizeof(char));

		printf("Input original string: ");
		fflush(stdin);
		gets(s);

		printf("Enter substring: ");
		fflush(stdin);
		gets(s0);

		delete_all_input(s, s0);
		puts(s);

		free(s);
		free(s0);

	}


	if (choice == 3)
	{
		char *s = (char *)calloc(CHAR_MAX, sizeof(char));
		char *s1 = (char *)calloc(CHAR_MAX, sizeof(char));
		char *s2 = (char *)calloc(CHAR_MAX, sizeof(char));

		printf("Input original string: ");
		fflush(stdin);
		gets(s);

		printf("Input substring which replace: ");
		fflush(stdin);
		gets(s1);

		printf("Input changed substring: ");
		fflush(stdin);
		gets(s2);


		change_substring(s, s1, s2);
		puts(s);

		free(s);
		free(s1);
		free(s2);

	}


	if (choice == 4)
	{
		char *str = (char *)calloc(CHAR_MAX, sizeof(char));

		fflush(stdin);
		gets(str);

		fflush(stdin);
		char *result = substring_between_whitespace(str);
		puts(result);

		free(str);
		free(result);
	}

	system("pause");

	return 0;
}
