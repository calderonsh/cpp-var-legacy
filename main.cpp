#include <stdlib.h>
#include <stdio.h>

#include <map>

#include <var.hpp>


int main(int argc, char** argv)
{
	var a = true;
	var b = "4";
	var c = a + b;

	printf("%s\n%d\n", c.encode().c_str(),var::type(c));
}
