#include <iostream>
#include <sstream>
#include <list>
using namespace std;

#include "var.hpp"

int main(int argc, char** argv)
{
	var myVar;

	myVar = (var) "20.0" == 20.0;
	cout << myVar.cpp_string() << endl;

	myVar = (var) "20.0a" == 20.0;
	cout << myVar.cpp_string() << endl;

	myVar = (var) "20" == 20;
	cout << myVar.cpp_string() << endl;

	myVar = (var) "20a" == 20;
	cout << myVar.cpp_string() << endl;


	myVar = (var) 20.0 == "20.0";
	cout << myVar.cpp_string() << endl;

	myVar = (var) 20.0 == "20.0a";
	cout << myVar.cpp_string() << endl;

	myVar = (var) 20 == "20";
	cout << myVar.cpp_string() << endl;

	myVar = (var) 20 == "20a";
	cout << myVar.cpp_string() << endl;

	return 0;
}
