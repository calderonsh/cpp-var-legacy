#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "var.hpp"

var::var() {
	internal_type = VAR_NULL;
}

var::var(const bool& param)
{
	internal_bool = param;
	internal_type = VAR_BOOLEAN;
}

var::var(const int& param)
{
	internal_long = param;
	internal_type = VAR_INTEGER;
}

var::var(const unsigned int& param)
{
	internal_long = param;
	internal_type = VAR_INTEGER;
}

var::var(const long& param)
{
	internal_long = param;
	internal_type = VAR_INTEGER;
}

var::var(const double& param)
{
	internal_double = param;
	internal_type = VAR_FLOAT;
}

var::var(const char* param)
{
	internal_string = param;
	internal_type = VAR_STRING;
}

var::var(const string& param)
{
	internal_string = param;
	internal_type = VAR_STRING;
}

var::var(void* param)
{
	internal_resource = param;
	internal_type = VAR_RESOURCE;
}

void var::clear()
{
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			internal_bool = false;
			break;

		case VAR_STRING:
			internal_string.clear();
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

		case VAR_VECTOR:
			internal_vector.clear();
			break;

		case VAR_VECTOR_ITERATOR:
			internal_long = 0;
			break;

		case VAR_RESOURCE:
			internal_resource = NULL;
			break;
	}

	internal_type = VAR_NULL;
}

var var::operator =(const var& param)
{
	this->clear();

	switch(param.internal_type)
	{
		case VAR_BOOLEAN:
			internal_bool = param.internal_bool;
			internal_type = VAR_BOOLEAN;

			break;

		case VAR_STRING:
			internal_string = param.internal_string;
			internal_type = VAR_STRING;

			break;

		case VAR_INTEGER:
			internal_long = param.internal_long;
			internal_type = VAR_INTEGER;

			break;

		case VAR_FLOAT:
			internal_double = param.internal_double;
			internal_type = VAR_FLOAT;

			break;

		case VAR_MAP:
			internal_map = param.internal_map;
			internal_type = VAR_MAP;

			break;

		case VAR_MAP_ITERATOR:
			internal_map_iterator = param.internal_map_iterator;
			internal_type = VAR_MAP_ITERATOR;

			break;

		case VAR_VECTOR:
			internal_vector = param.internal_vector;
			internal_type = VAR_VECTOR;

			break;

		case VAR_VECTOR_ITERATOR:
			internal_vector_iterator = param.internal_vector_iterator;
			internal_type = VAR_VECTOR_ITERATOR;

			break;

		case VAR_RESOURCE:
			internal_resource = param.internal_resource;
			internal_type = VAR_RESOURCE;

			break;

		case VAR_NULL:
			internal_type=VAR_NULL;

	}

	return param;
}

var var::operator +(const var& param)
{
	var retval = *this;

	switch(retval.internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					retval.internal_bool = internal_bool || param.internal_bool;
					retval.internal_type = VAR_BOOLEAN;

					return retval;

				case VAR_INTEGER:
					retval.internal_bool = internal_bool || param.internal_long;
					retval.internal_type = VAR_BOOLEAN;

					return retval;

				case VAR_FLOAT:
					retval.internal_bool = internal_bool || param.internal_double;
					retval.internal_type = VAR_BOOLEAN;

					return retval;
			}
			break;

		case VAR_STRING:
			switch(param.internal_type)
			{
				case VAR_STRING:
					retval.internal_string += param.internal_string;
					retval.internal_type = VAR_STRING;

					return retval;

				case VAR_INTEGER:
					retval.internal_string += param.cpp_string();
					retval.internal_type = VAR_STRING;

					return retval;

				case VAR_FLOAT:
					retval.internal_string += param.cpp_string();
					retval.internal_type = VAR_STRING;

					return retval;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval + param.num();

				case VAR_INTEGER:
					retval.internal_long += param.internal_long;
					retval.internal_type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long + param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval + param.num();

				case VAR_INTEGER:
					retval.internal_double += param.internal_long;
					retval.internal_type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double += param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

var var::operator -(const var& param)
{
	var retval = this->num();

	switch(retval.internal_type)
	{
		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval - param.num();

				case VAR_INTEGER:
					retval.internal_long -= param.internal_long;
					retval.internal_type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long - param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval - param.num();

				case VAR_INTEGER:
					retval.internal_double -= param.internal_long;
					retval.internal_type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double -= param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

var var::operator *(const var& param)
{
	var retval = *this;

	switch(retval.internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					retval.internal_bool = internal_bool && param.internal_bool;
					retval.internal_type = VAR_BOOLEAN;

					return retval;

				case VAR_INTEGER:
					retval.internal_bool = internal_bool && param.internal_long;
					retval.internal_type = VAR_BOOLEAN;

					return retval;

				case VAR_FLOAT:
					retval.internal_bool = internal_bool && param.internal_double;
					retval.internal_type = VAR_BOOLEAN;

					return retval;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval * param.num();

				case VAR_INTEGER:
					retval.internal_long *= param.internal_long;
					retval.internal_type = VAR_INTEGER;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long * param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval * param.num();

				case VAR_INTEGER:
					retval.internal_double *= param.internal_long;
					retval.internal_type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double *= param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

var var::operator /(const var& param)
{
	var retval = this->num();

	switch(retval.internal_type)
	{
		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval / param.num();

				case VAR_INTEGER:
					retval.internal_double = (double)retval.internal_long / param.internal_long;
					retval.internal_long = (long)retval.internal_double;
					retval.internal_type = retval.internal_double == retval.internal_long ? VAR_INTEGER : VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double = retval.internal_long / param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return retval / param.num();

				case VAR_INTEGER:
					retval.internal_double /= param.internal_long;
					retval.internal_type = VAR_FLOAT;

					return retval;

				case VAR_FLOAT:
					retval.internal_double /= param.internal_double;
					retval.internal_type = VAR_FLOAT;

					return retval;
			}
			break;
	}

	return retval;
}

var var::operator ++(int)
{
	switch(internal_type)
	{
		case VAR_INTEGER:
			internal_long++;
			break;

		case VAR_FLOAT:
			internal_double++;
			break;

		case VAR_MAP_ITERATOR:
			internal_map_iterator++;
			break;

		case VAR_VECTOR_ITERATOR:
			internal_long++;
			internal_vector_iterator++;
			break;
	}

	return *this;
}

var var::operator --(int)
{
	switch(internal_type)
	{
		case VAR_INTEGER:
			internal_long--;
			break;

		case VAR_FLOAT:
			internal_double--;
			break;

		case VAR_MAP_ITERATOR:
			internal_map_iterator--;
			break;

		case VAR_VECTOR_ITERATOR:
			internal_vector_iterator--;
			break;
	}

	return *this;
}

bool var::operator ==(const var& param)
{
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
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
			switch(param.internal_type)
			{
				case VAR_STRING:
					return internal_string == param.internal_string ;

				case VAR_INTEGER:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 == param.internal_long;

					return operator double() == param.internal_long;

				case VAR_FLOAT:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 == param.internal_double;

					return operator double() == param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
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

					return internal_long == (double)param;

				case VAR_NULL:
					return internal_long == 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
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

					return internal_double == (double)param;

				case VAR_NULL:
					return internal_double == 0;
			}
			break;

		case VAR_RESOURCE:
			if(param.internal_type == VAR_RESOURCE && internal_resource == param.internal_resource)
				return true;
			break;

		case VAR_NULL:
			switch(param.internal_type)
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

bool var::operator !=(const var& param)
{
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					return internal_bool != param.internal_bool;

				case VAR_INTEGER:
					return internal_bool != param.internal_long;

				case VAR_FLOAT:
					return internal_bool != param.internal_double;

				case VAR_NULL:
					return internal_bool != 0;
			}
			break;

		case VAR_STRING:
			switch(param.internal_type)
			{
				case VAR_STRING:
					return internal_string != param.internal_string ;

				case VAR_INTEGER:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 != param.internal_long;

					return operator double() != param.internal_long;

				case VAR_FLOAT:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 != param.internal_double;

					return operator double() != param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					return internal_long != param.internal_bool;

				case VAR_INTEGER:
					return internal_long != param.internal_long;

				case VAR_FLOAT:
					return internal_long != param.internal_double;

				case VAR_STRING:
					for(unsigned i = 0; i < param.internal_string.length(); i++)
						if( (param.internal_string[i] < '0' || param.internal_string[i] > '9') && param.internal_string[i] != '.')
							return internal_long != 0;

					return internal_long != (double)param;

				case VAR_NULL:
					return internal_long != 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					return internal_double != param.internal_bool;

				case VAR_INTEGER:
					return internal_double != param.internal_long;

				case VAR_FLOAT:
					return internal_double != param.internal_double;

				case VAR_STRING:
					for(unsigned i = 0; i < param.internal_string.length(); i++)
						if( (param.internal_string[i] < '0' || param.internal_string[i] > '9') && param.internal_string[i] != '.')
							return internal_double != 0;

					return internal_double != (double)param;

				case VAR_NULL:
					return internal_double != 0;
			}
			break;

		case VAR_MAP_ITERATOR:
			switch(param.internal_type)
			{
				case VAR_MAP_ITERATOR:
					return internal_map_iterator != param.internal_map_iterator;
			}
			break;

		case VAR_VECTOR_ITERATOR:
			switch(param.internal_type)
			{
				case VAR_VECTOR_ITERATOR:
					return internal_vector_iterator != param.internal_vector_iterator;
			}
			break;

		case VAR_RESOURCE:
			if(param.internal_type == VAR_RESOURCE && internal_resource != param.internal_resource)
				return true;
			break;

		case VAR_NULL:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					return 0 != param.internal_bool;

				case VAR_INTEGER:
					return 0 != param.internal_long;

				case VAR_FLOAT:
					return 0 != param.internal_double;

				case VAR_STRING:
					return true;

				case VAR_NULL:
					return false;
			}
			break;
	}

	return true;
}

bool var::operator <(const var& param)
{
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
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
			switch(param.internal_type)
			{
				case VAR_STRING:
					return internal_string < param.internal_string ;

				case VAR_INTEGER:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 < param.internal_long;

					return operator double() < param.internal_long;

				case VAR_FLOAT:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 < param.internal_double;

					return operator double() < param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
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

					return internal_long < (double)param;

				case VAR_NULL:
					return internal_long < 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
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

					return internal_double < (double)param;

				case VAR_NULL:
					return internal_double < 0;
			}
			break;

		case VAR_NULL:
			switch(param.internal_type)
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
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
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
			switch(param.internal_type)
			{
				case VAR_STRING:
					return internal_string > param.internal_string ;

				case VAR_INTEGER:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 > param.internal_long;

					return operator double() > param.internal_long;

				case VAR_FLOAT:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 > internal_double;

					return operator double() > param.internal_double;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					return internal_long > param.internal_bool;

				case VAR_INTEGER:
					return internal_long > param.internal_long;

				case VAR_FLOAT:
					return internal_long > param.internal_double;

				case VAR_STRING:
					return internal_long > (double)param;

				case VAR_NULL:
					return internal_long > 0;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					return internal_double > param.internal_bool;

				case VAR_INTEGER:
					return internal_double > param.internal_long;

				case VAR_FLOAT:
					return internal_double > param.internal_double;

				case VAR_STRING:
					return internal_double > (double)param;

				case VAR_NULL:
					return internal_double > 0;
			}
			break;

		case VAR_NULL:
			switch(param.internal_type)
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
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
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
			switch(param.internal_type)
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
			switch(param.internal_type)
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
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
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
			switch(param.internal_type)
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
			switch(param.internal_type)
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
	switch(internal_type)
	{
		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_INTEGER:
					return internal_long & param.internal_long;

				case VAR_FLOAT:
					return internal_long & (long)param.internal_double;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
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
	switch(internal_type)
	{
		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_INTEGER:
					return internal_long | param.internal_long;

				case VAR_FLOAT:
					return internal_long | (long)param.internal_double;
			}

		case VAR_FLOAT:
			switch(param.internal_type)
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
	if (internal_type != VAR_MAP && internal_type != VAR_VECTOR)
	{
		this->clear();
		internal_type = VAR_MAP;
	}

	if (internal_type == VAR_VECTOR) {
		return (var&)internal_vector[(long)param];
	}

	internal_map_type::iterator iterador;
	for (iterador = internal_map.begin(); iterador != internal_map.end(); iterador++)
	{
		if(iterador->first == param)
		{
			internal_map_iterator = internal_map.end();
			return (var&)(iterador->second);
		}
	}

	internal_map.push_back(pair<var,var>(param,var()));

	return (var&)(operator[](param));
}


var& var::operator <<(const var& param)
{
	if(internal_type != VAR_VECTOR && internal_type != VAR_MAP)
	{
		this->clear();
		internal_type = VAR_VECTOR;
	}

	if(internal_type == VAR_VECTOR)
	{
		internal_vector.push_back(param);
		return (var&) internal_vector[internal_vector.size()-1];
	}

	int last = 0;

	for(internal_map_iterator = internal_map.begin(); internal_map_iterator != internal_map.end(); internal_map_iterator++)
		if( (internal_map_iterator->first).internal_type == VAR_INTEGER && (internal_map_iterator->first).internal_long >= last)
			last = (internal_map_iterator->first).internal_long + 1;

	internal_map.push_back(pair<var,var>(var(last), param));
	return (var&)(operator[](var(last)));
}

var var:: operator +(const int& a) { return operator +(var(a)); }
var var:: operator +(const char* a) { return operator +(var(a)); }
bool var:: operator ==(const bool& a) { return operator ==(var(a)); }
bool var:: operator ==(const int& a) { return operator ==(var(a)); }
bool var:: operator ==(const float& a) { return operator ==(var(a)); }
bool var:: operator <(unsigned int a) { return operator <(var(a));}
var& var:: operator [](const char* a) { return operator[](var(a)); }

bool var::fetch(var& key, var& value)
{
	switch(internal_type)
	{
		case VAR_MAP:
			if (internal_map_iterator == internal_map.end())
			{
				internal_map_iterator = internal_map.begin();
				key = internal_map_iterator->first;
				value = internal_map_iterator->second;

				return true;
			}
			else
			{
				internal_map_iterator++;

				if (internal_map_iterator == internal_map.end()) {
					return false;
				}

				key = internal_map_iterator->first;
				value = internal_map_iterator->second;
			}
			return true;

		case VAR_VECTOR: //TODO
			if ( (unsigned) internal_long >= internal_vector.size())
			{
				internal_long = 0;
				key = internal_long;
				value = internal_vector[internal_long];

				return true;
			}
			else
			{
				internal_long++;

				if ( (unsigned) internal_long >= internal_vector.size()) {
					return false;
				}
				key = internal_long;
				value = internal_vector[internal_long];
			}
			return true;
	}
	return false;
}

var var::key()
{
	switch(internal_type)
	{
		case VAR_MAP_ITERATOR:
			return (var&) internal_map_iterator->first;

		case VAR_VECTOR_ITERATOR:
			return internal_long;
	}

	return (var&) *this;
}

var& var::operator *()
{
	switch(internal_type)
	{
		case VAR_MAP_ITERATOR:
			return (var&) internal_map_iterator->second;

		case VAR_VECTOR_ITERATOR:
			return (var&) *internal_vector_iterator;

	}

	return (var&) *this;
}

var var::begin()
{
	var retval;

	switch(internal_type)
	{
		case VAR_MAP:
			retval.internal_map_iterator = internal_map.begin();
			retval.internal_type = VAR_MAP_ITERATOR;
			return retval;

		case VAR_VECTOR:
			retval.internal_long = 0;
			retval.internal_vector_iterator =  internal_vector.begin();
			retval.internal_type = VAR_VECTOR_ITERATOR;
			return retval;
	}

	return 0;
}

var var::end()
{
	var retval;

	switch(internal_type)
	{
		case VAR_MAP:
			retval.internal_map_iterator =  internal_map.end();
			retval.internal_type = VAR_MAP_ITERATOR;
			return retval;

		case VAR_VECTOR:
			retval.internal_long = internal_vector.size();
			retval.internal_vector_iterator =  internal_vector.end();
			retval.internal_type = VAR_VECTOR_ITERATOR;
			return retval;
	}

	return 0;
}

long var::size() const
{
	switch(internal_type)
	{
		case VAR_STRING:
			return internal_string.length();

		case VAR_MAP:
			return internal_map.size();

		case VAR_VECTOR:
			return internal_vector.size();
	}

	return 0;
}

var var::num() const
{
	var retval;
	switch(internal_type)
	{
		case VAR_STRING:
			retval.internal_double = atof(internal_string.c_str());
			retval.internal_long = (long)retval.internal_double;
			retval.internal_type = (retval.internal_double == retval.internal_long) ? VAR_INTEGER : VAR_FLOAT;
			break;

		case VAR_INTEGER:
			retval.internal_long = internal_long;
			retval.internal_type = VAR_INTEGER;
			break;

		case VAR_FLOAT:
			retval.internal_double = internal_double;
			retval.internal_type = VAR_FLOAT;
			break;

		case VAR_NULL:
			retval.internal_long = 0;
			retval.internal_type = VAR_INTEGER;
			break;
	}

	return retval;
}

var::operator bool() const
{
	switch(internal_type)
	{
		case VAR_BOOLEAN:
			return internal_bool;

		case VAR_STRING:
			return atof(internal_string.c_str()) ? true : false;

		case VAR_INTEGER:
			return internal_long ? true : false;

		case VAR_FLOAT:
			return internal_double ? true : false;

		case VAR_RESOURCE:
			return internal_resource ? true : false;
	}

	return false;
}

var::operator long() const
{
	switch(internal_type)
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

var::operator double() const
{
	switch(internal_type)
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

	switch(internal_type)
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

var::operator void *() const
{
	if (internal_type == VAR_RESOURCE) {
		return internal_resource;
	} else {
		return NULL;
	}
}

var::internal_map_type& var::cpp_map() {
	return (internal_map_type&) internal_map;
}

var::internal_vector_type& var::cpp_vector() {
	return (internal_vector_type&) internal_vector;
}

std::string var::encode()
{
	string retval;
	char* buffer = (char*) malloc(32);

	switch(internal_type)
	{
		case VAR_BOOLEAN:
			return internal_bool ? "true" : "false";

		case VAR_INTEGER:
			sprintf(buffer,"%li", internal_long);
			break;

		case VAR_FLOAT:
			sprintf(buffer,"%f", internal_double);
			break;

		case VAR_STRING:
			return "\"" + internal_string + "\"";

		case VAR_MAP:
			retval = "{";

			for(internal_map_type::iterator it = internal_map.begin(); it != internal_map.end(); it++) {
				retval += (it)->first.encode() + ":" + (it)->second.encode() + ",";
			}

			retval[retval.size()-1] = '}';

			return retval;

		case VAR_VECTOR:
			retval = "[";

			for(unsigned i = 0; i < internal_vector.size(); i++) {
				retval += internal_vector[i].encode() + ",";
			}

			retval[retval.size()-1] = ']';

			return retval;

		case VAR_RESOURCE: //TODO
			sprintf(buffer,"0");
			break;

		default:
			sprintf(buffer,"0");
	}

	retval = buffer;
	free(buffer);

	return retval;
}

int var::decode(std::string data) //TODO
{
	return 1;
}

int var_type(const var& param) {
	return param.internal_type;
}
