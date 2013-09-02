#include <stdio.h>

#include "var.hpp"


int main(int argc, char** argv)
{
	var linguagens;

	linguagens << "PHP";	//0	-5
	linguagens << "ASP";	//1	-4
	linguagens << "C-Ansi";	//2	-3
	linguagens << "C++";	//3	-2
	linguagens << "Python";	//4	-1

	var asp;
	asp["nome"] = linguagens[1];
	asp["qualidade"] = "lixo";

	var cpp;
	cpp["nome"] = "C e " + linguagens[2];
	cpp["nota"] = 10;

	linguagens[1] = asp;
	linguagens[2] = cpp;

	var serialized = linguagens.encode();

	printf((const char*)serialized);
	printf("\n%s\n", (const char*)linguagens[-1]);

	return 0;
}
