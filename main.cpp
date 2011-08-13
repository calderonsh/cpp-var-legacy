#include <iostream>
#include <sstream>
#include <list>
using namespace std;

#include "var.hpp"

int main(int argc, char** argv)
{
	var myVar;

	myVar = true;

	if(myVar == true)
		cout << "True" << endl;
	else
		cout << "False" << endl;

	myVar = false;

	if(myVar == true)
		cout << "True" << endl;
	else
		cout << "False" << endl;

	return 0;
}
