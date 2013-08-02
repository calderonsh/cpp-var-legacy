#include <stdio.h>
#include <iostream>

#include "var.hpp"

inline var operator+(int a, var b) {return var(a) + b;}
inline var operator+(float a, var b) {return var(a) + b;}
inline var operator+(double a, var b) {return var(a) + b;}
inline var operator+(const char* a, var b) {return var(a) + b;}

int main(int argc, char** argv)
{
	var sobrenome = " Passos";

	var nome = "Miguel" + sobrenome + " Calderon";

	std::cout << nome.cpp_string() << std::endl;
	/*var myVar = 1;

	myVar << "Celso";
	myVar << " Donabella";

	myVar["Miguel"] = "Calderon";

	myVar <<  "Volpi";

	/*for (var value = myVar.begin(); value != myVar.end(); value++)
	{
		std::cout<< value.key().cpp_string() << ":" << (*value).cpp_string() << std::endl;
	}*/

	//std::cout << myVar.encode() << std::endl;

	return 0;
}
