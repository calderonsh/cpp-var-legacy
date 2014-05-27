#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "var.hpp"


var::var() {
	internal_type = var::null;
}

var::var(bool that)
{
	this->internal_bool = that;
	this->internal_type = var::boolean;
}

var::var(int that)
{
	this->internal_long = that;
	this->internal_type = var::integer;
}

var::var(var_t that)
{
	this->internal_type = that;
}

var::var(unsigned int that)
{
	this->internal_long = that;
	this->internal_type = var::integer;
}

var::var(long that)
{
	this->internal_long = that;
	this->internal_type = var::integer;
}

var::var(double that)
{
	this->internal_double = that;
	this->internal_type = var::real;
}

var::var(const char* that)
{
	this->internal_string = that;
	this->internal_type = var::string;
}

var::var(const std::string& that)
{
	this->internal_string = that;
	this->internal_type = var::string;
}

var::var(void* that)
{
	this->internal_resource = that;
	this->internal_type = var::string;
}

void var::clear()
{
	switch(this->internal_type)
	{
		case var::boolean:
			this->internal_bool = false;
			break;

		case var::string:
			this->internal_string.clear();
			break;

		case var::integer:
			this->internal_long = 0;
			break;

		case var::real:
			this->internal_double = 0;
			break;

		case var::map:
			this->internal_map.clear();
			break;

		case var::vector:
			this->internal_vector.clear();
			break;

		case var::vector_iterator:
			this->internal_long = 0;
			break;

		case var::resource:
			this->internal_resource = NULL;
			break;
	}

	this->internal_type = var::null;
}

var var::operator =(const var& that)
{
	this->clear();

	switch(that.internal_type)
	{
		case var::boolean:
			this->internal_bool = that.internal_bool;
			this->internal_type = var::boolean;

			break;

		case var::string:
			this->internal_string = that.internal_string;
			this->internal_type = var::string;

			break;

		case var::integer:
			this->internal_long = that.internal_long;
			this->internal_type = var::integer;

			break;

		case var::real:
			this->internal_double = that.internal_double;
			this->internal_type = var::real;

			break;

		case var::map:
			this->internal_map = that.internal_map;
			this->internal_type = var::map;

			break;

		case var::map_iterator:
			this->internal_map_iterator = that.internal_map_iterator;
			this->internal_type = var::map_iterator;

			break;

		case var::vector:
			this->internal_vector = that.internal_vector;
			this->internal_type = var::vector;

			break;

		case var::vector_iterator:
			this->internal_vector_iterator = that.internal_vector_iterator;
			this->internal_type = var::vector_iterator;

			break;

		case var::resource:
			this->internal_resource = that.internal_resource;
			this->internal_type = var::resource;

			break;

		case var::null:
			this->internal_type=var::null;
	}

	return that;
}

var var::operator +(const var& that) const
{
	var result = *this;

	switch(result.internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					result.internal_bool = internal_bool || that.internal_bool;
					result.internal_type = var::boolean;

					return result;

				case var::integer:
					result.internal_bool = internal_bool || that.internal_long;
					result.internal_type = var::boolean;

					return result;

				case var::real:
					result.internal_bool = internal_bool || that.internal_double;
					result.internal_type = var::boolean;

					return result;
			}
			break;

		case var::string:
			switch(that.internal_type)
			{
				case var::string:
					result.internal_string += that.internal_string;
					result.internal_type = var::string;

					return result;

				case var::integer:
					result.internal_string += (const char*)that;
					result.internal_type = var::string;

					return result;

				case var::real:
					result.internal_string += (const char*)that;
					result.internal_type = var::string;

					return result;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::string:

					return result + that.num();

				case var::integer:
					result.internal_long += that.internal_long;
					result.internal_type = var::integer;

					return result;

				case var::real:
					result.internal_double = result.internal_long + that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::string:

					return result + that.num();

				case var::integer:
					result.internal_double += that.internal_long;
					result.internal_type = var::real;

					return result;

				case var::real:
					result.internal_double += that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;
	}

	return result;
}

var var::operator -(const var& that) const
{
	var result = this->num();

	switch(result.internal_type)
	{
		case var::integer:
			switch(that.internal_type)
			{
				case var::string:

					return result - that.num();

				case var::integer:
					result.internal_long -= that.internal_long;
					result.internal_type = var::integer;

					return result;

				case var::real:
					result.internal_double = result.internal_long - that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::string:

					return result - that.num();

				case var::integer:
					result.internal_double -= that.internal_long;
					result.internal_type = var::real;

					return result;

				case var::real:
					result.internal_double -= that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;
	}

	return result;
}

var var::operator *(const var& that) const
{
	var result = *this;

	switch(result.internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					result.internal_bool = internal_bool && that.internal_bool;
					result.internal_type = var::boolean;

					return result;

				case var::integer:
					result.internal_bool = internal_bool && that.internal_long;
					result.internal_type = var::boolean;

					return result;

				case var::real:
					result.internal_bool = internal_bool && that.internal_double;
					result.internal_type = var::boolean;

					return result;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::string:

					return result * that.num();

				case var::integer:
					result.internal_long *= that.internal_long;
					result.internal_type = var::integer;

					return result;

				case var::real:
					result.internal_double = result.internal_long * that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::string:

					return result * that.num();

				case var::integer:
					result.internal_double *= that.internal_long;
					result.internal_type = var::real;

					return result;

				case var::real:
					result.internal_double *= that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;
	}

	return result;
}

var var::operator /(const var& that) const
{
	var result = this->num();

	switch(result.internal_type)
	{
		case var::integer:
			switch(that.internal_type)
			{
				case var::string:

					return result / that.num();

				case var::integer:
					result.internal_double = (double)result.internal_long / that.internal_long;
					result.internal_long = (long)result.internal_double;
					result.internal_type = result.internal_double == result.internal_long ? var::integer : var::real;

					return result;

				case var::real:
					result.internal_double = result.internal_long / that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::string:

					return result / that.num();

				case var::integer:
					result.internal_double /= that.internal_long;
					result.internal_type = var::real;

					return result;

				case var::real:
					result.internal_double /= that.internal_double;
					result.internal_type = var::real;

					return result;
			}
			break;
	}

	return result;
}

var var::operator ++(int)
{
	switch(this->internal_type)
	{
		case var::integer:
			this->internal_long++;
			break;

		case var::real:
			this->internal_double++;
			break;

		case var::map_iterator:
			this->internal_map_iterator++;
			break;

		case var::vector_iterator:
			this->internal_long++;
			this->internal_vector_iterator++;
			break;
	}

	return *this;
}

var var::operator --(int)
{
	switch(internal_type)
	{
		case var::integer:
			this->internal_long--;
			break;

		case var::real:
			this->internal_double--;
			break;

		case var::map_iterator:
			this->internal_map_iterator--;
			break;

		case var::vector_iterator:
			this->internal_vector_iterator--;
			break;
	}

	return *this;
}

bool var::operator ==(const var& that) const
{
	switch(internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					return this->internal_bool == that.internal_bool;

				case var::integer:
					return this->internal_bool == that.internal_long;

				case var::real:
					return this->internal_bool == that.internal_double;

				case var::null:
					return this->internal_bool == 0;
			}
			break;

		case var::string:
			switch(that.internal_type)
			{
				case var::string:
					return this->internal_string == that.internal_string ;

				case var::integer:
					for(unsigned i = 0; i < this->internal_string.length(); i++)
						if( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 == that.internal_long;

					return operator double() == that.internal_long;

				case var::real:
					for(unsigned i = 0; i < this->internal_string.length(); i++)
						if( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 == that.internal_double;

					return operator double() == that.internal_double;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::boolean:
					return this->internal_long == that.internal_bool;

				case var::integer:
					return this->internal_long == that.internal_long;

				case var::real:
					return this->internal_long == that.internal_double;

				case var::string:
					for(unsigned i = 0; i < that.internal_string.length(); i++)
						if( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_long == 0;

					return this->internal_long == (double)that;

				case var::null:
					return this->internal_long == 0;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::boolean:
					return this->internal_double == that.internal_bool;

				case var::integer:
					return this->internal_double == that.internal_long;

				case var::real:
					return this->internal_double == that.internal_double;

				case var::string:
					for(unsigned i = 0; i < that.internal_string.length(); i++)
						if( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_double == 0;

					return this->internal_double == (double)that;

				case var::null:
					return this->internal_double == 0;
			}
			break;

		case var::resource:
			if(that.internal_type == var::resource && this->internal_resource == that.internal_resource)
				return true;
			break;

		case var::null:
			switch(that.internal_type)
			{
				case var::boolean:
					return 0 == that.internal_bool;

				case var::integer:
					return 0 == that.internal_long;

				case var::real:
					return 0 == that.internal_double;

				case var::string:
					return false;

				case var::null:
					return true;
			}
			break;
	}

	return false;
}

bool var::operator !=(const var& that) const
{
	switch(internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_bool != that.internal_bool;

				case var::integer:
					return internal_bool != that.internal_long;

				case var::real:
					return internal_bool != that.internal_double;

				case var::null:
					return internal_bool != 0;
			}
			break;

		case var::string:
			switch(that.internal_type)
			{
				case var::string:
					return internal_string != that.internal_string ;

				case var::integer:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 != that.internal_long;

					return operator double() != that.internal_long;

				case var::real:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 != that.internal_double;

					return operator double() != that.internal_double;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_long != that.internal_bool;

				case var::integer:
					return internal_long != that.internal_long;

				case var::real:
					return internal_long != that.internal_double;

				case var::string:
					for(unsigned i = 0; i < that.internal_string.length(); i++)
						if( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return internal_long != 0;

					return internal_long != (double)that;

				case var::null:
					return internal_long != 0;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_double != that.internal_bool;

				case var::integer:
					return internal_double != that.internal_long;

				case var::real:
					return internal_double != that.internal_double;

				case var::string:
					for(unsigned i = 0; i < that.internal_string.length(); i++)
						if( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return internal_double != 0;

					return internal_double != (double)that;

				case var::null:
					return internal_double != 0;
			}
			break;

		case var::map_iterator:
			switch(that.internal_type)
			{
				case var::map_iterator:
					return internal_map_iterator != that.internal_map_iterator;
			}
			break;

		case var::vector_iterator:
			switch(that.internal_type)
			{
				case var::vector_iterator:
					return internal_vector_iterator != that.internal_vector_iterator;
			}
			break;

		case var::resource:
			if(internal_resource != that.internal_resource)
				return true;
			break;

		case var::null:
			switch(that.internal_type)
			{
				case var::boolean:
					return 0 != that.internal_bool;

				case var::integer:
					return 0 != that.internal_long;

				case var::real:
					return 0 != that.internal_double;

				case var::string:
					return true;

				case var::null:
					return false;
			}
			break;
	}

	return true;
}

bool var::operator <(const var& that) const
{
	switch(internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_bool < that.internal_bool;

				case var::integer:
					return internal_bool < that.internal_long;

				case var::real:
					return internal_bool < that.internal_double;

				case var::null:
					return internal_bool < 0;

			}
			break;

		case var::string:
			switch(that.internal_type)
			{
				case var::string:
					return internal_string < that.internal_string ;

				case var::integer:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 < that.internal_long;

					return operator double() < that.internal_long;

				case var::real:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 < that.internal_double;

					return operator double() < that.internal_double;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_long < that.internal_bool;

				case var::integer:
					return internal_long < that.internal_long;

				case var::real:
					return internal_long < that.internal_double;

				case var::string:
					for(unsigned i = 0; i < that.internal_string.length(); i++)
						if( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return internal_long < 0;

					return internal_long < (double)that;

				case var::null:
					return internal_long < 0;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_double < that.internal_bool;

				case var::integer:
					return internal_double < that.internal_long;

				case var::real:
					return internal_double < that.internal_double;

				case var::string:
					for(unsigned i = 0; i < that.internal_string.length(); i++)
						if( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return internal_double < 0;

					return internal_double < (double)that;

				case var::null:
					return internal_double < 0;
			}
			break;

		case var::null:
			switch(that.internal_type)
			{
				case var::boolean:
					return 0 < that.internal_bool;

				case var::integer:
					return 0 < that.internal_long;

				case var::real:
					return 0 < that.internal_double;

				case var::null:
					return false;
			}
			break;

		case var::resource:
				return false;
	}

	return false;
}

bool var::operator >(const var& that) const
{
	switch(internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_bool > that.internal_bool;

				case var::integer:
					return internal_bool > that.internal_long;

				case var::real:
					return internal_bool > that.internal_double;

				case var::null:
					return internal_bool > 0;
			}
			break;

		case var::string:
			switch(that.internal_type)
			{
				case var::string:
					return internal_string > that.internal_string ;

				case var::integer:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 > that.internal_long;

					return operator double() > that.internal_long;

				case var::real:
					for(unsigned i = 0; i < internal_string.length(); i++)
						if( (internal_string[i] < '0' || internal_string[i] > '9') && internal_string[i] != '.')
							return 0 > internal_double;

					return operator double() > that.internal_double;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_long > that.internal_bool;

				case var::integer:
					return internal_long > that.internal_long;

				case var::real:
					return internal_long > that.internal_double;

				case var::string:
					return internal_long > (double)that;

				case var::null:
					return internal_long > 0;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_double > that.internal_bool;

				case var::integer:
					return internal_double > that.internal_long;

				case var::real:
					return internal_double > that.internal_double;

				case var::string:
					return internal_double > (double)that;

				case var::null:
					return internal_double > 0;
			}
			break;

		case var::null:
			switch(that.internal_type)
			{
				case var::boolean:
					return 0 > that.internal_bool;

				case var::integer:
					return 0 > that.internal_long;

				case var::real:
					return 0 > that.internal_double;

				case var::null:
					return false;
			}
			break;

		case var::resource:
			return false;
	}

	return false;
}

bool var::operator &&(const var& that) const
{
	switch(internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_bool && that.internal_bool;

				case var::integer:
					return internal_bool && that.internal_long;

				case var::real:
					return internal_bool && that.internal_double;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_long && that.internal_bool;

				case var::integer:
					return internal_long && that.internal_long;

				case var::real:
					return internal_long && that.internal_double;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_double && that.internal_long;

				case var::integer:
					return internal_double && that.internal_long;

				case var::real:
					return internal_double && that.internal_double;
			}
			break;
	}

	return false;
}

bool var::operator ||(const var& that) const
{
	switch(internal_type)
	{
		case var::boolean:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_bool || that.internal_bool;

				case var::integer:
					return internal_bool || that.internal_long;

				case var::real:
					return internal_bool || that.internal_double;
			}
			break;

		case var::integer:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_long || that.internal_bool;

				case var::integer:
					return internal_long || that.internal_long;

				case var::real:
					return internal_long || that.internal_double;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::boolean:
					return internal_double || that.internal_long;

				case var::integer:
					return internal_double || that.internal_long;

				case var::real:
					return internal_double || that.internal_double;
			}
			break;
	}

	return false;
}

long var::operator &(const var& that)
{
	switch(internal_type)
	{
		case var::integer:
			switch(that.internal_type)
			{
				case var::integer:
					return internal_long & that.internal_long;

				case var::real:
					return internal_long & (long)that.internal_double;
			}
			break;

		case var::real:
			switch(that.internal_type)
			{
				case var::integer:
					return (long)internal_double & that.internal_long;

				case var::real:
					return (long)internal_double & (long)that.internal_double;
			}
			break;
	}

	return false;
}

long var::operator |(const var& that)
{
	switch(internal_type)
	{
		case var::integer:
			switch(that.internal_type)
			{
				case var::integer:
					return internal_long | that.internal_long;

				case var::real:
					return internal_long | (long)that.internal_double;
			}

		case var::real:
			switch(that.internal_type)
			{
				case var::integer:
					return (long)internal_double | that.internal_long;

				case var::real:
					return (long)internal_double | (long)that.internal_double;
			}
	}

	return false;
}

var& var::operator [](const var& that)
{
	if (this->internal_type != var::map && this->internal_type != var::vector)
	{
		this->clear();
		this->internal_type = var::map;
	}

	if (this->internal_type == var::vector)
	{
		if (that.internal_type == var::integer)
		{
			long i = that;

			if (i < 0) {
				i += this->internal_vector.size() * (ceil(fabs(i)/(float)this->internal_vector.size()));
			}

			if (this->internal_vector.size() < (unsigned int)i) {
				this->internal_vector.resize(i + 1);
			}

			return (var&)this->internal_vector[i];
		}
		else
		{
			for (unsigned i = 0; i < this->internal_vector.size(); i++)
			{
				this->internal_map[i] = this->internal_vector[i];
				this->internal_vector[i].clear();
			}

			this->internal_vector.clear();

			this->internal_type = var::map;
		}
	}

	return (var&)(this->internal_map[that]);
}

var& var::operator <<(const var& that)
{
	if(this->internal_type != var::vector && this->internal_type != var::map)
	{
		this->clear();
		this->internal_type = var::vector;
	}

	if(this->internal_type == var::vector)
	{
		this->internal_vector.push_back(that);
		return *this;
	}

	var last = 0;

	for (this->internal_map_iterator = this->internal_map.begin(); this->internal_map_iterator != this->internal_map.end(); this->internal_map_iterator++)
	{
		if (this->internal_map_iterator->first.num().compare(last) ) {
			last = (last > this->internal_map_iterator->first.num() ? last : this->internal_map_iterator->first.num() ) + 1;
		}
	}

	this->internal_map[var(last)] = that;

	return *this;
}

var var::split(const var& separator)
{
	std::string delimiter_cpp = (const char*)separator;
	std::string string_cpp = (const char*)(*this);
	var ret_var;
	unsigned previous = 0, next = 0;

	if (delimiter_cpp.length() == 0) {
		return false;
	}

	while ( (next = string_cpp.find(delimiter_cpp, previous + delimiter_cpp.length()-1)) != std::string::npos)
	{
		ret_var << string_cpp.substr(previous, next - previous);
		previous = next + delimiter_cpp.length();
	}

	ret_var << string_cpp.substr(previous);

	return ret_var;
}

var var::join(const var& separator)
{
		unsigned length = 0;
		std::string glue_cpp = (const char*)separator;
		std::string ret_cpp;
		var it;

		for (it = (*this).begin(); it != (*this).end(); it++) {
			length += (*it).size();
		}

		length += separator.size() * (*this).size();
		ret_cpp.reserve(length);

		it = (*this).begin();

		while (true)
		{
			if (var::type(*it) != var::map && var::type(*it) != var::vector) {
				ret_cpp += (const char*)(*it);
			} else {
				continue;
			}

			it++;

			if (!(it != (*this).end())) {
				break;
			}

			ret_cpp += glue_cpp;
		}

		return ret_cpp;
}

bool var::compare(const var& that) const
{
	if (this->internal_type != that.internal_type) {
		return false;
	}

	return (*this == that);
}

bool var::fetch(var& key, var& value)
{
	switch(this->internal_type)
	{
		case var::map:
			if (this->internal_map_iterator == this->internal_map.end())
			{
				this->internal_map_iterator = this->internal_map.begin();
				key = this->internal_map_iterator->first;
				value = this->internal_map_iterator->second;

				return true;
			}
			else
			{
				this->internal_map_iterator++;

				if (this->internal_map_iterator == this->internal_map.end()) {
					return false;
				}

				key = this->internal_map_iterator->first;
				value = this->internal_map_iterator->second;
			}
			return true;

		case var::vector:
			if ( (unsigned) this->internal_long >= this->internal_vector.size())
			{
				this->internal_long = 0;
				key = this->internal_long;
				value = this->internal_vector[this->internal_long];

				return true;
			}
			else
			{
				this->internal_long++;

				if ( (unsigned) this->internal_long >= this->internal_vector.size()) {
					return false;
				}
				key = this->internal_long;
				value = this->internal_vector[this->internal_long];
			}
			return true;
	}

	return false;
}

var var::key()
{
	switch(this->internal_type)
	{
		case var::map_iterator:
			return (var&) this->internal_map_iterator->first;

		case var::vector_iterator:
			return this->internal_long;
	}

	return (var&) *this;
}

var& var::operator *()
{
	switch(this->internal_type)
	{
		case var::map_iterator:
			return (var&) this->internal_map_iterator->second;

		case var::vector_iterator:
			return (var&) *this->internal_vector_iterator;
	}

	return (var&) *this;
}

var var::begin()
{
	var result;

	switch(this->internal_type)
	{
		case var::map:
			result.internal_map_iterator = this->internal_map.begin();
			result.internal_type = var::map_iterator;
			return result;

		case var::vector:
			result.internal_long = 0;
			result.internal_vector_iterator =  this->internal_vector.begin();
			result.internal_type = var::vector_iterator;
			return result;
	}

	return 0;
}

var var::end()
{
	var result;

	switch(this->internal_type)
	{
		case var::map:
			result.internal_map_iterator = this->internal_map.end();
			result.internal_type = var::map_iterator;
			return result;

		case var::vector:
			result.internal_long = this->internal_vector.size();
			result.internal_vector_iterator = this->internal_vector.end();
			result.internal_type = var::vector_iterator;
			return result;
	}

	return 0;
}

unsigned long var::size() const
{
	switch(this->internal_type)
	{
		case var::string:
			return this->internal_string.length();

		case var::map:
			return this->internal_map.size();

		case var::vector:
			return this->internal_vector.size();
	}

	return 0;
}

var var::num() const
{
	var result;
	switch(this->internal_type)
	{
		case var::string:
			result.internal_double = atof(this->internal_string.c_str());
			result.internal_long = (long)result.internal_double;
			result.internal_type = (result.internal_double == result.internal_long) ? var::integer : var::real;
			break;

		case var::integer:
			result.internal_long = this->internal_long;
			result.internal_type = var::integer;
			break;

		case var::real:
			result.internal_double = this->internal_double;
			result.internal_type = var::real;
			break;

		case var::null:
			result.internal_long = 0;
			result.internal_type = var::integer;
			break;
	}

	return result;
}

var::operator bool() const
{
	switch(this->internal_type)
	{
		case var::boolean:
			return this->internal_bool;

		case var::string:
			return atof(this->internal_string.c_str()) ? true : false;

		case var::integer:
			return this->internal_long ? true : false;

		case var::real:
			return this->internal_double ? true : false;

		case var::map:
			return !this->internal_map.empty();

		case var::vector:
			return !this->internal_vector.empty();

		case var::resource:
			return this->internal_resource ? true : false;
	}

	return false;
}

var::operator long() const
{
	switch(this->internal_type)
	{
		case var::boolean:
			return this->internal_bool ? 1 : 0;

		case var::string:
			return (long)atof(this->internal_string.c_str());

		case var::integer:
			return this->internal_long;

		case var::real:
			return (long)this->internal_double;
	}

	return 0;
}

var::operator double() const
{
	switch(this->internal_type)
	{
		case var::boolean:
			return this->internal_bool ? 1 : 0;

		case var::string:
			return atof(this->internal_string.c_str());

		case var::integer:
			return (double)this->internal_long;

		case var::real:
			return this->internal_double;
	}

	return 0;
}

var::operator const char*() const
{
	std::string result;
	char* buffer;

	switch(this->internal_type)
	{
		case var::null:
			return "";

		case var::boolean:
			return this->internal_bool ? "true" : "false";

		case var::string:
			return this->internal_string.c_str();

		case var::integer:
			buffer = (char*) malloc(32);
			sprintf(buffer,"%ld", this->internal_long);
			break;

		case var::real:
			buffer = (char*) malloc(32);
			sprintf(buffer,"%f", this->internal_double);
			break;

		default:
			buffer = (char*) malloc(32);
			sprintf(buffer,"0");
	}

	result = buffer;
	free(buffer);

	return result.c_str();
}

var::operator void *() const
{
	if (this->internal_type == var::resource) {
		return this->internal_resource;
	} else {
		return NULL;
	}
}

var var::encode() const
{
	std::string result;
	unsigned int pos = 0;

	switch(this->internal_type)
	{
		case var::boolean:
		case var::integer:
		case var::real:
			return (const char*) *this;

		case var::string:
			result = this->internal_string;

			for (pos = 0; pos < result.size(); pos++)
			{
				switch (result[pos])
				{
					case '\\':
						result.replace(pos++, 1, "\\\\");
						break;

					case '"':
						result.replace(pos++, 1, "\\\"");
						break;

					case '/':
						result.replace(pos++, 1, "\\/");
						break;

					case '\n':
						result.replace(pos++, 1, "\\n");
						break;

					case '\r':
						result.replace(pos++, 1, "\\r");
						break;

					case '\t':
						result.replace(pos++, 1, "\\t");
						break;
				}
			}

			return "\"" + result + "\"";

		case var::map:
			if (this->internal_map.size() > 0)
			{
				result = "{";

				for(internal_map_type::const_iterator it = this->internal_map.begin(); it != this->internal_map.end(); it++) {
					result += (const char*)((it)->first.encode() + ":" + (it)->second.encode() + ",");
				}

				result[result.size()-1] = '}';

				return result;
			}
			else {
				return "{}";
			}

		case var::vector:
			if (this->internal_vector.size() > 0)
			{
				result = "[";

				for(unsigned i = 0; i < this->internal_vector.size(); i++) {
					result += (const char*)(this->internal_vector[i].encode() + ",");
				}

				result[result.size()-1] = ']';

				return result;
			} else {
				return "[]";
			}

		case var::resource:
			return "\"(resource)\"";

		/* var::null, var::map_iterator, var::vector_iterator */
		default:
			return "null";
	}

	return result;
}

void var::decodeSub(const std::string& data, unsigned& i, var& value)
{
	value.clear();

	for (; i < data.length(); i++)
	{
		while (data[i] == ' ') i++;

		if ( (data[i] >= '0' && data[i] <= '9') || data[i] == '-') /* [-0-9] */
		{
			var::decodeNumber(data, i, value.internal_double);

			if (ceil(value.internal_double) == (floor(value.internal_double)))
			{
				value.internal_long = value.internal_double;
				value.internal_type = var::integer;
			}
			else {
				value.internal_type = var::real;
			}

			return;
		}

		if (data[i] == '$'|| data[i] == '_'|| (data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z')) /* [_a-zA-Z] */
		{
			var::decodeSymbol(data, i, value.internal_string);

			if (value.internal_string == "null")
			{
				value.internal_string.clear();
				value.internal_type = var::null;

				return;
			}

			if (value.internal_string == "true")
			{
				value.internal_string.clear();
				value.internal_type = var::boolean;
				value.internal_bool = true;

				return;
			}

			if (value.internal_string == "false")
			{
				value.internal_string.clear();
				value.internal_type = var::boolean;
				value.internal_bool = false;

				return;
			}

			value.internal_type = var::string;

			return;
		}

		if (data[i] == '"')
		{
			var::decodeString(data, i, value.internal_string);
			value.internal_type = var::string;

			return;
		}

		switch (data[i])
		{
			case '[':
			case '(':
				value.internal_type = var::vector;
				var::decodeVector(data, i, value.internal_vector);
				return;

			case '{':
				value.internal_type = var::map;
				var::decodeMap(data, i, value.internal_map);
				return;

			case ',':
			case ':':
				return;

			default:
				printf("%s\n", data.c_str());
				for (unsigned c = 0; c < i; c++) printf(" ");
				printf ("^\n");
				throw;
		}
	}

	return;
}

inline void var::decodeNumber(const std::string& data, unsigned& i, double& value)
{
	unsigned begin = i;

	while (i < data.length() && (data[i] == '-' || (data[i] >= '0' && data[i] <= '9') || data[i] == '.')) /* [-0-9.]+ */ {
		i++;
	}

	char* strValue = strdup(data.substr(begin, i-begin).c_str());
	value = atof(strValue);
	free(strValue);

	i--;
}

inline void var::decodeSymbol(const std::string& data, unsigned& i, std::string& value)
{
	unsigned begin = i;
	for (unsigned j = 0; i < data.length(); i++, j++)
	{
		if ( !(data[i] == '$' || data[i] == '_' || (data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z') || (data[i] >= '0' && data[i] <= '9')) ) /* [_a-zA-Z0-9] */ {
			value  = data.substr(begin, j);
			i--;
			return;
		}
	}
}

inline void var::decodeString(const std::string& data, unsigned& i, std::string& value)
{
	unsigned begin = ++i;
	for (unsigned j = 0; i < data.length(); i++, j++)
	{
		if (data[i] == '\\')
		{
			i++; j++;
			continue;
		}

		if (data[i] == '"')
		{
			value  = data.substr(begin, j);
			break;
		}
	}

	/* TODO: Escape string */
	for (unsigned j = 0; j < value.length(); j++)
	{
		if (value[j] == '\\')
		{
			switch (value[j+1])
			{
				case '\\':
					value.replace(j, 2, "\\");
					break;

				case '"':
					value.replace(j, 2, "\"");
					break;

				case '/':
					value.replace(j, 2, "/");
					break;

				case 'n':
					value.replace(j, 2, "\n");
					break;

				case 'r':
					value.replace(j, 2, "\r");
					break;

				case 't':
					value.replace(j, 2, "\t");
					break;
			}
		}
	}
}

inline void var::decodeVector(const std::string& data, unsigned& i, var::internal_vector_type& value)
{
	std::list<var> varList;
	i++;
	for (; i < data.length(); i++)
	{
		while (data[i] == ',' || data[i] == ' ' || data[i] == '\n' || data[i] == '\r' || data[i] == '\t') i++; /* [,\s]* */

		if (data[i] == ']' || data[i] == ')')
		{
			value.resize(varList.size());

			unsigned j = 0;
			for (std::list<var>::iterator it = varList.begin(); it != varList.end(); it++)
			{
				value[j] = *it;
				j++;
			}

			return;
		}

		varList.push_back(var());
		decodeSub(data, i, *(varList.rbegin()));
	}
}

inline void var::decodeMap(const std::string& data, unsigned& i, var::internal_map_type& value)
{
	i++;
	var mapKey;
	var mapValue;
	while (data[i] == ' ') i++;

	for (; i < data.length(); i++)
	{
		while (data[i] == ',' || data[i] == ' ' ||data[i] == '\n' || data[i] == '\r' || data[i] == '\t') i++; /* [,\s]* */

		if (data[i] == '}') return;

		mapKey.clear();
		decodeSub(data, i, mapKey);

		do {
			i++;
		} while (data[i] == ':' || data[i] == ' ' || data[i] == '\n' || data[i] == '\r' || data[i] == '\t'); /* [:\s]* */

		mapValue.clear();
		decodeSub(data, i, mapValue);

		value[mapKey] = mapValue;
	}
}

var& var::decode(const var& json)
{
	this->clear();

	if (json.internal_type != var::string) {
		return *this;
	}

	unsigned i = 0;
	var::decodeSub(json.internal_string, i, *this);

	return *this;
}

var var:: operator +(int a) const { return operator +(var(a)); }
var var:: operator +(const char* a) const { return operator +(var(a)); }
bool var:: operator ==(bool a) const { return operator ==(var(a)); }
bool var:: operator ==(int a) const{ return operator ==(var(a)); }
bool var:: operator ==(float a) const { return operator ==(var(a)); }
bool var:: operator ==(double a) const { return operator ==(var(a)); }
bool var:: operator ==(const char* a) const { return operator ==(var(a)); }
bool var:: operator !=(int a) const { return operator !=(var(a)); }
bool var:: operator !=(const char* a) const { return operator !=(var(a)); }
bool var:: operator <(unsigned int a) const { return operator <(var(a));}
var& var:: operator [](int a) { return operator[](var(a)); }
var& var:: operator [](const char* a) { return operator[](var(a)); }
var& var:: operator <<(int a) { return operator<<(var(a)); }

var operator+(char* a, var b) {return var(a) + b;}
var operator+(const char* a, var b) {return var(a) + b;}
var::operator int() const { return operator long(); }

int var::type(const var& that) {
	return that.internal_type;
}

int var::exists(const var& haystack, const var& needle)
{
	unsigned size = 0;
	switch (haystack.internal_type)
	{
		case var::map:

			for (internal_map_type::const_iterator iterador = haystack.internal_map.begin(); iterador != haystack.internal_map.end(); iterador++)
			{
				if((iterador->first).compare(needle)) {
					return 1;
				}
			}

		break;

		case var::vector:
			size = (int)needle;
			if (size > 0 && size < haystack.internal_vector.size()) {
				return 1;
			}

		break;

		default:
			return 0;
	}

	return 0;
}
