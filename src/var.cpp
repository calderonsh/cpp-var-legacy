#include <stdlib.h>
#include <stdio.h>

#include <sstream>
#include <map>
using namespace std;

#include "var.hpp"


var::var() {
	type = VAR_NULL;
}

var::var(int param)
{
	internal_long = param;
	type = VAR_INTEGER;
}
var::var(long param)
{
	internal_long = param;
	type = VAR_INTEGER;
}

var::var(double param)
{
	internal_double = param;
	type = VAR_FLOAT;
}

var::var(const char* param)
{
	internal_string = param;
	type = VAR_STRING;
}

var::var(string param)
{
	internal_string = param;
	type = VAR_STRING;
}

var::var(void* param)
{
	internal_resource = param;
	type = VAR_RESOURCE;
}

void var::reset()
{
	switch(type)
	{
		case VAR_STRING:
			internal_string = "";

			break;

		case VAR_INTEGER:
			internal_long = 0;

			break;

		case VAR_FLOAT:
			internal_double = 0;

			break;

		case VAR_MAP:
			internal_map.clear();

			break;

		case VAR_RESOURCE:
			internal_resource = NULL;
	}

	type = VAR_NULL;
}

var var::operator =(var param)
{
	this->reset();

	switch(param.type)
	{
		case VAR_STRING:
			internal_string = param.internal_string;
			type = VAR_STRING;

			break;

		case VAR_INTEGER:
			internal_long = param.internal_long;
			type = VAR_INTEGER;

			break;

		case VAR_FLOAT:
			internal_double = param.internal_double;
			type = VAR_FLOAT;

			break;

		case VAR_MAP:
			internal_map = param.internal_map;
			type = VAR_MAP;

			break;

		case VAR_RESOURCE:
			internal_resource = param.internal_resource;
			type = VAR_RESOURCE;
			break;

		case VAR_NULL:
			type=VAR_NULL;
	}

	return param;
}

var var::operator +(var param)
{
	var retval = *this;

	switch(retval.type)
	{
		case VAR_STRING:
			switch(param.type)
			{
				case VAR_STRING:
					retval.internal_string += param.internal_string;
					retval.type = VAR_STRING;

					return retval;

				case VAR_INTEGER:
					retval.internal_string += param.cpp_string();
					retval.type = VAR_STRING;

					return retval;

				case VAR_FLOAT:
					retval.internal_string += param.cpp_string();
					retval.type = VAR_STRING;

					return retval;
			}

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval + param.atofi();

				case VAR_INTEGER:
					retval.internal_long += param.internal_long;
					retval.type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long + param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval + param.atofi();

				case VAR_INTEGER:
					retval.internal_double += param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double += param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
	}

	return (long)0;
}

var var::operator -(var param)
{
	var retval = this->atofi();

	switch(retval.type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval - param.atofi();

				case VAR_INTEGER:
					retval.internal_long -= param.internal_long;
					retval.type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long - param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval - param.atofi();

				case VAR_INTEGER:
					retval.internal_double -= param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double -= param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
	}

	return retval;
}

var var::operator *(var param)
{
	var retval = this->atofi();

	switch(retval.type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval * param.atofi();

				case VAR_INTEGER:
					retval.internal_long *= param.internal_long;
					retval.type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long * param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval * param.atofi();

				case VAR_INTEGER:
					retval.internal_double *= param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double *= param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
	}

	return retval;
}

var var::operator /(var param)
{
	var retval = this->atofi();

	switch(retval.type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval / param.atofi();

				case VAR_INTEGER:
					retval.internal_double = (double)retval.internal_long / param.internal_long;
					retval.internal_long = (long)retval.internal_double;
					retval.type = retval.internal_double == retval.internal_long ? VAR_INTEGER : VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long / param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval / param.atofi();

				case VAR_INTEGER:
					retval.internal_double /= param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double /= param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
	}

	return retval;
}

bool var::operator ==(var param)
{
	switch(type)
	{
		case VAR_STRING:
			switch(param.type)
			{
				case VAR_INTEGER:
					return c_double() == param.internal_long;

				case VAR_FLOAT:
					return c_double() == param.internal_double;

				case VAR_STRING:
					return internal_string == param.internal_string ;

				case VAR_NULL:
					return c_double() == 0;
			}
		break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_long == param.internal_long;

				case VAR_FLOAT:
					return internal_long == param.internal_double;

				case VAR_STRING:
					return internal_long == param.c_double();

				case VAR_NULL:
					return internal_long == 0;
			}
		break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_double == param.internal_long;

				case VAR_FLOAT:
					return internal_double == param.internal_double;

				case VAR_STRING:
					return internal_double == param.c_double();

				case VAR_NULL:
					return internal_double == 0;
			}
		break;

		case VAR_RESOURCE:
			if(param.type == VAR_RESOURCE && internal_resource == param.internal_resource)
				return true;
		break;

		case VAR_NULL:
		{
			switch(param.type)
			{
				case VAR_INTEGER:
					return 0 == param.internal_long;
				case VAR_FLOAT:
					return 0 == param.internal_double;
				case VAR_STRING:
					return (0 == param.c_double());
				case VAR_NULL:
					return true;
			}
		}
		break;
	}

	return false;
}

bool var::operator <(var param)
{
	switch(type)
	{
		case VAR_STRING:
			switch(param.type)
			{
				case VAR_INTEGER:
					return c_double() < param.internal_long;

				case VAR_FLOAT:
					return c_double() < param.internal_double;

				case VAR_STRING:
					return internal_string < param.internal_string ;

				case VAR_NULL:
					return c_double() < 0;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_long < param.internal_long;

				case VAR_FLOAT:
					return internal_long < param.internal_double;

				case VAR_STRING:
					return internal_long < param.c_double();

				case VAR_NULL:
					return internal_long < 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_double < param.internal_long;

				case VAR_FLOAT:
					return internal_double < param.internal_double;

				case VAR_STRING:
					return (internal_double < param.c_double());

				case VAR_NULL:
					return internal_double < 0;
			}
			break;

		case VAR_NULL:
		{
			switch(param.type)
			{
				case VAR_INTEGER:
					return 0 < param.internal_long;

				case VAR_FLOAT:
					return 0 < param.internal_double;

				case VAR_STRING:
					return 0 < param.c_long();

				case VAR_NULL:
					return false;
			}
		}
			break;

		case VAR_RESOURCE:
				return false;
	}
	return false;
}

bool var::operator >(var param)
{
	switch(type)
	{
		case VAR_STRING:
			switch(param.type)
			{
				case VAR_INTEGER:
					return c_double() > param.internal_long;

				case VAR_FLOAT:
					return c_double() > param.internal_double;

				case VAR_STRING:
					return internal_string > param.internal_string ;

				case VAR_NULL:
					return c_double() > 0;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_long > param.internal_long;

				case VAR_FLOAT:
					return internal_long > param.internal_double;

				case VAR_STRING:
					return internal_long > param.c_double();

				case VAR_NULL:
					return internal_long > 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_double > param.internal_long;

				case VAR_FLOAT:
					return internal_double > param.internal_double;

				case VAR_STRING:
					return (internal_double > param.c_double());

				case VAR_NULL:
					return internal_double > 0;
			}
			break;

		case VAR_NULL:
		{
			switch(param.type)
			{
				case VAR_INTEGER:
					return 0 > param.internal_long;

				case VAR_FLOAT:
					return 0 > param.internal_double;

				case VAR_STRING:
					return 0 > param.c_long();

				case VAR_NULL:
					return false;
			}
		}
			break;

		case VAR_RESOURCE:
				return false;
	}
	return false;
}

bool var::operator &&(var param)
{
	var retval = atofi();
	param = param.atofi();

	switch(retval.type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_INTEGER:
					return retval.internal_long && param.internal_long;

				case VAR_FLOAT:
					return retval.internal_long && param.internal_double;
			}

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_INTEGER:
					return retval.internal_double && param.internal_long;

				case VAR_FLOAT:
					return retval.internal_double && param.internal_double;
			}
	}
	return false;
}

long var::operator |(var param)
{
	var retval = atofi();
	param = param.atofi();

	switch(retval.type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_INTEGER:
					return retval.internal_long | param.internal_long;

				case VAR_FLOAT:
					return retval.internal_long | (long)param.internal_double;
			}

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_INTEGER:
					return (long)retval.internal_double | param.internal_long;

				case VAR_FLOAT:
					return (long)retval.internal_double | (long)param.internal_double;
			}
	}

	return false;
}

var& var::operator[](var param)
{
	if(type != VAR_MAP) {
		reset();
		type = VAR_MAP;
	}

	return (var&)(internal_map[param]);
}

var& var::operator <<(var param)
{
	if(type != VAR_MAP){
		reset();
		type = VAR_MAP;
	}

	map<var,var>::iterator iterador;

	for(int i = 0; true; i++)
	{
		if(internal_map.find(i) == internal_map.end())
		{
			internal_map[i] = param;
			return *this;
		}
	}
}

var var::atofi()
{
	var retval;
	switch(type)
	{
		case VAR_STRING:
			retval.internal_double = atof(internal_string.c_str());
			retval.internal_long = (long)retval.internal_double;
			retval.type = retval.internal_double == retval.internal_long ? VAR_INTEGER : VAR_FLOAT;
			break;

		case VAR_INTEGER:
			retval.internal_long = internal_long;
			retval.type = VAR_INTEGER;
			break;

		case VAR_FLOAT:
			retval.internal_double = internal_double;
			retval.type = VAR_FLOAT;
			break;

		case VAR_NULL:
			retval.internal_long = 0;
			retval.type = VAR_INTEGER;
			break;
	}

	return retval;
}

long var::c_long()
{
	switch(type)
	{
		case VAR_STRING:
			return (long)atof(internal_string.c_str());

		case VAR_INTEGER:
			return internal_long;

		case VAR_FLOAT:
			return (long)internal_double;

	}

	return 0;
}

double var::c_double()
{
	switch(type)
	{
		case VAR_STRING:
			return atof(internal_string.c_str());

		case VAR_INTEGER:
			return (double)internal_long;

		case VAR_FLOAT:
			return internal_double;
	}

	return 0;
}

string var::cpp_string()
{
	string retval;
	char* buffer = (char*) malloc(32);

	switch(type)
	{
		case VAR_STRING:
			return  internal_string;

		case VAR_INTEGER:
			sprintf(buffer,"%li", internal_long);
			break;

		case VAR_FLOAT:
			sprintf(buffer,"%f", internal_double);
			break;

		default:
			sprintf(buffer,"0");
	}

	retval = buffer;
	free(buffer);

	return retval;
}

 var::internal_map_type& var::cpp_map()
{
	return (internal_map_type&) internal_map;
}
