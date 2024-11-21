#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <locale.h>
#include <string.h>



                                                          // Проектирование «неограниченного» калькулятора


#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

struct digit //объявляем структуру
{
    char *dig;
    int sign;
    int exponent;
    int len;
};

typedef struct digit ldd;

typedef struct Node_tag
{
    char value;
    struct Node_tag *next;
} Node_t;

typedef struct st_tag
{
    ldd value;
    struct st_tag *next;
} st_t;

ldd add(ldd, ldd );
void delete_ldd(ldd );
size_t getSize( Node_t *);
size_t getSize2( st_t *);
ldd ldd_minus(ldd,ldd );
int lddcmp(ldd,ldd );
ldd make_ldd(char *);
int max(int, int );
int min(int, int );
ldd multiplication(ldd, ldd);
char* opz(char *);
ldd opzTOldd(char *);
char pop(Node_t **);
ldd pop2(st_t **);
ldd post_minus(ldd,ldd );
ldd preminus(ldd,ldd );
ldd presum(ldd, ldd );
ldd preUmn(ldd,ldd);
void print_ldd(ldd );
int PRIOR(char );
void push(Node_t **, char );
void push2(st_t **, ldd );
char top(Node_t* );
ldd top2(st_t* );
void sdv10(ldd*, ldd*);


int main()
{
    setlocale(LC_CTYPE, "RUSSIAN");
    srand(time(NULL));
    int V=0;

    printf("What do you want to do?\n");
    printf("add two numbers - 1\n");
    printf("input and output - 2\n");
    printf("Compare two numbers - 3\n");
    printf("subtraction - 4\n");
    printf("multiplication - 5\n");
    printf("expression - 6\n");
    printf("equation of exponents - 7\n");
    printf("output- 8\n");

    scanf("%d",&V);
    fflush(stdin);// чистим ввод и экран
    system("cls");

    if(V==1) // если добавляем
    {


        printf("enter the first number: \n");
        char *st1=(char*)calloc(128,sizeof(char));
        gets(st1);
        ldd A= make_ldd(st1);
        printf("enter the second number: \n");
        char *st2=(char*)calloc(128,sizeof(char));
        gets(st2);
        ldd B= make_ldd(st2);

        ldd sum=presum(A,B);
        print_ldd(sum);

        delete_ldd(A);
        delete_ldd(B);
        delete_ldd(sum);

        free(st1);
        free(st2);

        system("pause");
        fflush(stdin);
    }
    if (V==2)
    {
        printf("enter a number: \n");
        char *st1=(char *)calloc(128,sizeof(char));//для номера группы
        gets(st1);// читаем номер группы

        ldd A= make_ldd(st1);

        print_ldd(A);

        delete_ldd(A);
        system("pause");
        free(st1);

    }

    if (V==3)
    {

        printf("enter the first number: \n");
        char *st1=(char*)calloc(128,sizeof(char));
        gets(st1);
        ldd A= make_ldd(st1);
        printf("enter the second number: \n");
        char *st2=(char*)calloc(128,sizeof(char));
        gets(st2);
        ldd B= make_ldd(st2);

        printf("%d",lddcmp(A,B));
        delete_ldd(A);
        delete_ldd(B);


        free(st1);
        free(st2);

        system("pause");
        fflush(stdin);
    }
    if(V==4)
    {
        printf("enter the first number: \n");
        char *st1=(char*)calloc(128,sizeof(char));
        gets(st1);
        ldd A= make_ldd(st1);
        printf("enter the second number: \n");
        char *st2=(char*)calloc(128,sizeof(char));
        gets(st2);
        ldd B= make_ldd(st2);

        ldd raz=preminus(A,B);
        print_ldd(raz);

        delete_ldd(A);
        delete_ldd(B);
        delete_ldd(raz);

        free(st1);
        free(st2);

        system("pause");
        fflush(stdin);

    }
    if(V==5)
    {
        printf("enter the first number: \n");
        char *st1=(char*)calloc(128,sizeof(char));
        gets(st1);
        ldd A= make_ldd(st1);
        printf("enter the second number: \n");
        char *st2=(char*)calloc(128,sizeof(char));
        gets(st2);
        ldd B= make_ldd(st2);

        ldd raz=preUmn(A,B);
        print_ldd(raz);

        delete_ldd(A);
        delete_ldd(B);
        delete_ldd(raz);

        free(st1);
        free(st2);

        system("pause");
        fflush(stdin);

    }
    if(V==6)
    {
        printf("enter expression: \n");
        char *st1=(char*)calloc(128,sizeof(char));
        gets(st1);
        char *op= opz(st1);
        puts(op);
        ldd anss=opzTOldd(op);
        printf("ans=\n");
        print_ldd(anss);


        free(st1);
        free(op);
        delete_ldd(anss);
        system("pause");
        fflush(stdin);

    }
    if(V==7) // если добавляем
    {


        printf("enter the first number: \n");
        char *st1=(char*)calloc(128,sizeof(char));
        gets(st1);
        ldd A= make_ldd(st1);
        printf("enter the second number: \n");
        char *st2=(char*)calloc(128,sizeof(char));
        gets(st2);
        ldd B= make_ldd(st2);

        printf("exp= %d\n",A.exponent);
        print_ldd(A);
        printf("exp= %d\n",B.exponent);
        print_ldd(B);
        system("pause");
        sdv10(&A,&B);

        printf("exp= %d\n",A.exponent);
        print_ldd(A);
        printf("exp= %d\n",B.exponent);
        print_ldd(B);

        delete_ldd(A);
        delete_ldd(B);


        free(st1);
        free(st2);

        system("pause");
        fflush(stdin);
    }
    system("cls");

    system("pause");
    return 0;
}

void push(Node_t **head, char value)
{
    Node_t *tmp = malloc(sizeof(Node_t));
    if (tmp == NULL)
    {
        printf("input error\n");
        exit(STACK_OVERFLOW);
    }

    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}
char pop(Node_t **head)
{
    Node_t *out;
    char value;
    if (*head == NULL)
    {
        printf("input error\n");
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

size_t getSize( Node_t *head)
{
    size_t size = 0;
    while (head)
    {
        size++;
        head = head->next;
    }
    return size;
}
char top(Node_t* head)
{
    if (head == NULL)
    {
        printf("input error\n");
        exit(STACK_UNDERFLOW);
    }
    return head->value;
}


int PRIOR(char a)
{
    switch (a)
    {
    case '*':
        return 3;

    case '-':
    case '+':
        return 2;

    case '(':
        return 1;
    }
}

int max(int a, int b)
{

    return a>b?a:b;
}
int min(int a, int b)
{

    return a<b?a:b;
}


ldd add(ldd A, ldd B)
{
    ldd rez;
    rez.len=max(A.len,B.len);
    rez.sign=1;
    rez.dig=(char *)calloc(rez.len+1,sizeof(char));
    int c=0;
    for(int i=0; i<rez.len; i++)
    {

        c= c+A.dig[i]+B.dig[i];
        rez.dig[i]=c%10;
        c/=10;
    }
    if(c>0)
    {
        rez.len++;
        rez.dig[rez.len]=c;
    }

    return rez;
}

ldd make_ldd(char *st)
{

    ldd rez;
    rez.sign=1;
    int start=0;
    rez.len=strlen(st);
    // printf("len=%d\n",rez.len);
    if (st[0]=='_')  //если - то учитываем и переходим к след символу
    {
        start++;
        rez.sign=-1;
        rez.len--;
    }
    if (st[0]=='+') // если + то идем к след символу
    {
        start++;
        rez.len--;
    }
    rez.dig=(char *)calloc(rez.len+1,sizeof(char));
    int j=0;
    int tchk=0;
    for(int i= strlen(st)-1; i>=start; i--)
    {
        if(st[i]==' ')
        {
            rez.len--;
            continue;
        }
        if(st[i]=='.')
        {
            tchk=j;
            continue;
        }
        rez.dig[j]=st[i]-'0';
        j++;
    }
    if(tchk!=0)rez.len--;
    rez.exponent=tchk;
    return rez;
}

void delete_ldd(ldd A)
{
    free(A.dig);
    return;
}

void print_ldd(ldd A)
{

    if(A.sign==1)printf("+");
    else printf("-");

    for(int i=1; i<=A.len; i++)
    {
        printf("%c",(A.dig[A.len-i]+'0'));
        if((i==A.len-A.exponent)&&(A.exponent!=0))
        {
            printf(".");
        }
    }
    printf("\n");
    printf("\n");

    return;
}

int lddcmp(ldd A,ldd B)
{
    if(A.len<B.len)return -1;
    if(A.len>B.len)return 1;
    for(int i=A.len-1; i>=0; i--)
    {
        if(A.dig[i]<B.dig[i])return -1;
        if(A.dig[i]>B.dig[i])return 1;
    }
    return 0;
}

ldd post_minus(ldd A,ldd B)
{
    ldd rez;
    rez.len=A.len;
    rez.sign=1;
    rez.dig=(char *)calloc(rez.len+1,sizeof(char));

    int c=0;
    for(int i=0; i<rez.len; i++)
    {
        c = c+A.dig[i]-B.dig[i]+10;
        rez.dig[i]=c%10;
        if(c < 10) c=-1;
        else c=0;
    }
    while(rez.dig[rez.len-1]==0 && rez.len>1) rez.len--;
    return rez;
}


ldd ldd_minus(ldd A,ldd B)
{
    ldd rez;
    if(lddcmp(A,B)>=0)
    {
        rez=post_minus(A,B);
        //printf(" cmp = %d\n",lddcmp(A,B));
        rez.sign=1;

    }
    else
    {
        rez=post_minus(B,A);
        rez.sign=-1;

    }
    return rez;
}
ldd multiplication(ldd A, ldd B)
{
    ldd rez;
    rez.len=A.len+B.len+2;
    rez.sign=1;
    rez.dig=(char *)calloc(rez.len+1,sizeof(char));
    int c=0;
    int cur=0;
    int i=0;
    while(i<A.len)
    {
        int j=0;
        while(j< B.len || c)
        {
            if(j<B.len)
                cur=rez.dig[i+j]+A.dig[i]*B.dig[j]+c;
            else
                cur= rez.dig[i+j]+c;
            rez.dig[i+j]=cur%10;
            c=cur/10;
            j++;
        }
        i++;
    }
    while((rez.dig[rez.len-1]==0) && (rez.len>1)) rez.len--;
    return rez;
}

char* opz(char *st)
{

    char* out=(char *)calloc(128,sizeof(char));
    Node_t *stack = NULL;


    int   point=0;
    for(int i=0; i<strlen(st); i++)
    {
        if(st[i]==')')
            /* то выталкиваем из стека в выходную стpоку */
        {
            /* все знаки опеpаций до ближайшей */
            while((top(stack))!='(')
            {
                /* откpывающей скобки */
                out[point++]=' ';
                out[point++]=pop(&stack);
                if(stack == NULL)
                {
                    printf("Input error:\n brackets\n");
                    return NULL;
                }
            }
            /* Удаляем из стека саму откpывающую скобку */

            pop(&stack);
            continue;
        }
        if((st[i]>='0')&&(st[i]<='9'))
        {

            /* пеpеписываем её в выходную стpоку */
            out[point]=st[i];
            point++;
            continue;
        }
        if( st[i]==' ' || st[i]=='.' || st[i]=='_')
        {
            out[point++]=st[i];
            continue;
        }
        if(st[i]=='(')
        {
            push(&stack, st[i]);
            out[point++]=' ';
            continue;
        }
        if(st[i]=='+'||st[i]=='-'||st[i]=='*')
        {
            if(stack==NULL)
            {

                out[point++]=' ';
                push(&stack, st[i]);
            }
            else
            {
                if(PRIOR(top(stack))<PRIOR(st[i]))
                {
                    out[point++]=' ';
                    push(&stack,st[i]);
                }

                else
                {
                    while(stack!=NULL && PRIOR(top(stack))>=PRIOR(st[i]))
                    {
                        out[point++]=' ';
                        out[point++]=pop(&stack);
                        out[point++]=' ';
                    }
                    push(&stack,st[i]);
                }
            }
            continue;
        }
        puts("Input error incorrect expression entered\n\0");
        return NULL;
    }

    while(stack!=NULL)
    {
        if(top(stack) == '(' || top(stack) == ')')
        {
            printf("Error entering parenthesis\n");
            return NULL;
        }
        out[point++]=' ';
        out[point++]=pop(&stack);
    }
    out[point]='\0';


    return out;

}



void push2(st_t **head, ldd value)
{
    st_t *tmp = malloc(sizeof(st_t));

    if (tmp == NULL)
    {
        printf("input error\n");
        exit(STACK_OVERFLOW);
    }

    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}
ldd pop2(st_t **head)
{
    st_t *out;
    ldd value;
    if (*head == NULL)
    {
        printf("input error\n");
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

size_t getSize2( st_t *head)
{
    size_t size = 0;
    while (head)
    {
        size++;
        head = head->next;
    }
    return size;
}
ldd top2(st_t* head)
{
    if (head == NULL)
    {
        printf("input error\n");
        exit(STACK_UNDERFLOW);
    }
    return head->value;
}

ldd opzTOldd(char *st)
{

    char *tmp=(char*)calloc(128,sizeof(char));
    int j=0;
    st_t *stack_ldd=NULL;
    for(int i=0; i<strlen(st); i++)
    {
        if((st[i]>='0'&&st[i]<='9')||st[i]=='_'||st[i]=='.')
        {
            tmp[j]=st[i];
            j++;
        }
        if(st[i]==' '||st[i]=='*'||st[i]=='-'||st[i]=='+' )
        {
            if(j!=0)
            {
                tmp[j]='\0';
                ldd t= make_ldd(tmp);
                j=0;
                //printf("addst =\n");
                // print_ldd(t);

                push2(&stack_ldd,t);
            }
        }
        if(st[i]=='+')
        {
            //printf("+\n");
            ldd A=pop2(&stack_ldd);
            ldd B=pop2(&stack_ldd);
            //print_ldd(A);
            //print_ldd(B);
            push2(&stack_ldd,presum(A,B));
            delete_ldd(A);
            delete_ldd(B);
        }

        if(st[i]=='-')
        {
            ldd A=pop2(&stack_ldd);
            //printf("-\n");
            //print_ldd(A);
            ldd B=pop2(&stack_ldd);
            //print_ldd(B);
            // print_ldd(preminus(B,A));
            push2(&stack_ldd,preminus(B,A));
            delete_ldd(A);
            delete_ldd(B);
        }

        if(st[i]=='*')
        {
            ldd A=pop2(&stack_ldd);
            //printf("*\n");
            //print_ldd(A);
            ldd B=pop2(&stack_ldd);
            // print_ldd(B);
            //print_ldd(preUmn(B,A));
            push2(&stack_ldd,preUmn(A,B));
            delete_ldd(A);
            delete_ldd(B);
        }
    }

    return pop2(&stack_ldd);

}

ldd presum(ldd A, ldd B)
{

    ldd rez;
    sdv10(&A,&B);
    //print_ldd(A);
    //print_ldd(B);
    if(A.sign==-1 && B.sign==-1)
    {
        rez=add(A,B);
        rez.sign=-1;
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    if(A.sign==-1 )
    {
        rez=ldd_minus(B,A);
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    if(B.sign==-1 )
    {
        rez=ldd_minus(A,B);
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    if(A.sign==1 && B.sign==1)
    {
        rez=add(A,B);
        rez.sign=1;
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    return rez;
}

ldd preminus(ldd A,ldd B)
{

    ldd rez;
    sdv10(&A,&B);
    if(A.sign==-1 && B.sign==1)
    {
        rez=add(A,B);
        rez.sign=-1;
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    if(A.sign==-1 && B.sign==-1)
    {
        rez=ldd_minus(B,A);
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    if(A.sign==1 && B.sign==-1)
    {
        rez=add(A,B);
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    if(A.sign==1 && B.sign==1)
    {
        rez=ldd_minus(A,B);
        rez.exponent=max(A.exponent,B.exponent);
        return rez;
    }
    return rez;

}

ldd preUmn(ldd A,ldd B)
{

    ldd rez;
    if(A.sign==-1 && B.sign==-1)
    {
        rez=multiplication(A,B);
        rez.exponent=A.exponent+B.exponent;
        return rez;
    }
    if(A.sign==-1 && B.sign==1)
    {
        rez=multiplication(B,A);
        rez.sign=-1;
        rez.exponent=A.exponent+B.exponent;
        return rez;
    }
    if(A.sign==1 && B.sign==-1)
    {
        rez=multiplication(B,A);
        rez.sign=-1;
        rez.exponent=A.exponent+B.exponent;
        return rez;
    }
    if(A.sign==1 && B.sign==1)
    {
        rez=multiplication(B,A);
        rez.exponent=A.exponent+B.exponent;
        return rez;
    }
    rez.exponent=A.exponent+B.exponent;
    return rez;

}

void sdv10(ldd *A,ldd *B)
{
    int e=max(A->exponent, B->exponent) - A->exponent;
    for(int i=0; i<e; i++)
    {
        A->dig=realloc(A->dig,(++A->len)*sizeof(char));
        for(int j=A->len-1; j>=1; j--)
        {
            A->dig[j]=A->dig[j-1];
        }
        A->dig[0]=0;
        A->exponent++;
    }
    //A.exponent=max(A.exponent, B.exponent);
    e=max(A->exponent, B->exponent) - B->exponent;
    for(int i=0; i<e; i++)
    {
        B->dig=realloc(B->dig,(++B->len)*sizeof(char));
        for(int j=B->len-1; j>=1; j--)
        {
            B->dig[j]=B->dig[j-1];
        }
        B->dig[0]=0;
        B->exponent++;
    }
    //B.exponent=max(A.exponent, B.exponent);
    return;
}
