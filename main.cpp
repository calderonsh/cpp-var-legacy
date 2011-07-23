#include <iostream>
#include <sstream>
#include <map>
using namespace std;

#include "var.hpp"

int main(int argc, char** argv)
{
	var myVar;
		myVar["one"]   = "um";
		myVar["two"]   = "dois";
		myVar["three"] = "três";

		myVar << "quatro";
		myVar << "cinco";

	cout << myVar.cpp_map().size() << endl;

	for(var::internal_map_type::iterator it = myVar.cpp_map().begin(); it != myVar.cpp_map().end(); it++)
		cout<< ((var)(it->first)).cpp_string() << " " << (it->second).cpp_string() << endl;

	return 0;
}
