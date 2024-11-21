char *delete_sympols_and_replace(char *str)
{
    int lenght = strlen(str),
        counter = 0,
        t = 0;

    for (int i = 0; i < strlen(str); i ++)
    {
        str[i] = str[i + t];
        if (!(str[i] >= 'A' && str[i] <= 'Z' ||
                str[i] >= 'a' && str[i] <= 'z' ||
                str[i] >= '0' && str[i] <= '9' ))
        {
            t += 1;
            str[i] = str[i + t];
            i --;
        }

        if (str[i] >= '0' && str[i] <= '9')
        {
            counter ++;
        }
    }

    lenght = strlen(str);
    char *new_str = (char *)calloc((lenght + counter * 2), sizeof(char));

    int j = 0;
    for (int i = 0; i < lenght; i ++)
    {
        // printf("%i\t%i\n", i, j);
        if (str[i] >= '0' && str[i] <= '9')
        {
            new_str[j] = '*';
            new_str[j + 1] = '*';
            j += 2;
        }

        else
        {
            new_str[j] = str[i];
            j += 1;
        }
    }

    new_str[lenght + counter] = '\0';

    return new_str;
}

void task5()
{
    char *str = (char *)calloc(CHAR_MAX, sizeof(char));
    gets(str);

    char *new_str = delete_sympols_and_replace(str);
    puts(new_str);
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    task5();
    return 0;
}
