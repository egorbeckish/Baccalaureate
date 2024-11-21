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
	int hours;
	int minutes;
	int seconds;
} Time;



int *duraction(int T1, int T2)
{
	int *passed = (int *)calloc(3, sizeof(int));

    Time f = {0, 0, 0};
    Time s = {0, 0, 0};

    f.hours = T1 / 3600;
    s.hours = T2 / 3600;
    f.minutes = (T1 % 3600) / 60;
    s.minutes = (T2 % 3600) / 60;
    f.seconds = (T1 % 3600) % 60;
    s.seconds = (T2 % 3600) % 60;


    if (f.hours <= s.hours)
    {
        passed[0] = s.hours - f.hours;
        passed[1] = s.minutes - f.minutes;
        passed[2] = s.seconds - f.seconds;

        if (passed[1] < 0) {passed[0] --; passed[1] += 60;}
        if (passed[2] < 0) {passed[1] --; passed[2] += 100;}
    }


    else
    {
        passed[0] = 24 - s.hours + f.hours;
        passed[1] = f.minutes - s.minutes;
        passed[2] = f.seconds - s.seconds;

        if (passed[1] < 0) {passed[0] --; passed[1] += 60;}
        if (passed[2] < 0) {passed[1] --; passed[2] += 100;}
    }


    printf("Second time - %i h\t%i m\t%i s\n", s.hours, s.minutes, s.seconds);
    printf("First time - %i h\t%i m\t%i s\n", f.hours, f.minutes, f.seconds);
    // printf("%i\t%i\t%i\n", passed[0], passed[1], passed[2]);
    return passed;

}


void task7()
{
	int first_time, second_time;

	printf("Enter first time in seconds: ");
	scanf("%i", &first_time);

	printf("Enter second time in seconds: ");
	scanf("%i", &second_time);
	printf("\n");

	int *answer = duraction(first_time, second_time);
	printf("\t\t%i\t%i\t%i\n", answer[0], answer[1], answer[2]);
}


int main(int argc, char const *argv[])
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
  task7();
  
  return 0;
}
