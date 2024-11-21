#include <iostream>
#include "binary.h"

void binary(unsigned char *, int);


int main(int argc, char const *argv[])
{
	signed int _int = -2'147'483'647;
	unsigned int un_int = 4'294'967'295;

	char _char = -128;
	unsigned char un_char = 255;

	short _short = -32'768;
	unsigned short un_short = 65'535;

	long long _long_long = -9'223'372'036'854'775'807;
	unsigned long long un_long_long = 18'446'744'073'709'551'615;

	float _float = 1.512;
	// unsigned float un_float = 3.452;

	double _double = 8.256;
	// unsigned double un_double = 17.356;


	std::cout << std::endl;

	std::cout << "int " << (signed int)_int << " = "; binary((unsigned char *) &_int, sizeof(_int));
	std::cout << "unsigned int " << (unsigned int)un_int << " = "; binary((unsigned char *) &un_int, sizeof(un_int));

	std::cout << std::endl;

	std::cout << "char " << (int)_char << " = "; binary((unsigned char *) &_char, sizeof(un_char));
	std::cout << "unsigned char " << (unsigned int)un_char << " = "; binary((unsigned char *) &un_char, (sizeof(un_char)));

	std::cout << std::endl;

	std::cout << "short " << (short)_short << " = "; binary((unsigned char *) &_short, sizeof(_short));
	std::cout << "unsigned short " << (unsigned short)un_short << " = "; binary((unsigned char *) &un_char, sizeof(un_short));

	std::cout << std::endl;

	std::cout << "long long " << (long long)_long_long << " = "; binary((unsigned char *) &_long_long, sizeof(long long));
	std::cout << "unsigned long long " << (unsigned long long)un_long_long << " = "; binary((unsigned char *) &un_long_long, sizeof(unsigned long long));

	std::cout << std::endl;

	std::cout << "float " << (float)_float << " = "; binary((unsigned char *) &_float, sizeof(float));
	// std::cout << "unsigned float " << (unsigned float)un_float << " = "; binary((unsigned char *) &un_float, (sizeof(un_float));

	std::cout << std::endl;

	std::cout << "double " << (double)_double << " = "; binary((unsigned char *) &_double, sizeof(double));
	// std::cout << "unsigned double " << (unsigned double)un_char << " = "; binary((unsigned char *) &un_double, (sizeof(un_double)));
	return 0;
}
