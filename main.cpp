#include <stdio.h>
#include <iostream>

#include "var.hpp"


int main(int argc, char** argv)
{
	var linguagens;

	linguagens << "PHP";	//0
	linguagens << "ASP";	//1
	linguagens << "C++";	//2
	linguagens << "Python";	//3

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

	return 0;
}
