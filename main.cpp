#include <iostream>
#include <sstream>
#include <list>
using namespace std;

#include "var.hpp"

int main(int argc, char** argv)
{
	var myVar;

	myVar = (var) true + 0;
	cout << myVar.cpp_string() << endl;

	myVar = (var) true + 1;
	cout << myVar.cpp_string() << endl;

	myVar = (var) true * 0;
	cout << myVar.cpp_string() << endl;

	myVar = (var) true * 1;
	cout <<myVar .cpp_string() << endl;

	return 0;
}
