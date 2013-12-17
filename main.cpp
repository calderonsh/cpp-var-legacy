#include <stdlib.h>
#include <stdio.h>

#include <typeinfo>

#include <var.hpp>

var file_get_contents(const var &filename)
{
	const char* filename_c = (const char*)filename;

	char *ret_c;

	FILE *file = fopen(filename_c, "r");

	if (file == NULL) {
		return false;
	}

	fseek (file , 0, SEEK_END);
	size_t size = ftell(file);
	rewind (file);

	ret_c = (char*)malloc(size + 1);

	size = fread(ret_c, 1, size, file);

	fclose(file);

	ret_c[size] = '\0';
	var ret = ret_c;
	free(ret_c);

	return ret;
}

int main(int argc, char** argv)
{
	var beagle;

	beagle.decode("\"Miguel Passos \nCalderon\"");

	printf((const char*) beagle.encode());

	return 0;
}
