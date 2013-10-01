#include <stdio.h>

#include "var.hpp"


var& operator,(var &a, var b)
{
	if (var_type(a) != VAR_VECTOR) {
		var c = a;
		a << c;
	}
	a << b;
	return a;
}

void teste(var a, var b)
{
	printf("teste : %s:%s\n",(const char*)a, (const char*) b);
}

int main(int argc, char** argv)
{
	var numeroNum = "20";
	var numeroStr = 27;

	var result = (long int)numeroNum + (long int)numeroStr;

	printf("%s\n", (const char*)result);
	return 0;
}
