# cpp-var
Dynamically typed variables for C++ based in javascript.

## Examples of use:

### Scalar variables - integer

**code**

```
#include <var.hpp>

int main(int argc, char** argv)
{
	var currentYear = 2021;
	var age = 36;

	var bornYear = currentYear - age;

	printf("You born in the year %d.\n", (int) bornYear);


	return 0;
}
```

**output**
```
$ ./main
You born in the year 1985.
```

### Scalar variables - string

**code**

```
#include <var.hpp>

int main(int argc, char** argv)
{
	var sample;

	sample = "the lazy dog";

	printf("The quick brown fox jumps over %s.\n", (const char*) sample);

	return 0;
}
```

**output**
```
$ ./main
The quick brown fox jumps over the lazy dog.
```
