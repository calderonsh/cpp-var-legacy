#include <stdlib.h>
#include <stdio.h>

#include <map>

#include <var.hpp>


int main(int argc, char** argv)
{

	var json;
	json.decode("{\"mac\":\"coisa de beesha\",\"debian\":\"coisa de macho\"}");

	printf("JSON: %s\n", (const char*)json.encode());
	printf("mac: %s\n", (const char*)json["mac"]);
	printf("debian: %s\n", (const char*)json["debian"]);

	var splitted = var("Luis,Felipe,Beatriz").split(",").join("|");

	json["pedrita"] = splitted;

	printf("novo JSON: %s\n", (const char*)json.encode());
}
