#include <iostream>
#include "var.hpp"
using namespace std;

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
