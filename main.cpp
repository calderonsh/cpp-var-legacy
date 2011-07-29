#include <iostream>
#include <sstream>
#include <list>
using namespace std;

#include "var.hpp"

int main(int argc, char** argv)
{
	var myVar1 = 5;
	var myVar2 = "5";
	var myVar3;

	myVar3 = myVar1 + myVar2;
	cout<< myVar3.cpp_string() << endl;

	myVar3 = myVar2 + myVar1;
	cout<< myVar3.cpp_string() << endl;

	return 0;
}
