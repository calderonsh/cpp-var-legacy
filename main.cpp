#include <iostream>
#include "var.hpp"
using namespace std;

int main(int argc, char** argv)
{
	var myVar;
		myVar << "Primeiro";
		myVar << "Segundo";
		myVar << "Terceiro";
		myVar << "Quarto";

	//var key, value;

	//var::internal_map_type::iterator it;
	//for(it = myVar.cpp_map().begin(); it != myVar.cpp_map().end(); it++)
	//	cout << (it->first).cpp_string() + "::" + (it->second).cpp_string() + "\n";

	cout << "Tipo:" << var_type(myVar) << endl;

	for(int i = 0; i < myVar.size(); i++) {
		cout << (myVar[i]).cpp_string() << endl;
	}

	return 0;
}
