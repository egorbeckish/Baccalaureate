#include <iostream>
#include <fstream>

#define MAX_SIZE_STACK 100


int Stack[MAX_SIZE_STACK];
int t;
void init();
void Push(int);
int Pop();
int Top();
bool IsEmpty();

void T(std::ifstream &input);
void F(std::ifstream &input);



int main(int argc, char const *argv[])
{
	std::cout << "В текстовом файле LOG записано без ошибок логическое выражение в следующем формате:" <<
	"\n<ЛВ> ::= True | False | (¬<ЛВ >) | (<ЛВ > ∧ < ЛВ >) | (<ЛВ > ∨ < ЛВ >)" <<
	"\nЗнаки ∧, ∨ означают соответственно отрицание, конъюнкция, дизъюнкция." <<
	"\nНапример: ((T ∨ F) ∧ (F ∨ T))" <<
	"\nВычислить значение введенного логического выражения."  <<
	"\nПри решении задачи использовать стек. Для реализации АДТ Стек использовать массив.\n\n" << std::endl;

	std::ifstream input("input.txt");

	if (!input)
	{
		std::cout << "File is close!!!" << std::endl;
		exit(EXIT_FAILURE);
	}

	else
	{
		std::cout << "File input is open!!!" << std::endl;
		char k; init();

		// while (input >> k)
		// {
		// 	switch(k)
		// 	{	
		// 		case 'T' : T(input); break;
		// 		case 'F' : F(input); break;
		// 	}
		// }

		input >> k;
		// std::cout << "First element, that met - "<< k << std::endl;
		switch(k)
		{	
			case '(' : F(input); break;
			case 'T' : T(input); break;
			case 'F' : F(input); break;
		}	


		std::cout << "\nStack - [ ";
		for (int i = 0; i < MAX_SIZE_STACK; ++ i)
			std::cout << Stack[i] << " ";
		std::cout << "]";


		std::ofstream output("output.txt");

		if (!output)
		{
			std::cout << "File is close!!!" << std::endl;
			exit(EXIT_FAILURE);
		}

		else 
		{ 
			std::cout << "\n\nFile output is open!!!" << std::endl;
			std::cout << "\nIndex, that take in stack - " << t << std::endl; 
			output << Pop(); 
		}

	}

	std::cout << "\n" << std::endl;

	return 0;
}



void init() { t = - 1; }

void Push(int a)
{
	if (t == MAX_SIZE_STACK)
	{
		std::cout << "Attempt entries a values in full stack!!!" << std::endl;
		exit(EXIT_FAILURE);
	}

	else Stack[++ t] = a;
}

int Pop()
{
	if (t == MAX_SIZE_STACK)
	{
		std::cout << "Attempt read from an empty stack!!!" << std::endl;
		exit(EXIT_FAILURE);
	}

	else { return Stack[t --]; }
}

int Top()
{
	if (!IsEmpty()) { return Stack[t]; }
	else { return EOF; }
}

bool IsEmpty() { return t == - 1; }

void T(std::ifstream &input)
{
	while (!input.eof())
	{
		char k;
		int a, b, c;

		input >> k;
		switch(k)
		{	
			case 'T' : Push(1); T(input); break;
			case 'F' : Push(0); break;
			case '+' : Push((int)'+'); break;
			case '*' : Push((int)'*'); break;
			case ')' : a = Pop(); b = Pop(); c = Pop(); Push((char)b == '+' ? (a + c) : (a * c)); return;
		}
	}
}


void F(std::ifstream &input)
{
	while (!input.eof())
	{
		char k;
		int a, b, c;

		input >> k;
		switch(k)
		{	
			case 'T' : Push(1); break;
			case 'F' : Push(0); F(input); break;
			case '+' : Push((int)'+'); break;
			case '*' : Push((int)'*'); break;
			case ')' : a = Pop(); b = Pop(); c = Pop(); Push((char)b == '+' ? (a + c) : (a * c)); return;
		}
	}
}
