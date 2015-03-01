#include <iostream>
#include <string>

#include <var.hpp>

int main(int argc, char** argv)
{
	var fruits = "Banana,Orange,Apple,Mango";

	fruits = fruits.split(",");
	fruits.splice(2, 0, "Lemon", "Kiwi");

	printf("%s\n", fruits.encode().c_str());
}
