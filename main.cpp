#include <iostream>
#include <string>

#include <var.hpp>

int main(int argc, char** argv)
{
	var fruits; fruits.decode("[\"Banana\", \"Orange\", \"Apple\", \"Mango\"]");
	var bla = fruits.push("Kiwi");


	printf("%s\n", fruits.encode().c_str());
	printf("%s\n", bla.encode().c_str());
}
