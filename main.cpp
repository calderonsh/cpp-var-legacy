#include <iostream>
#include "var.hpp"
using namespace std;

int main(int argc, char** argv)
{
	var myVar;

	myVar = ":)";

	switch(var_type(myVar))
	{
		case VAR_NULL:
			cout << "VAR_NULL" <<endl;
		break;

		case VAR_BOOLEAN:
			cout << "VAR_BOOLEAN" <<endl;
		break;

		case VAR_INTEGER:
			cout << "VAR_INTEGER" <<endl;
		break;

		case VAR_FLOAT:
			cout << "VAR_FLOAT" <<endl;
		break;

		case VAR_STRING:
			cout << "VAR_STRING" <<endl;
		break;

		case VAR_MAP:
			cout << "VAR_MAP" <<endl;
		break;

		case VAR_RESOURCE:
			cout << "VAR_RESOURCE" <<endl;
		break;
	}

	return 0;
}
