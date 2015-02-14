#include <stdlib.h>
#include <stdio.h>

#include <map>

#include <var.hpp>


int main(int argc, char** argv)
{
	var str = "Hello World!     ";
	var n = str.trim();

	printf("%s\n", n.encode().c_str());
}
