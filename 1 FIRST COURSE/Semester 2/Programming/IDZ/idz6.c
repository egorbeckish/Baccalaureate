char *delete_space(char *s)
{
        OemToCharA(s,s);
        char strnew[CHAR_MAX][CHAR_MAX];
        int k = 0;
        int dl = strlen(s);
        for(int i = 0; i < dl; i++)
                if( s[i] != ' ')
                {
                        int j = 0;
                        for(j; s[i + j] != ' ' && s[i + j] != '\0'; j++)
                                strnew[k][j] = s[i + j];
                        strnew[k][j] = '\0';
                        k++;
                        i += j;
                }

                qsort(strnew, k, CHAR_MAX, (int (*)(const void *,const void *)) strcmp);

                for(int i = 0; i < k; i++)
                        printf("%s ", strnew[i]);
                system("pause");    
}


void task6()
{
    char *str = (char *)calloc(CHAR_MAX, sizeof(char));
    gets(str);

    char *new_str = delete_space(str);
    puts(new_str);
}


int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    task6();
    return 0;
}
