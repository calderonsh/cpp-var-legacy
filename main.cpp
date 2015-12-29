#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <map>

#include <var.hpp>
#include <php/php.hpp>
using namespace php;

class
{
	public:
		static std::string stringify(const var& object)
		{
			return object.encode();
		}

		static var parse(const var& json)
		{
			var result;
			result.decode(json);

			return result;
		}
} JSON;

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

#define forin(a,b) for(var a; a.in(b);)

int main(int argc, char** argv)
{
	var mesh = JSON.parse(file_get_contents("mesh.zrb"));

	console.time("Miguel");

	forin(i, mesh)
	{
		console.log(i);

		forin(j, mesh[i]) {
			console.log(j + ": " + mesh[i][j].encode());
		}
	}

	console.timeEnd("Miguel");

	var dSample;

	dSample.push("BrazilJS");
	dSample.push(3.1415);


	var objSample;

	objSample["Key"] = "Value";
	objSample["node"] = "js";

	dSample.push(objSample);

	console.log(JSON.stringify(dSample));
}
