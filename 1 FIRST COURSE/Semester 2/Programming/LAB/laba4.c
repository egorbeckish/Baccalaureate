                                      // 1. Определить структурный тип данных для хранения информации о городах и
                                      //         странах, в которых они находятся. Создать массив экземпляров этого типа.
                                      //       Написать функцию, которая печатает названия городов, находящихся в указанной стране.


                                      // 2. Определить структурный тип данных для хранения информации о товарах:
                                      //           наименование, цена в рублях и копейках. Написать функцию, возвращающую 
                                      //               название более дорогого из двух указанных товаров.


                                      // 3. Определить структурный тип данных «Телефонная книга»: (фамилия, номер, телефона).
                                      //         А) Написать функцию, которая по заданной фамилии возвращает номер
                                      //             телефона. Если фамилии нет, возвращает NULL.
                                      //         Б) Написать функцию, которая по заданному номеру телефона возвращает
                                      //             фамилию владельца. Если номера нет, возвращает NULL.




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
	char *name_city;
	char *country;
} City;


void find_country(City *list, int n)
{
	char *name_country = (char *)calloc(CHAR_MAX, sizeof(char));
	gets(name_country);

	for (int i = 0; i < n; i ++)
	{
		if (strcmp(list[i].country, name_country) == 0)
		{
			puts(list[i].name_city);
		}
	}
}


int main()
{
	srand(time(0));
	// int counter = rand() % 10;
	int counter = 10;
	City list[counter];

	for (int i = 0; i < counter; i ++)
	{
		switch(i)
		{
			case 0:
            	list[i].name_city = "Washington";
            	list[i].country = "USA";
            	break;
        	case 1:
            	list[i].name_city = "Moscow";
            	list[i].country = "Russia";
            	break;
        	case 2:
            	list[i].name_city = "Tomsk";
            	list[i].country = "Russia";
            	break;
        	case 3:
            	list[i].name_city = "Berlin";
            	list[i].country = "Germany";
            	break;
        	case 4:
            	list[i].name_city = "London";
            	list[i].country = "Britain";
            	break;
        	case 5:
            	list[i].name_city = "Bristol";
            	list[i].country = "Britain";
            	break;
        	case 6:
            	list[i].name_city = "Cologne";
            	list[i].country = "Germany";
            	break;
        	case 7:
            	list[i].name_city = "New-York";
            	list[i].country = "USA";
            	break;
        	case 8:
            	list[i].name_city = "Sydney";
            	list[i].country = "Australia";
            	break;
        	case 9:
            	list[i].name_city = "Canberra";
            	list[i].country = "Australia";
            	break;
		}
	}

	find_country(list, counter);
	return 0;
}




-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
    char *name_product;
    int cost_ruble;
    int cost_kopeck;
} Product;


void high_price(Product *list, int n)
{
    char *first_product = (char *)calloc(CHAR_MAX, sizeof(char));
    char *second_product = (char *)calloc(CHAR_MAX, sizeof(char));

    gets(first_product);
    gets(second_product);

    int first_price_ruble,
        first_price_kopeck,
        second_price_ruble,
        second_price_kopeck;

    int found_first,
        found_second;

    for (int i = 0; i < n; i ++)
    {
        if (strcmp(first_product, list[i].name_product) == 0)
        {
            first_price_ruble = list[i].cost_ruble;
            first_price_kopeck = list[i].cost_kopeck;
            found_first = 1;
        }

        if (strcmp(second_product, list[i].name_product) == 0)
        {
            second_price_ruble = list[i].cost_ruble;
            second_price_kopeck = list[i].cost_kopeck;
            found_second = 1;
        }
    }


    if (found_first == 0 || found_second == 0)
    {
        printf("\nBad. Have't products");
        system("pause");
    }

    if (first_price_ruble > second_price_ruble || 
        (first_price_ruble == second_price_ruble && first_price_kopeck > second_price_kopeck))
    {
        printf("first product > second product");
    }

    else
    {
        printf("first product < second product");
    }


    printf("\n\n%i\t%i\n", first_price_ruble, first_price_kopeck);
    printf("%i\t%i", second_price_ruble, second_price_kopeck);
}




int main()
{

    srand(time(NULL));
    
    // int counter = rand() % 10;
    int counter = 10;
    Product list[counter];

    for(int i = 0; i < counter; i ++)
    {
        list[i].cost_ruble = rand() % 200 + 50;
        list[i].cost_kopeck = rand() % 100;
    }

    {   list[0].name_product = "coffee";
        list[1].name_product = "tea";
        list[2].name_product = "sugar";
        list[3].name_product = "oil";
        list[4].name_product = "milk";
        list[5].name_product = "chiken";
        list[6].name_product = "bread";
        list[7].name_product = "salt";
        list[8].name_product = "apple";
        list[9].name_product = "water";  }
    
    printf("\nAvailable products:\n\n");
    for(int i = 0; i < counter; i ++)
    {
        printf("%s\n", list[i].name_product);
    }
    printf("\n");

    high_price(list, counter);
    return 0;
}




-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
	char *name;
	char *number;
	
} Phone_Book;


char *find_name(Phone_Book *list, int n)
{
	char *name = (char *)calloc(CHAR_MAX, sizeof(char));
	gets(name);

	for (int i = 0; i < n; i ++)
	{
		if (strcmp(name, list[i].name) == 0)
		{
			puts(list[i].number);
			return list[i].number;
		}
	}

	printf("Not found\n");
	return NULL;
}




char *find_number(Phone_Book *list, int n)
{
	char *number = (char *)calloc(CHAR_MAX, sizeof(char));
	gets(number);

	for (int i = 0; i < n; i ++)
	{
		if (strcmp(number, list[i].number) == 0)
		{
			puts(list[i].name);
			return list[i].name;
		}
	}

	printf("Not found\n");
	return NULL;
}



int main(int argc, char const *argv[])
{
	srand(time(NULL));
	// int counter = rand() % 10;
	int counter = 10;
	Phone_Book list[counter];

	list[0].name = "Alex";
    list[0].number = "89134352233";
    list[1].name = "Oleg";
    list[1].number = "89527085480";
    list[2].name = "Andrey";
    list[2].number = "89069213344";
    list[3].name = "Egor";
    list[3].number = "89230090157";
    list[4].name = "Dima";
    list[4].number = "89327771222";
    list[5].name = "Leonid";
    list[5].number = "89404058949";
    list[6].name = "Gleb";
    list[6].number = "89231115598";
    list[7].name = "Max";
    list[7].number = "89243314598";
    list[8].name = "Petr";
    list[8].number = "89231464245";
    list[9].name = "Pasha";
    list[9].number = "89231432325";

    find_name(list, counter);
    find_number(list, counter);

	return 0;
}
  
  
  
  
  
  
  
  
  
  
