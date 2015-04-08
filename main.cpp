#include <stdlib.h>
#include <stdio.h>

#include <map>

#include <var.hpp>


int main(int argc, char** argv)
{
	var json;
	json.decode("{\"user\":\"Miguel Calderon\",\"company\":\"Terra Networks\"}");

	printf("JSON: %s\n", json.encode().c_str());
	printf("User: %s\n", (const char*)json["user"]);
	printf("Company: %s\n", (const char*)json["company"]);

	for (var it = json.begin(); it != json.end(); it++) {
		printf("%s => %s\n", (const char*)it.key(), (const char*)*it);
	}

	var splitted = var("Luis,Felipe,Beatriz").split(",").join("|");

	json["pedrita"] = splitted;

	printf("novo JSON: %s\n", json.encode().c_str());
}
