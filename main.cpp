#include <stdio.h>
#include <iostream>

#include "var.hpp"



int main(int argc, char** argv)
{
	var sobrenome = " Passos";

	var nome = (int)1 + sobrenome + " Calderon";

	std::cout << nome << std::endl;
	return 0;
}
