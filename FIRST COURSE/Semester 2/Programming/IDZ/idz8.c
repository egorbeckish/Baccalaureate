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



typedef struct
{
	char name[30];
	char shop[30];
	char product_price[10];

} Price;



void task8()
{
    srand(time(NULL));

    int limit = 30;
    Price product[30];
    char *check = (char *)calloc(30, sizeof(char));
    char *memory = (char *)calloc(30, sizeof(char));

    for (int i = 0; i < 2; i ++)
    {
        printf("Enter product %i NAME: ", (i + 1));
        fgets(product[i].name, 30, stdin);
        printf("Enter product %d SHOP: ", (i + 1));
        fgets(product[i].shop, 30, stdin);
        printf("Enter product %d PRICE: ", (i + 1));
        fgets(product[i].product_price, 10, stdin);
        printf("\n");
    }


    // for (int i = 0; i < 2; i ++)
    // {
    //     if (product[i + 1].name > product[i].name)
    //     {
    //         strcpy(memory, product[i].name);
    //         strcpy(product[i].name, product[i + 1].name);
    //         strcpy(product[i + 1].name, memory);
    //     }
    // }

    printf("\nPrice list: \n");
    for (int i = 0; i < 2; i ++)
    {
        printf("%s", product[i].name);
    }


    while(1)
    {
        printf("\nYou can get information about any product by enter it's name:\n");
        fgets(check, 30, stdin);
        for(int i = 0; i < 2; i ++){
            if(strncmp(check, product[i].name, limit) == 0 ){
                printf("Product %d NAME is: %s", i, product[i].name);
                printf("Product %d SHOP is: %s", i, product[i].shop);
                printf("Product %d PRICE is: %s", i, product[i].product_price);
            }
        }
    }
}



int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	task8();
	
	return 0;
}
