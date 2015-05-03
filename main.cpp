#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <map>

#include <var.hpp>


var file_get_contents(const var &filename)
{
	const char* filename_c = filename;

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

class Console
{
	public:
		void log(const var&);

		void time(const var&);
		void timeEnd(const var&);

	private:
		var times;
};

void Console::log(const var& that)
{
	printf("%s\n", (const char*)that);
}

void Console::time(const var& label)
{
	timeval time;
	gettimeofday(&time, NULL);
	double miliseconds = time.tv_sec*1000 + time.tv_usec/1000;
	times[label] = miliseconds;
}

void Console::timeEnd(const var& label)
{
	timeval time;
	gettimeofday(&time, NULL);
	double miliseconds = time.tv_sec*1000 + time.tv_usec/1000;

	printf("%s: %1.0fms\n", (const char*)label, (double)(var(miliseconds) - times[label]));
}

Console console;


int main(int argc, char** argv)
{
	var mesh;

	mesh.decode(file_get_contents("mesh.zrb"));

	console.time("Miguel");
	var i;
	while(i.in(mesh))
	{
		console.log(i);

		var j;
		while(j.in(mesh[i])) {
			console.log(j + ": " + mesh[i][j].encode());
		}
	}

	console.timeEnd("Miguel");
}
