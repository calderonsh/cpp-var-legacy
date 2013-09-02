#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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

var::var(const std::string& param)
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
	var result = *this;

	switch(result.internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					result.internal_bool = internal_bool || param.internal_bool;
					result.internal_type = VAR_BOOLEAN;

					return result;

				case VAR_INTEGER:
					result.internal_bool = internal_bool || param.internal_long;
					result.internal_type = VAR_BOOLEAN;

					return result;

				case VAR_FLOAT:
					result.internal_bool = internal_bool || param.internal_double;
					result.internal_type = VAR_BOOLEAN;

					return result;
			}
			break;

		case VAR_STRING:
			switch(param.internal_type)
			{
				case VAR_STRING:
					result.internal_string += param.internal_string;
					result.internal_type = VAR_STRING;

					return result;

				case VAR_INTEGER:
					result.internal_string += param.cpp_string();
					result.internal_type = VAR_STRING;

					return result;

				case VAR_FLOAT:
					result.internal_string += param.cpp_string();
					result.internal_type = VAR_STRING;

					return result;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result + param.num();

				case VAR_INTEGER:
					result.internal_long += param.internal_long;
					result.internal_type = VAR_INTEGER;

					return result;

				case VAR_FLOAT:
					result.internal_double = result.internal_long + param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result + param.num();

				case VAR_INTEGER:
					result.internal_double += param.internal_long;
					result.internal_type = VAR_FLOAT;

					return result;

				case VAR_FLOAT:
					result.internal_double += param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;
	}

	return result;
}

var var::operator -(const var& param)
{
	var result = this->num();

	switch(result.internal_type)
	{
		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result - param.num();

				case VAR_INTEGER:
					result.internal_long -= param.internal_long;
					result.internal_type = VAR_INTEGER;

					return result;

				case VAR_FLOAT:
					result.internal_double = result.internal_long - param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result - param.num();

				case VAR_INTEGER:
					result.internal_double -= param.internal_long;
					result.internal_type = VAR_FLOAT;

					return result;

				case VAR_FLOAT:
					result.internal_double -= param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;
	}

	return result;
}

var var::operator *(const var& param)
{
	var result = *this;

	switch(result.internal_type)
	{
		case VAR_BOOLEAN:
			switch(param.internal_type)
			{
				case VAR_BOOLEAN:
					result.internal_bool = internal_bool && param.internal_bool;
					result.internal_type = VAR_BOOLEAN;

					return result;

				case VAR_INTEGER:
					result.internal_bool = internal_bool && param.internal_long;
					result.internal_type = VAR_BOOLEAN;

					return result;

				case VAR_FLOAT:
					result.internal_bool = internal_bool && param.internal_double;
					result.internal_type = VAR_BOOLEAN;

					return result;
			}
			break;

		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result * param.num();

				case VAR_INTEGER:
					result.internal_long *= param.internal_long;
					result.internal_type = VAR_INTEGER;

					return result;

				case VAR_FLOAT:
					result.internal_double = result.internal_long * param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result * param.num();

				case VAR_INTEGER:
					result.internal_double *= param.internal_long;
					result.internal_type = VAR_FLOAT;

					return result;

				case VAR_FLOAT:
					result.internal_double *= param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;
	}

	return result;
}

var var::operator /(const var& param)
{
	var result = this->num();

	switch(result.internal_type)
	{
		case VAR_INTEGER:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result / param.num();

				case VAR_INTEGER:
					result.internal_double = (double)result.internal_long / param.internal_long;
					result.internal_long = (long)result.internal_double;
					result.internal_type = result.internal_double == result.internal_long ? VAR_INTEGER : VAR_FLOAT;

					return result;

				case VAR_FLOAT:
					result.internal_double = result.internal_long / param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;

		case VAR_FLOAT:
			switch(param.internal_type)
			{
				case VAR_STRING:

					return result / param.num();

				case VAR_INTEGER:
					result.internal_double /= param.internal_long;
					result.internal_type = VAR_FLOAT;

					return result;

				case VAR_FLOAT:
					result.internal_double /= param.internal_double;
					result.internal_type = VAR_FLOAT;

					return result;
			}
			break;
	}

	return result;
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

var& var::operator [](const var& param)
{
	if (internal_type != VAR_MAP && internal_type != VAR_VECTOR)
	{
		this->clear();
		internal_type = VAR_MAP;
	}

	if (internal_type == VAR_VECTOR)
	{
		if (param.internal_type == VAR_INTEGER)
		{
			long i = param;

			if (i < 0) {
				i += internal_vector.size() * (ceil(fabs(i)/(float)internal_vector.size()));
			}

			if (internal_vector.size() < (unsigned int)i) {
				internal_vector.resize(i + 1);
			}

			return (var&)internal_vector[i];
		}
		else
		{
			for (unsigned i = 0; i < internal_vector.size(); i++)
			{
				internal_map.push_back(std::pair<var,var>(i, internal_vector[i]));
				internal_vector[i].clear();
			}

			internal_vector.clear();

			internal_type = VAR_MAP;
		}
	}

	internal_map_type::iterator iterador;
	for (iterador = internal_map.begin(); iterador != internal_map.end(); iterador++)
	{
		if((iterador->first).compare(param))
		{
			internal_map_iterator = internal_map.end();
			return (var&)(iterador->second);
		}
	}

	internal_map.push_back(std::pair<var,var>(param,var()));

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

	var last = 0;

	for (internal_map_iterator = internal_map.begin(); internal_map_iterator != internal_map.end(); internal_map_iterator++)
	{
		if (internal_map_iterator->first.num().compare(last) ) {
			last = (last > internal_map_iterator->first.num() ? last : internal_map_iterator->first.num() ) + 1;
		}
	}

	internal_map.push_back(std::pair<var,var>(var(last), param));
	return (var&)(operator[](var(last)));
}

bool var::compare(const var& param)
{
	if (this->internal_type != param.internal_type) {
		return false;
	}

	return (*this == param);
}

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
	var result;

	switch(internal_type)
	{
		case VAR_MAP:
			result.internal_map_iterator = internal_map.begin();
			result.internal_type = VAR_MAP_ITERATOR;
			return result;

		case VAR_VECTOR:
			result.internal_long = 0;
			result.internal_vector_iterator =  internal_vector.begin();
			result.internal_type = VAR_VECTOR_ITERATOR;
			return result;
	}

	return 0;
}

var var::end()
{
	var result;

	switch(internal_type)
	{
		case VAR_MAP:
			result.internal_map_iterator =  internal_map.end();
			result.internal_type = VAR_MAP_ITERATOR;
			return result;

		case VAR_VECTOR:
			result.internal_long = internal_vector.size();
			result.internal_vector_iterator =  internal_vector.end();
			result.internal_type = VAR_VECTOR_ITERATOR;
			return result;
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
	var result;
	switch(internal_type)
	{
		case VAR_STRING:
			result.internal_double = atof(internal_string.c_str());
			result.internal_long = (long)result.internal_double;
			result.internal_type = (result.internal_double == result.internal_long) ? VAR_INTEGER : VAR_FLOAT;
			break;

		case VAR_INTEGER:
			result.internal_long = internal_long;
			result.internal_type = VAR_INTEGER;
			break;

		case VAR_FLOAT:
			result.internal_double = internal_double;
			result.internal_type = VAR_FLOAT;
			break;

		case VAR_NULL:
			result.internal_long = 0;
			result.internal_type = VAR_INTEGER;
			break;
	}

	return result;
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

		case VAR_MAP:
			return !internal_map.empty();

		case VAR_VECTOR:
			return !internal_vector.empty();

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

std::string var::cpp_string() const
{
	std::string result;
	char* buffer;

	switch(internal_type)
	{
		case VAR_NULL:
			return "";

		case VAR_BOOLEAN:
			return internal_bool ? "true" : "false";

		case VAR_STRING:
			return  internal_string;

		case VAR_INTEGER:
			buffer = (char*) malloc(32);
			sprintf(buffer,"%ld", internal_long);
			break;

		case VAR_FLOAT:
			buffer = (char*) malloc(32);
			sprintf(buffer,"%f", internal_double);
			break;

		default:
			buffer = (char*) malloc(32);
			sprintf(buffer,"0");
	}

	result = buffer;
	free(buffer);

	return result;
}

var::operator const char*() const
{
	return this->cpp_string().c_str();
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
	std::string result;
	char* buffer;
	unsigned int pos = 0;

	switch(internal_type)
	{
		case VAR_NULL:
			return "null";

		case VAR_BOOLEAN:
		case VAR_INTEGER:
		case VAR_FLOAT:
			return this->cpp_string();

		case VAR_STRING:
			result = internal_string;


			while((pos = result.find("\"", pos)) != std::string::npos)
			{
				result.replace(pos, 1, "\\\"");
				pos += 4;
			}

			return "\"" + result + "\"";

		case VAR_MAP:
			result = "{";

			for(internal_map_type::iterator it = internal_map.begin(); it != internal_map.end(); it++) {
				result += (it)->first.encode() + ":" + (it)->second.encode() + ",";
			}

			result[result.size()-1] = '}';

			return result;

		case VAR_VECTOR:
			result = "[";

			for(unsigned i = 0; i < internal_vector.size(); i++) {
				result += internal_vector[i].encode() + ",";
			}

			result[result.size()-1] = ']';

			return result;

		default:
			buffer = (char*) malloc(32);
			sprintf(buffer,"0");
	}

	result = buffer;
	free(buffer);

	return result;
}

int var::decode(std::string data) //TODO
{
	return 1;
}

var var:: operator +(const int& a) { return operator +(var(a)); }
var var:: operator +(const char* a) { return operator +(var(a)); }
bool var:: operator ==(const bool& a) { return operator ==(var(a)); }
bool var:: operator ==(const int& a) { return operator ==(var(a)); }
bool var:: operator ==(const float& a) { return operator ==(var(a)); }
bool var:: operator ==(const double& a) { return operator ==(var(a)); }
bool var:: operator ==(const char* a) { return operator ==(var(a)); }
bool var:: operator !=(const int& a) { return operator !=(var(a)); }
bool var:: operator !=(const char* a) { return operator !=(var(a)); }
bool var:: operator <(unsigned int a) { return operator <(var(a));}
var& var:: operator [](const int& a) { return operator[](var(a)); }
var& var:: operator [](const char* a) { return operator[](var(a)); }

var operator+(char* a, var b) {return var(a) + b;}
var operator+(const char* a, var b) {return var(a) + b;}
var::operator int() const { return operator long(); }

int var_type(const var& param) {
	return param.internal_type;
}
