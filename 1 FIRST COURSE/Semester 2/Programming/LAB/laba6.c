                  // Телефонная книга это набор страниц, пронумерованных буквами русского алфавита. Всего страниц 30 (буквы Ё, Ь, Ъ исключены). 
                  //              На странице содержатся записи вида {Фамилия, Телефон}. Все фамилии на странице начинаются с
                  //                   её буквенного номера. Количество записей на странице не ограничено.


                                              // Вариант 1.
                                              //   - Каждой фамилии соответствует ровно один телефон.
                                              //   - Каждому телефону соответствует ровно одна фамилия.
                                              // Вариант 2.
                                              //   - Каждой фамилии соответствует один или более телефонов.
                                              //   - Каждому телефону соответствует ровно одна фамилия.
                                              // Вариант 3.
                                              //   - Каждой фамилии соответствует один или более телефонов.
                                              //   - Каждому телефону соответствует одна или более фамилий.




#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
 
enum OPTION // Опции функции в адресной книге
{
    EXIT,
    ADD,
    DEL,
    FIND,
    MODIFY,
    SHOW,
    SORT,
    EMPTY
};
 
enum MODIFY // Возможность изменить контактную информацию
{
    EXIT1,
    NAME,
    AGE,
    SEX
};
 
#define MAX_NAME 20
#define MAX_SEX 5
#define  MAX 1000
 
 typedef struct PeoInfo // Определение типа структуры, в которой хранится контактная информация
{
    char name[MAX_NAME];
    char subname[MAX_NAME];
    char phone[MAX_NAME];
}PeoInfo;
 
typedef struct Contact
{
     PeoInfo data [MAX]; // Определяем массив типа PeoInfo для хранения контактной информации
     int count; // Указывает количество контактов
}Contact, *pContact;
 
void InitContact (pContact pc); // инициализация
void AddContact (pContact pc); // Добавляем контактную информацию
void DelContact (pContact pc); // Удаляем контактную информацию
int Find (pContact pc); // Находим чью-то информацию и возвращаем ее индекс
void FindContact (pContact pc); // Находим контактную информацию
void ShowContact (pContact pc); // Отображаем контактную информацию
void ModifyContact (pContact pc); // Изменить контактную информацию
void EmptyContact (pContact pc); // Пустая контактная информация
void SortContact (pContact pc); // Сортировка контактной информации
 

 
void InitContact (pContact pc) // инициализация
{
    pc->count = 0;
    memset(pc->data, 0, sizeof(pc->data));
}
 
void menu1 () // Модифицируем меню функций контактной информации адресной книги
{
 
    printf("**************************\n");
    printf("**** 1.name   2.subname   ****\n");
    printf("**** 3.phone    0.exit1 ****\n");
    printf("**************************\n");
}
 
 void AddContact (pContact pc) // Добавляем информацию
{
    if (pc->count == MAX)
    {
         printf ("«Извините, адресная книга заполнена!»");
        return;
    }
     printf ("Пожалуйста, введите имя:>");
    scanf("%s",pc->data[pc->count].name);
     printf ("Пожалуйста, введите возраст:>");
    scanf("%s", pc->data[pc->count].subname);
     printf ("Пожалуйста, введите пол:>");
    scanf("%s", pc->data[pc->count].phone);
    pc->count++;
}
 
 int Find (pContact pc) // Находим информацию указанного контакта
{
    int i = 0;
    char name[MAX_NAME];
     printf ("Пожалуйста, введите имя контакта, которого вы ищете:>");
    scanf("%s",name);
    for (i = 0; i < pc->count;i++)
    {
        if (strcmp(name, pc->data[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}
 
 void DelContact (pContact pc) // Удалить контакт
{
    int i = 0;
    if (pc->count == 0)
    {
         printf ("К сожалению, адресная книга пуста \n");
        return;
    }
    else
    {
        int ret = Find(pc);
        if (ret == -1)
        {
             printf ("К сожалению, такого контакта нет \n");
            return;
        }
        else
        {
            for (i = ret; i < pc->count - 1; i++)
            {
                pc->data[i] = pc->data[i + 1];
            }
            pc->count--;
        }
         printf ("Поздравляем, контакт успешно удален \n");
    }
}
 
 void FindContact (pContact pc) // Находим адресную книгу
{
    int ret = Find(pc);
    if (ret != -1)
    {
         printf ("name:% s \n", pc-> data [ret].name);
         printf ("subname:% s \n", pc-> data [ret].subname);
         printf ("phone:% s \n", pc-> data [ret].phone);
    }
    else
    {
         printf ("Извините, контакт, который вы ищете, не существует \n");
    }
}
 
 void ModifyContact (pContact pc) // Изменить контактную информацию
{
    int ret = Find(pc);
    if (ret == -1)
    {
         printf ("Извините, нет информации о введенном вами имени \n");
        return;
    }
    else
    {
        int input = 0;
        menu1();
         printf ("Пожалуйста, выберите информацию, которую нужно изменить>:");
        scanf("%d", &input);
        switch (input)
        {
        case NAME:
             printf ("Пожалуйста, введите измененное имя>:");
            scanf("%s", pc->data[ret].name);
            break;
        case AGE:
             printf ("Пожалуйста, введите измененный возраст>:");
            scanf("%s", &(pc->data[ret].subname));
            break;
        case SEX:
             printf ("Пожалуйста, введите измененный пол>:");
            scanf("%s", pc->data[ret].phone);
            break;
        case EXIT1:
            break;
        default:
             printf ("Неправильный выбор, выберите повторно>:");
            break;
        }
         printf ("Поздравляем, вы успешно изменили контактную информацию \n");
    }
}
 void ShowContact (pContact pc) // Отображение контактной информации адресной книги
{
    int  i = 0;
    if (pc->count == 0)
    {
         printf ("Адресная книга пуста \n");
        return;
    }
    for (i = 0; i < pc->count; i++)
    {
        printf("%s %s %s\n", pc->data[i].name, pc->data[i].subname, pc->data[i].phone);
    }
    printf("--------------------------------------------------------------------\n");
}
 
 void EmptyContact (pContact pc) // Пустая контактная информация
{
    pc->count = 0;
     printf ("Поздравляем, контакт успешно очищен \n");
}
 
 void SortContact (pContact pc) // Сортировать все контакты по имени (пузырьковая сортировка)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < pc->count - 1; i++)
        for (j = 0; j < pc->count - 1 - i; j++)
        {
            if (strcmp(pc->data[j].name, pc->data[j + 1].name)>0)
            {
                PeoInfo tmp;
                tmp = pc->data[j];
                pc->data[j] = pc->data[j + 1];
                pc->data[j + 1] = tmp;
            }
        }
     printf ("Сортировано успешно, проверьте \n");
}
 

 
void menu () // Все меню функций адресной книги
{
    printf("*************************\n");
    printf("*** 1.Add    2.Del    ***\n");
    printf("*** 3.Find   4.modify ***\n");
    printf("*** 5.Show   6.Sort   ***\n"); 
    printf("*** 7.Empty  0.Exit   ***\n");
}
 
int main()
{
    int input = 0;
    Contact my_con;
    InitContact(&my_con);
    do
    {
        menu();
         printf ("Выберите функцию операции>:");
        scanf("%d", &input);
        switch (input)
        {
        case ADD:
            AddContact(&my_con);
            break;
        case DEL:
            DelContact(&my_con);
            break;
        case FIND:
            FindContact(&my_con);
            break;
        case MODIFY:
            ModifyContact(&my_con);
            break;
        case SHOW:
            ShowContact(&my_con);
            break;
        case SORT:
            SortContact(&my_con);
            break;
        case EMPTY:
            EmptyContact(&my_con);
            break;
        case EXIT:
            break;
        default:
             printf ("Выбрать неправильно, выберите еще раз \n");
            break;
        }
    } while (input);
    system("pause");
    return 0;
}











-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
  #include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
#define OK 1
#define ERROR -1
#define MAXSIZE 15
#define MAX 1000
 
typedef struct Contacts
{
	char name [MAXSIZE]; // Имя
	char subname [MAXSIZE]; // Фамилия
	char phone [MAXSIZE]; // Номер телефона	
	struct Contacts *next;
} Contacts ,*People;

typedef struct contacts
{
    Contacts peoples[1000];
    int size;
} contacts;

 
//Основная функция
int creat_contacts(People head); // Добавляем контакты
int delete_contacts(People head); // Удаляем контакты
int find_contacts(People head); // Находим контакты
int change_contacts(People head); // Изменить контакты
int show_contacts (People head); // Показать контакты
int empty_contacts(People head); // Пустые контакты
// void sort_contacts(People head);
 
 

 
int creat_contacts(People head) // Добавить контакты (за раз можно добавить только один)
{
    People people;
    people = (People)malloc(sizeof(Contacts));
    fflush(stdin);

    char choose = 0;
    printf("Whether add to contacts? (Y / N): ");
    choose = getchar();

    if (choose == 'y' || choose == 'Y')
    {
        printf("Please enter the name of contact: ");
        scanf("%s", people->name);
        printf("Please enter the subname of contact: ");
        scanf("%s", people->subname);
        printf("Please enter your contact number: ");
        scanf("%s", people->phone);


        people->next = head->next;
        head->next = people;


        printf("\nThe added contact information:\n");
        printf("The name of contact: %s\n", head->next->name);
        printf("The subname of contact: %s\n", head->next->subname);
        printf("Your contact number: %s\n", head->next->phone);
    }  
    return 0;
}
 
int delete_contacts(People head) // Удаляем контакты
{
    int variant;
    char name[MAXSIZE];
    char subname[MAXSIZE];
    char phone[MAXSIZE];
    People people1, people2;

    people1 = head;
    if (head->next == NULL)
    {
        printf("Linked list is empty!\n");
        return 0;
    }

    else
    {
        printf("Please choose the right way:\n");
        printf("1) Delete by name\n");
        printf("2) Delete by subname\n");
        printf("3) Delete by phone\n");
        printf("Please choice 1, 2 or 3: ");
        scanf("%i", &variant);
    }


    switch(variant)
    {
        case 1:
        printf("Please enter the name you want to find: ");
        fflush(stdin);
        gets(name);

        while (people1->next != NULL)
        {
            if (strcmp(people1->next->name, name) == 0)
            {
                printf("The user exists\n");
                printf("Name: %s\tSubname: %s\tPhone: %s\n", people1->next->name, people1->next->subname, people1->next->phone);
                people2 = people1->next;
                people1->next = people2->next;
                free(people2);
            }

            else {people1 = people1->next;}
        }
        return OK;
        break;

        case 2:
        printf("Please enter the subname you want to find: ");
        fflush(stdin);
        gets(subname);

        while (people1->next != NULL)
        {
            if (strcmp(people1->next->subname, subname) == 0)
            {
                printf("The user exists\n");
                printf("Name: %s\tSubname: %s\tPhone: %s\t", people1->next->name, people1->next->subname, people1->next->phone);
                people2 = people1->next;
                people1->next = people2->next;
                free(people2);              
            }

            else {people1 = people1->next;}
        }
        return OK;
        break;

        case 3:
        printf("Please enter the subname you want to find: ");
        fflush(stdin);
        gets(phone);

        while (people1->next != NULL)
        {
            if (strcmp(people1->next->phone, phone) == 0)
            {
                printf("The user exists\n");
                printf("Name: %s\tSubname: %s\tPhone: %s\t", people1->next->name, people1->next->subname, people1->next->phone);
                people2 = people1->next;
                people1->next = people2->next;
                free(people2);         
            }

            else {people1 = people1->next;}
        }
        return OK;
        break;
    }

    return 0;
}
 
int find_contacts(People head) // Находим контакты
{
    People people;
    people = head;
    int variant;
    char name[MAXSIZE];
    char subname[MAXSIZE];
    char phone[MAXSIZE];

    if (head->next == NULL) {printf("Linked list empty!\n");}

    else
    {
        printf("Please choose the right way:\n");
        printf("1) Find by name\n");
        printf("2) Find by subname\n");
        printf("3) Find by phone\n");
        printf("Please choice 1, 2 or 3: ");
        scanf("%i", &variant);
    }


    switch(variant)
    {
        case 1:
        printf("Please enter the name you want to find: ");
        fflush(stdin);
        gets(name);

        while (people->next != NULL)
        {
            people = people->next;
            if (strcmp(people->name, name) == 0)
            {
                printf("The user exists\n");
                printf("Name: %s\tSubname: %s\tPhone: %s\n", people->name, people->subname, people->phone);
            }
        }
        return OK;
        break;


        case 2:
        printf("Please enter the name you want to find: ");
        fflush(stdin);
        gets(subname);

        while (people->next != NULL)
        {
            people = people->next;
            if (strcmp(people->subname, subname) == 0)
            {
                printf("The user exists\n");
                printf("Name: %s\tSubname: %s\tPhone: %s\n", people->name, people->subname, people->phone);
            }
        }
        return OK;
        break;


        case 3:
        printf("Please enter the name you want to find: ");
        fflush(stdin);
        gets(phone);

        while (people->next != NULL)
        {
            people = people->next;
            if (strcmp(people->phone, phone) == 0)
            {
                printf("The user exists\n");
                printf("Name: %s\tSubname: %s\tPhone: %s\n", people->name, people->subname, people->phone);
            }
        }
        return OK;
        break;
    }

    return 0;
}
 
int change_contacts(People head) // Изменить контакты
{
    People people;
    people = head;
    int variant;
    char name[MAXSIZE];
    char subname[MAXSIZE];
    char phone[MAXSIZE];

    if (head->next == NULL)
    {
        printf("Linked list empty!\n");
        return 0;
    }

    printf("Please choose the right way:\n");
    printf("1) Find by name\n");
    printf("2) Find by subname\n");
    printf("3) Find by phone\n");
    printf("Please choice 1, 2 or 3: ");
    scanf("%i", &variant);


    switch(variant)
    {
        case 1:
        printf("Please enter a name to change: ");
        fflush(stdin);
        gets(name);

        while (people->next != NULL)
        {
            people = people->next;
            if (strcmp(people->name, name) == 0)
            {
                printf("The user exists\n");
                printf("Name: %s\nSubname: %s\nPhone: %s\n", people->name, people->subname, people->phone);
                printf("Please enter the information for change:\n");
                printf("Name: ");
                scanf("%s", name);
                printf("Subname: ");
                scanf("%s", subname);
                printf("Phone: ");
                scanf("%s", phone);
                strcpy(people->name, name);
                strcpy(people->subname, subname);
                strcpy(people->phone, phone);
                printf("Changed information:\n");
                printf("Name: %s\tSubname: %s\tPhone: %s\n", people->name, people->subname, people->phone);                
            }
        }
        return OK;
        break;
    }

    return 0;
}
 
 int show_contacts (People head) // Показать контакты
{
    People people;
    if (head->next == NULL) {printf("Linked list is empty!");}
    else
    {
        people = head;
        printf("That is all contact message:\n");
        while (people->next != NULL)
        {
            people = people->next;
            printf("Name: %s\tSubname: %s\tPhone: %s\n", people->name, people->subname, people->phone);
        }
    }

    return 0;
}
 
 int empty_contacts (People head) // Пустые контакты
{
    People people1, people2;
    people1 = head;
    people2 = head;

    while (head->next != NULL)
    {
        people1 = head->next;
        people2 = people1->next;
        head->next = people1->next;
        free(people1);
    }

    if (head->next == NULL) {printf("All contacts were delete!\n");}
    return 0;
}
 

// void sort_contacts(People head)
// {
//     People tmp;
//     int n = head->next;

//     for (int i = 0; i < n - 1; i ++)
//     {
//         for (int j = 0; j < n - i - 1; j ++)
//         {
//             if (strcmp(head->))
//         }
//     }
// }




int menu(People head)
{
    
    char str1[]= "                         ";
    char str2[]= "***********";
    int variant = 0;
    
    
    printf("\n");
    printf("%s", str1);
    printf("%sPhone Book%s\n", str2, str2);
    printf("%sSelect an action\n", str1);
    printf("%s1) Add contact\n", str1);
    printf("%s2) Delete contact\n", str1);
    printf("%s3) Find contact\n", str1);
    printf("%s4) Change contact\n", str1);
    printf("%s5) Show contact\n", str1);
    printf("%s6) Clear contacts\n", str1);
    printf("%s7) Exit\n", str1);

    scanf("%d", &variant);
    switch(variant)
    {
        case 1: creat_contacts(head); break;
        case 2: delete_contacts(head); break;
        case 3: find_contacts(head); break;
        case 4: change_contacts(head); break;
        case 5: show_contacts(head); break;
        case 6: empty_contacts(head); break;
        case 7: sort_contacts(head); break;
        case 8: return 0; break;
    }


    system("pause");
    system("cls");
    return 1;
}


int main()
{
    People head; // Определяем головной узел
    head = (People)malloc(sizeof(Contacts));
    head->next=NULL;
    while(menu(head));
    return 0;
}
