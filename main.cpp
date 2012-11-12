#include <iostream>
#include "var.hpp"
using namespace std;

int main(int argc, char** argv)
{
	var myVar;
		myVar ["a"] = "Primeiro";
		myVar << "Segundo";
		myVar << "Terceiro";
		myVar << "Quarto";

	var key, value;

	for(var i = myVar.begin(); i != myVar.end(); i++)
	{
		cout << i.key().cpp_string() << ":" << (*i).cpp_string() << endl;
		*i = *i + ".";
	}

	while(myVar.fetch(key, value)) {
		cout << key.cpp_string() << ":" << value.cpp_string() << endl;
	}

	return 0;
}
