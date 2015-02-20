#include <iostream>
#include <string>

#include <var.hpp>

int main(int argc, char** argv)
{
	var str1 = "Hello,";
	var str2 = " Miguel ";
	var str3 = " world!";
	var str4 = " Have a nice day!";
	var res = str1.concat(str3);

	printf("%s\n", res.encode().c_str());
}
