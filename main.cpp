#include <stdlib.h>
#include <stdio.h>

#include <map>

#include <var.hpp>


int main(int argc, char** argv)
{

	var felipe;
	felipe.decode("{\"mac\":\"coisa de beesha\",\"debian\":\"coisa de macho\"}");

	printf("JSON: %s\n", (const char*)felipe.encode());
	printf("mac: %s\n", (const char*)felipe["mac"]);
	printf("debian: %s\n", (const char*)felipe["debian"]);

	var splitted = var("Luis,Felipe,Beatriz").split(",").join("|");

	felipe["pedrita"] = splitted;

	printf("novo JSON: %s\n", (const char*)felipe.encode());
}
