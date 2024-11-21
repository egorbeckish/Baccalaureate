//---------------------------------------------------------------------------
// Модуль вычисления значений символьных выражений, версия 2.2 (win32)
// Copyright (C) 2003-2020 by Voverkill
//---------------------------------------------------------------------------
#ifndef __POLSTR_H__
#define __POLSTR_H__
//---------------------------------------------------------------------------
#include <locale.h>
#include <windows.h>
#include <stdio.h>
//---------------------------------------------------------------------------
// Указатели на функции из DLL
struct PolStr
{
	typedef int(__stdcall *GetErrorProc)();
	typedef unsigned(__stdcall *StrToPolStrProc)(const char *, char *, unsigned);
	typedef char *(__stdcall *CreatePolStrProc)(const char *, unsigned);
	typedef double(__stdcall *EvalStrProc)(const char *, double, unsigned);
	typedef double(__stdcall *EvalStrVProc)(const char *, const double *, unsigned, unsigned, unsigned);
	typedef double(__stdcall *EvalPolStrProc)(const char *, double, unsigned);
	typedef double(__stdcall *EvalPolStrVProc)(const char *, const double *, unsigned, unsigned);

	HMODULE dll;
	GetErrorProc GetError;
	StrToPolStrProc StrToPolStr;
	CreatePolStrProc CreatePolStr;
	EvalStrProc EvalStr;
	EvalStrVProc EvalStrV;
	EvalPolStrProc EvalPolStr;
	EvalPolStrVProc EvalPolStrV;

	void ShowError(const char *procname = NULL)
	{
		LPVOID buf;
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			LPSTR(&buf),
			0,
			NULL
		);
		if (procname == NULL) printf("PolStr.dll: %s", (char *)buf);
		else printf("PolStr.dll::%s: %s", procname, (char *)buf);
		LocalFree(buf);
	}

	FARPROC LoadProc(const char *procname)
	{
		FARPROC proc = GetProcAddress(dll, procname);
		if (proc == NULL)
		{
			ShowError(procname);
		}
		return proc;
	}

	PolStr() : dll(NULL), GetError(NULL), StrToPolStr(NULL), CreatePolStr(NULL),
		EvalStr(NULL), EvalStrV(NULL), EvalPolStr(NULL), EvalPolStrV(NULL)
	{
		setlocale(LC_ALL, "russian");
		dll = LoadLibraryA("PolStr.dll");
		if (dll != NULL)
		{
			GetError = (GetErrorProc)LoadProc("GetError");
			StrToPolStr = (StrToPolStrProc)LoadProc("StrToPolStr");
			CreatePolStr = (CreatePolStrProc)LoadProc("CreatePolStr");
			EvalStr = (EvalStrProc)LoadProc("EvalStr");
			EvalStrV = (EvalStrVProc)LoadProc("EvalStrV");
			EvalPolStr = (EvalPolStrProc)LoadProc("EvalPolStr");
			EvalPolStrV = (EvalPolStrVProc)LoadProc("EvalPolStrV");
		}
		else
		{
			ShowError();
		}
	}

	~PolStr()
	{
		if (dll != NULL)
		{
			//FreeLibrary(dll);
		}
	}
} _;
//---------------------------------------------------------------------------
#define ERR_OK              0
#define ERR_SYNTAX_ERROR    1
#define ERR_BAD_ARGUMENT    2
#define ERR_STACK_ERROR     3
#define ERR_INVALID_PARAM   4
#define ERR_HUGE_VALUE      5
#define ERR_UNKNOWN_DER     6
#define ERR_OUT_OF_MEMORY   7
#define ERR_DLL_NOT_FOUND   8
#define ERR_PROC_NOT_FOUND  9
//---------------------------------------------------------------------------
// Индикатор ошибки:
// • ERR_OK             - ошибки нет;
// • ERR_SYNTAX_ERROR   - синтаксическая ошибка;
// • ERR_BAD_ARGUMENT   - неверный индекс у аргумента;
// • ERR_STACK_ERROR    - в стеке нет необходимых данных (обычно это следствие
//                        синтаксической ошибки);
// • ERR_INVALID_PARAM  - неверный параметр у процедуры (нулевой указатель,
//                        производная по несуществующему аргументу и т.п.);
// • ERR_HUGE_VALUE     - числовая константа не верна или выходит за рамки
//                        типа double;
// • ERR_UNKNOWN_DER    - производная не может быть вычислена;
// • ERR_OUT_OF_MEMORY  - не хватает динамической памяти;
// • ERR_DLL_NOT_FOUND  - библиотека PolStr.dll не найдена;
// • ERR_PROC_NOT_FOUND - в библиотеке PolStr.dll не найдена одна или несколько
//                        требуемых процедур.
// Если ошибок было несколько, хранится значение самой первой.
int GetError()
{
	if (!_.dll) return ERR_DLL_NOT_FOUND;
	if (!_.GetError || !_.StrToPolStr || !_.CreatePolStr || !_.EvalStr || !_.EvalStrV ||
		!_.EvalPolStr || !_.EvalPolStrV) return ERR_PROC_NOT_FOUND;
	return _.GetError();
}
//---------------------------------------------------------------------------
// Преобразование выражения к обратной польской строке (ОПС). Выражение может
// содержать числовые константы, числа PI и E, аргументы (x для скалярного,
// x1..xn для векторного n-мерного аргумента), скобки и следующие операции:
// • +   (сложение или унарный плюс);
// • -   (вычитание или унарный минус);
// • *   (умножение);
// • /   (деление);
// • ^   (возведение в степень);
// • sin (синус);
// • cos (косинус);
// • tg  (тангенс);
// • ctg (котангенс);
// • exp (экспоненциальная функция, exp x = e^x);
// • ln  (натуральный логарифм);
// • lg  (логарифм по основанию 10).
// Регистр символов не важен. Скобки после функций от одного аргумента
// ставить не обязательно (например, верны следующие выражения: cos 2,
// exp(x), sin (x + pi)). После преобразования в ОПС будут содержаться
// следующие символы:
// • s - sin;
// • c - cos;
// • t - tg;
// • z - ctg;
// • e - exp;
// • l - ln;
// • g - lg;
// • n - унарный минус;
// • p - унарный плюс;
// • q - число e;
// • w - число pi.
// Знаки операций, числовые константы и аргументы остаются без изменений.
// Скобки убираются. Аргументы:
// 1) char *expr - указатель на строку, содержащую исходное выражение;
// 2) char *pstr - указатель на строку, в которую будет помещено выражение
//    в виде ОПС (если равен NULL, строка не формируется, функция только
//    вычисляет ее длину);
// 3) unsigned arg_count - количество аргументов в выражении (если аргумент
//    скалярный, должно быть равно нулю).
// Возвращаемое значение - длина ОПС. Выражение сканируется до тех пор, пока
// не встретится символ конца строки, символ ";" или не возникнет ошибка.
// Если в процессе преобразования возникла ошибка, ОПС будет сформирована не
// полностью. Следите за индикатором ошибки!
unsigned StrToPolStr(const char *expr, char *pstr, unsigned arg_count = 0)
{
	return _.StrToPolStr(expr, pstr, arg_count);
}
//---------------------------------------------------------------------------
// Создание ОПС. Аргументы:
// 1) char *expr - указатель на строку, содержащую исходное выражение;
// 2) unsigned arg_count - количество аргументов в выражении.
// Данная функция просто сначала вызывает функцию StrToPolStr, чтобы
// вычислить длину ОПС, затем выделяет необходимую для хранения ОПС память и
// снова вызывает StrToPolStr для формирования ОПС. Память выделяется
// динамически, поэтому не забудьте освободить ее оператором delete [].
char *CreatePolStr(const char *expr, unsigned arg_count)
{
	return _.CreatePolStr(expr, arg_count);
}
//---------------------------------------------------------------------------
// Вычисление выражения (скалярный аргумент). Аргументы:
// 1) char *expr - указатель на строку, содержащую выражение;
// 2) double arg - значение аргумента;
// 3) unsigned der - порядок производной (0 - по умолчанию - вычислить
//    выражение, 1 - первую производную, 2 - вторую производную и т.д.).
// Данная функция просто возвращает значение функции EvalStr для векторного
// аргумента: EvalStr(expr, &arg, 0, der, 0).
double EvalStr(const char *expr, double arg, unsigned der = 0)
{
	return _.EvalStr(expr, arg, der);
}
//---------------------------------------------------------------------------
// Вычисление выражения (векторный аргумент). Аргументы:
// 1) char *expr - указатель на строку, содержащую выражение;
// 2) double *args - вектор аргументов (нулевой элемент содержит x1,
//    первый элемент - x2 и т.д);
// 3) unsigned arg_count - количество аргументов в выражении;
// 4) unsigned der - порядок производной (по умолчанию 0);
// 5) unsigned arg_idx - по какому аргументу берется производная (0 - по
//    умолчанию - по единственному скалярному аргументу, 1 - по x1 для
//    векторного аргумента, 2 - по x2 и т.д.).
// Данная функция сначала формирует ОПС pstr вызовом функции CreatePolStr,
// затем, если была ошибка, возвращает ноль, иначе возвращает значение
// функции EvalPolStr(pstr, args, der, arg_idx). Замечание: если одно и то
// же выражение вычисляется несколько раз, то выделение памяти для ОПС,
// формирование ОПС и освобождение памяти будут производиться многократно,
// что не есть хорошо. В этом случае лучше один раз самостоятельно создать
// ОПС с помощью функции CreatePolStr, а затем вызывать EvalPolStr вместо
// EvalStr.
double EvalStr(const char *expr, const double *args, unsigned arg_count,
	unsigned der = 0, unsigned arg_idx = 0)
{
	return _.EvalStrV(expr, args, arg_count, der, arg_idx);
}
//---------------------------------------------------------------------------
// Вычисление выражения в виде ОПС (скалярный аргумент). Аргументы:
// 1) char *pstr - указатель на строку, содержащую ОПС;
// 2) double arg - значение аргумента;
// 3) unsigned der - порядок производной (по умолчанию 0).
// Данная функция просто возвращает значение функции EvalPolStr для
// векторного аргумента: EvalPolStr(pstr, &arg, der, 0).
double EvalPolStr(const char *pstr, double arg, unsigned der = 0)
{
	return _.EvalPolStr(pstr, arg, der);
}
//---------------------------------------------------------------------------
// Вычисление выражения в виде ОПС (векторный аргумент). Это основная функция
// для вычисления выражений, все остальные функции так или иначе вызывают ее.
// Аргументы:
// 1) char *pstr - указатель на строку, содержащую ОПС;
// 2) double *args - вектор аргументов;
// 3) unsigned der - порядок производной (по умолчанию 0);
// 4) unsigned arg_idx - по какому аргументу берется производная (по
//    умолчанию 0).
// Функция возвращает значение выражения, если во время вычислений не было
// ошибки, иначе ноль. Ошибка ERR_UNKNOWN_DER возникает в том случае, если
// невозможно вычислить производную выражения. Если выражение содержит только
// операции +, - и *, то можно вычислит любую его производную. Если оно
// содержит другие функции и операции, то можно вычислить только первую и
// вторую производные.
double EvalPolStr(const char *pstr, const double *args, unsigned der = 0,
	unsigned arg_idx = 0)
{
	return _.EvalPolStrV(pstr, args, der, arg_idx);
}
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
