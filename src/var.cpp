#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "var.hpp"

var::var()
{
	type = VAR_NULL;
}

var::var(const bool& param)
{
	internal_bool = param;
	type = VAR_BOOLEAN;
}

var::var(const int& param)
{
	internal_long = param;
	type = VAR_INTEGER;
}

var::var(const long& param)
{
	internal_long = param;
	type = VAR_INTEGER;
}

var::var(const double& param)
{
	internal_double = param;
	type = VAR_FLOAT;
}

var::var(const char* param)
{
	internal_string = param;
	type = VAR_STRING;
}

var::var(const string& param)
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
		case VAR_BOOLEAN:
			internal_bool = false;

			break;

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

			break;
	}

	type = VAR_NULL;
}

var var::operator =(const var& param)
{
	this->reset();

	switch(param.type)
	{
		case VAR_BOOLEAN:
			internal_bool = param.internal_bool;
			type = VAR_BOOLEAN;

			break;

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

var var::operator +(const var& param)
{
	var retval = *this;

	switch(retval.type)
	{
		case VAR_BOOLEAN:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					retval.internal_bool = internal_bool || param.internal_bool;
					retval.type = VAR_BOOLEAN;

					return retval;

				case VAR_INTEGER:
					retval.internal_bool = internal_bool || param.internal_long;
					retval.type = VAR_BOOLEAN;

					return retval;

				case VAR_FLOAT:
					retval.internal_bool = internal_bool || param.internal_double;
					retval.type = VAR_BOOLEAN;

					return retval;
			}
			break;

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
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval + param.num();

				case VAR_INTEGER:
					retval.internal_long += param.internal_long;
					retval.type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long + param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval + param.num();

				case VAR_INTEGER:
					retval.internal_double += param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double += param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

var var::operator -(const var& param)
{
	var retval = this->num();

	switch(retval.type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval - param.num();

				case VAR_INTEGER:
					retval.internal_long -= param.internal_long;
					retval.type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long - param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval - param.num();

				case VAR_INTEGER:
					retval.internal_double -= param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double -= param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

var var::operator *(const var& param)
{
	var retval = *this;

	switch(retval.type)
	{
		case VAR_BOOLEAN:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					retval.internal_bool = internal_bool && param.internal_bool;
					retval.type = VAR_BOOLEAN;

					return retval;

				case VAR_INTEGER:
					retval.internal_bool = internal_bool && param.internal_long;
					retval.type = VAR_BOOLEAN;

					return retval;

				case VAR_FLOAT:
					retval.internal_bool = internal_bool && param.internal_double;
					retval.type = VAR_BOOLEAN;

					return retval;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval * param.num();

				case VAR_INTEGER:
					retval.internal_long *= param.internal_long;
					retval.type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long * param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval * param.num();

				case VAR_INTEGER:
					retval.internal_double *= param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double *= param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

var var::operator /(const var& param)
{
	var retval = this->num();

	switch(retval.type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_STRING:

					return retval / param.num();

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
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_STRING:

					return retval / param.num();

				case VAR_INTEGER:
					retval.internal_double /= param.internal_long;
					retval.type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double /= param.internal_double;
					retval.type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

bool var::operator ==(const var& param)
{
	switch(type)
	{
		case VAR_BOOLEAN:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_bool == param.internal_bool;

				case VAR_INTEGER:
					return internal_bool == param.internal_long;

				case VAR_FLOAT:
					return internal_bool == param.internal_double;

				case VAR_NULL:
					return internal_bool == 0;
			}
			break;

		case VAR_STRING:
			switch(param.type)
			{
				case VAR_STRING:
					return internal_string == param.internal_string ;

				case VAR_INTEGER:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 == param.internal_long;

					return c_double() == param.internal_long;

				case VAR_FLOAT:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 == param.internal_double;

					return c_double() == param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_long == param.internal_bool;

				case VAR_INTEGER:
					return internal_long == param.internal_long;

				case VAR_FLOAT:
					return internal_long == param.internal_double;

				case VAR_STRING:
					for(unsigned i = 0; i < param.internal_string.length(); i++)
						if( (param.internal_string[i] < '0' || param.internal_string[i] > '9') && param.internal_string[i] != '.')
							return internal_long == 0;

					return internal_long == param.c_double();

				case VAR_NULL:
					return internal_long == 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_double == param.internal_bool;

				case VAR_INTEGER:
					return internal_double == param.internal_long;

				case VAR_FLOAT:
					return internal_double == param.internal_double;

				case VAR_STRING:
					for(unsigned i = 0; i < param.internal_string.length(); i++)
						if( (param.internal_string[i] < '0' || param.internal_string[i] > '9') && param.internal_string[i] != '.')
							return internal_double == 0;

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
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return 0 == param.internal_bool;

				case VAR_INTEGER:
					return 0 == param.internal_long;

				case VAR_FLOAT:
					return 0 == param.internal_double;

				case VAR_STRING:
					return false;

				case VAR_NULL:
					return true;
			}
			break;
	}

	return false;
}

bool var::operator <(const var& param)
{
	switch(type)
	{
		case VAR_BOOLEAN:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_bool < param.internal_bool;

				case VAR_INTEGER:
					return internal_bool < param.internal_long;

				case VAR_FLOAT:
					return internal_bool < param.internal_double;

				case VAR_NULL:
					return internal_bool < 0;

			}
			break;

		case VAR_STRING:
			switch(param.type)
			{
				case VAR_STRING:
					return internal_string < param.internal_string ;

				case VAR_INTEGER:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 < param.internal_long;

					return c_double() < param.internal_long;

				case VAR_FLOAT:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 < param.internal_double;

					return c_double() < param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_long < param.internal_bool;

				case VAR_INTEGER:
					return internal_long < param.internal_long;

				case VAR_FLOAT:
					return internal_long < param.internal_double;

				case VAR_STRING:
					for(unsigned i = 0; i < param.internal_string.length(); i++)
						if( (param.internal_string[i] < '0' || param.internal_string[i] > '9') && param.internal_string[i] != '.')
							return internal_long < 0;

					return internal_long < param.c_double();

				case VAR_NULL:
					return internal_long < 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_double < param.internal_bool;

				case VAR_INTEGER:
					return internal_double < param.internal_long;

				case VAR_FLOAT:
					return internal_double < param.internal_double;

				case VAR_STRING:
					for(unsigned i = 0; i < param.internal_string.length(); i++)
						if( (param.internal_string[i] < '0' || param.internal_string[i] > '9') && param.internal_string[i] != '.')
							return internal_double < 0;

					return internal_double < param.c_double();

				case VAR_NULL:
					return internal_double < 0;
			}
			break;

		case VAR_NULL:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return 0 < param.internal_bool;

				case VAR_INTEGER:
					return 0 < param.internal_long;

				case VAR_FLOAT:
					return 0 < param.internal_double;

				case VAR_NULL:
					return false;
			}
			break;

		case VAR_RESOURCE:
				return false;
	}

	return false;
}

bool var::operator >(const var& param)
{
	switch(type)
	{
		case VAR_BOOLEAN:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_bool > param.internal_bool;

				case VAR_INTEGER:
					return internal_bool > param.internal_long;

				case VAR_FLOAT:
					return internal_bool > param.internal_double;

				case VAR_NULL:
					return internal_bool > 0;
			}
			break;

		case VAR_STRING:
			switch(param.type)
			{
				case VAR_STRING:
					return internal_string > param.internal_string ;

				case VAR_INTEGER:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 > param.internal_long;

					return c_double() > param.internal_long;

				case VAR_FLOAT:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 > internal_double;

					return c_double() > param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_long > param.internal_bool;

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
				case VAR_BOOLEAN:
					return internal_double > param.internal_bool;
				case VAR_INTEGER:
					return internal_double > param.internal_long;

				case VAR_FLOAT:
					return internal_double > param.internal_double;

				case VAR_STRING:
					return internal_double > param.c_double();

				case VAR_NULL:
					return internal_double > 0;
			}
			break;

		case VAR_NULL:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return 0 > param.internal_bool;

				case VAR_INTEGER:
					return 0 > param.internal_long;

				case VAR_FLOAT:
					return 0 > param.internal_double;

				case VAR_NULL:
					return false;
			}
			break;

		case VAR_RESOURCE:
			return false;
	}

	return false;
}

bool var::operator &&(const var& param)
{
	switch(type)
	{
		case VAR_BOOLEAN:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_bool && param.internal_bool;

				case VAR_INTEGER:
					return internal_bool && param.internal_long;

				case VAR_FLOAT:
					return internal_bool && param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_long && param.internal_bool;

				case VAR_INTEGER:
					return internal_long && param.internal_long;

				case VAR_FLOAT:
					return internal_long && param.internal_double;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_double && param.internal_long;

				case VAR_INTEGER:
					return internal_double && param.internal_long;

				case VAR_FLOAT:
					return internal_double && param.internal_double;
			}
			break;
	}

	return false;
}

bool var::operator ||(const var& param)
{
	switch(type)
	{
		case VAR_BOOLEAN:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_bool || param.internal_bool;

				case VAR_INTEGER:
					return internal_bool || param.internal_long;

				case VAR_FLOAT:
					return internal_bool || param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_long || param.internal_bool;

				case VAR_INTEGER:
					return internal_long || param.internal_long;

				case VAR_FLOAT:
					return internal_long || param.internal_double;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_BOOLEAN:
					return internal_double || param.internal_long;

				case VAR_INTEGER:
					return internal_double || param.internal_long;

				case VAR_FLOAT:
					return internal_double || param.internal_double;
			}
			break;
	}

	return false;
}

long var::operator &(const var& param)
{
	switch(type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_long & param.internal_long;

				case VAR_FLOAT:
					return internal_long & (long)param.internal_double;
			}
			break;

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_INTEGER:
					return (long)internal_double & param.internal_long;

				case VAR_FLOAT:
					return (long)internal_double & (long)param.internal_double;
			}
			break;
	}

	return false;
}

long var::operator |(const var& param)
{
	switch(type)
	{
		case VAR_INTEGER:
			switch(param.type)
			{
				case VAR_INTEGER:
					return internal_long | param.internal_long;

				case VAR_FLOAT:
					return internal_long | (long)param.internal_double;
			}

		case VAR_FLOAT:
			switch(param.type)
			{
				case VAR_INTEGER:
					return (long)internal_double | param.internal_long;

				case VAR_FLOAT:
					return (long)internal_double | (long)param.internal_double;
			}
	}

	return false;
}

var& var::operator[](const var& param)
{
	if(type != VAR_MAP) {
		reset();
		type = VAR_MAP;
	}

	internal_map_type::iterator iterador;
	for(iterador = internal_map.begin(); iterador != internal_map.end(); iterador++)
		if(iterador->first == param)
			return (var&)(iterador->second);

	internal_map.push_back(pair<var,var>(param,var()));

	return (var&)(operator[](param));
}

var& var::operator <<(const var& param)
{
	if(type != VAR_MAP){
		reset();
		type = VAR_MAP;
	}

	int last = 0;
	internal_map_type::iterator it;
	for(it = internal_map.begin(); it != internal_map.end(); it++)
		last = ( (it->first) > last || ((it->first) == last && ( !((it->first) == 0) || (it->first).type == VAR_INTEGER || (it->first).type == VAR_FLOAT))) ? (it->first).c_long() + 1 : last;

	internal_map.push_back(pair<var,var>(var(last), param));
	return (var&)(operator[](last));
}

var var::num() const
{
	var retval;
	switch(type)
	{
		case VAR_STRING:
			retval.internal_double = atof(internal_string.c_str());
			retval.internal_long = (long)retval.internal_double;
			retval.type = (retval.internal_double == retval.internal_long) ? VAR_INTEGER : VAR_FLOAT;
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

long var::c_long() const
{
	switch(type)
	{
		case VAR_BOOLEAN:
			return internal_bool ? 1 : 0;

		case VAR_STRING:
			return (long)atof(internal_string.c_str());

		case VAR_INTEGER:
			return internal_long;

		case VAR_FLOAT:
			return (long)internal_double;

	}

	return 0;
}

double var::c_double() const
{
	switch(type)
	{
		case VAR_BOOLEAN:
			return internal_bool ? 1 : 0;

		case VAR_STRING:
			return atof(internal_string.c_str());

		case VAR_INTEGER:
			return (double)internal_long;

		case VAR_FLOAT:
			return internal_double;
	}

	return 0;
}

string var::cpp_string() const
{
	string retval;
	char* buffer = (char*) malloc(32);

	switch(type)
	{
		case VAR_BOOLEAN:
			return internal_bool ? "true" : "false";

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
