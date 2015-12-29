#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <iostream>
#include <list>
#include <algorithm>

#include "var.hpp"


Var::Var()
{
	this->internal_type = Var::null;
}

Var::Var(Var_t that)
{
	this->internal_type = that;
}

Var::Var(const Var& that)
{
	*this = that;
}

Var::Var(bool that)
{
	this->internal_bool = that;
	this->internal_type = Var::boolean;
}

Var::Var(int that)
{
	this->internal_long = that;
	this->internal_type = Var::integer;
}

Var::Var(unsigned int that)
{
	this->internal_long = that;
	this->internal_type = Var::integer;
}

Var::Var(long that)
{
	this->internal_long = that;
	this->internal_type = Var::integer;
}

Var::Var(unsigned long that)
{
	this->internal_long = that;
	this->internal_type = Var::integer;
}

Var::Var(double that)
{
	this->internal_double = that;
	this->internal_type = Var::real;
}

Var::Var(const char* that)
{
	this->internal_string = that;
	this->internal_type = Var::string;
}

Var::Var(const std::string& that)
{
	this->internal_string = that;
	this->internal_type = Var::string;
}

Var::Var(void* that)
{
	this->internal_resource = that;
	this->internal_type = Var::resource;
}

Var::~Var()
{
	this->clear();
}

void Var::clear()
{
	switch (this->internal_type)
	{
		case Var::boolean:
			this->internal_bool = false;
			break;

		case Var::string:
			this->internal_string.clear();
			break;

		case Var::integer:
			this->internal_long = 0;
			break;

		case Var::real:
			this->internal_double = 0;
			break;

		case Var::map:
			for (Var::internal_map_type::iterator i = this->internal_map.begin(); i != this->internal_map.end(); i++) {
				delete i->second;
			}
			this->internal_map.clear();
			break;

		case Var::vector:
			for (size_t i = 0; i < this->internal_vector.size(); i++) {
				delete this->internal_vector[i];
			}
			this->internal_vector.clear();
			break;

		case Var::vector_iterator:
			this->internal_long = 0;
			break;

		case Var::resource:
			this->internal_resource = NULL;
			break;
	}

	this->internal_type = Var::null;
}

Var& Var::operator =(const Var& that)
{
	this->clear();

	switch (that.internal_type)
	{
		case Var::boolean:
			this->internal_bool = that.internal_bool;
			this->internal_type = Var::boolean;

			break;

		case Var::string:
			this->internal_string = that.internal_string;
			this->internal_type = Var::string;

			break;

		case Var::integer:
			this->internal_long = that.internal_long;
			this->internal_type = Var::integer;

			break;

		case Var::real:
			this->internal_double = that.internal_double;
			this->internal_type = Var::real;

			break;

		case Var::map:
			for (Var::internal_map_type::const_iterator i = that.internal_map.begin(); i != that.internal_map.end(); i++)
			{
				Var &container = *(this->internal_map[i->first] = new Var());
				container = *(i->second);
			}
			this->internal_type = Var::map;

			break;

		case Var::map_iterator:
			this->internal_map_iterator = that.internal_map_iterator;
			this->internal_type = Var::map_iterator;

			break;

		case Var::vector:
			this->internal_vector.resize(that.internal_vector.size());
			for (size_t i = 0; i < that.internal_vector.size(); i++)
			{
				Var* container = new Var(*(that.internal_vector[i]));
				this->internal_vector[i] = container;
			}
			this->internal_type = Var::vector;

			break;

		case Var::vector_iterator:
			this->internal_vector_iterator = that.internal_vector_iterator;
			this->internal_type = Var::vector_iterator;

			break;

		case Var::resource:
			this->internal_resource = that.internal_resource;
			this->internal_type = Var::resource;

			break;

		case Var::null:
			this->internal_type = Var::null;
	}

	return *this;
}

Var Var::operator +(const Var& that) const
{
	Var result;

	switch (this->internal_type)
	{
		case Var::boolean:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_bool = this->internal_bool || that.internal_bool;
					result.internal_type = Var::boolean;

					return result;

				case Var::integer:
					result.internal_long = (this->internal_bool?1:0) + that.internal_long;
					result.internal_type = Var::integer;

					return result;

				case Var::real:
					result.internal_double = (this->internal_bool?1.0:0.0) + that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					result.internal_string = (this->internal_bool?"true":"false") + that.internal_string;
					result.internal_type = Var::string;

					return result;
			}
			break;

		case Var::integer:
			switch (that.internal_type)
			{

				case Var::boolean:
					result.internal_long = this->internal_long + (that.internal_bool?1:0);
					result.internal_type = Var::integer;

					return result;

				case Var::integer:
					result.internal_long = this->internal_long + that.internal_long;
					result.internal_type = Var::integer;

					return result;

				case Var::real:
					result.internal_double = this->internal_long + that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					result.internal_string = this->toString() + that.internal_string;
					result.internal_type = Var::string;

					return result;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_double = this->internal_double + (that.internal_bool?1.0:0.0);
					result.internal_type = Var::real;

					return result;

				case Var::integer:
					result.internal_double = this->internal_double + that.internal_long;
					result.internal_type = Var::real;

					return result;

				case Var::real:
					result.internal_double = this->internal_double + that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					result.internal_string = this->toString() + that.internal_string;
					result.internal_type = Var::string;

					return result;
			}
			break;

		case Var::string:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_string = this->internal_string + (that.internal_bool?"true":"false");
					result.internal_type = Var::string;

					return result;

				case Var::integer:
					result.internal_string = this->internal_string + that.toString();
					result.internal_type = Var::string;

					return result;

				case Var::real:
					result.internal_string = this->internal_string + that.toString();
					result.internal_type = Var::string;

					return result;

				case Var::string:
					result.internal_string = this->internal_string + that.internal_string;
					result.internal_type = Var::string;

					return result;
			}
			break;
	}

	return result;
}

Var Var::operator -(const Var& that) const
{
	Var result = this->num();

	switch (result.internal_type)
	{
		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_long = result.internal_long - (that.internal_bool?1:0);
					result.internal_type = Var::integer;

					return result;

				case Var::integer:
					result.internal_long = result.internal_long - that.internal_long;
					result.internal_type = Var::integer;

					return result;

				case Var::real:
					result.internal_double = result.internal_long - that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					return result - that.num();
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_double = result.internal_double - (that.internal_bool?1.0:0.0);
					result.internal_type = Var::integer;

					return result;

				case Var::integer:
					result.internal_double = result.internal_double - that.internal_long;
					result.internal_type = Var::real;

					return result;

				case Var::real:
					result.internal_double = result.internal_double - that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					return result - that.num();
			}
			break;
	}

	return result;
}

Var Var::operator *(const Var& that) const
{
	Var result = this->num();

	switch (result.internal_type)
	{
		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_long = result.internal_long * (that.internal_bool?1:0);
					result.internal_type = Var::integer;

					return result;

				case Var::integer:
					result.internal_long = result.internal_long * that.internal_long;
					result.internal_type = Var::integer;

					return result;

				case Var::real:
					result.internal_double = result.internal_long * that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					return result * that.num();
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_double = result.internal_double * (that.internal_bool?1.0:0.0);
					result.internal_type = Var::integer;

					return result;

				case Var::integer:
					result.internal_double = result.internal_double * that.internal_long;
					result.internal_type = Var::real;

					return result;

				case Var::real:
					result.internal_double = result.internal_double * that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					return result * that.num();
			}
			break;
	}

	return result;
}

Var Var::operator /(const Var& that) const
{
	Var result = this->num();

	switch (result.internal_type)
	{
		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_long = result.internal_long / (that.internal_bool?1:0);
					result.internal_type = Var::integer;

					return result;

				case Var::integer:
					result.internal_long = result.internal_long / that.internal_long;
					result.internal_type = Var::integer;

					return result;

				case Var::real:
					result.internal_double = result.internal_long / that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					return result / that.num();
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					result.internal_double = result.internal_double / (that.internal_bool?1.0:0.0);
					result.internal_type = Var::integer;

					return result;

				case Var::integer:
					result.internal_double = result.internal_double / that.internal_long;
					result.internal_type = Var::real;

					return result;

				case Var::real:
					result.internal_double = result.internal_double / that.internal_double;
					result.internal_type = Var::real;

					return result;

				case Var::string:
					return result / that.num();
			}
			break;
	}

	return result;
}

Var& Var::operator ++(int)
{
	switch (this->internal_type)
	{
		case Var::integer:
			this->internal_long++;
			break;

		case Var::real:
			this->internal_double++;
			break;

		case Var::map_iterator:
			this->internal_map_iterator++;
			break;

		case Var::vector_iterator:
			this->internal_long++;
			this->internal_vector_iterator++;
			break;
	}

	return *this;
}

Var& Var::operator --(int)
{
	switch (this->internal_type)
	{
		case Var::integer:
			this->internal_long--;
			break;

		case Var::real:
			this->internal_double--;
			break;

		case Var::map_iterator:
			this->internal_map_iterator--;
			break;

		case Var::vector_iterator:
			this->internal_vector_iterator--;
			break;
	}

	return *this;
}

bool Var::operator ==(const Var& that) const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_bool == that.internal_bool;

				case Var::integer:
					return this->internal_bool == that.internal_long;

				case Var::real:
					return this->internal_bool == that.internal_double;

				case Var::null:
					return this->internal_bool == 0;
			}
			break;

		case Var::string:
			switch (that.internal_type)
			{
				case Var::string:
					return this->internal_string == that.internal_string ;

				case Var::integer:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 == that.internal_long;

					return operator double() == that.internal_long;

				case Var::real:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 == that.internal_double;

					return operator double() == that.internal_double;
			}
			break;

		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_long == that.internal_bool;

				case Var::integer:
					return this->internal_long == that.internal_long;

				case Var::real:
					return this->internal_long == that.internal_double;

				case Var::string:
					for (unsigned i = 0; i < that.internal_string.length(); i++)
						if ( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_long == 0;

					return this->internal_long == (double)that;

				case Var::null:
					return this->internal_long == 0;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_double == that.internal_bool;

				case Var::integer:
					return this->internal_double == that.internal_long;

				case Var::real:
					return this->internal_double == that.internal_double;

				case Var::string:
					for (unsigned i = 0; i < that.internal_string.length(); i++)
						if ( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_double == 0;

					return this->internal_double == (double)that;

				case Var::null:
					return this->internal_double == 0;
			}
			break;

		case Var::resource:
			if (that.internal_type == Var::resource && this->internal_resource == that.internal_resource)
				return true;
			break;

		case Var::null:
			switch (that.internal_type)
			{
				case Var::boolean:
					return 0 == that.internal_bool;

				case Var::integer:
					return 0 == that.internal_long;

				case Var::real:
					return 0 == that.internal_double;

				case Var::string:
					return false;

				case Var::null:
					return true;
			}
			break;
	}

	return false;
}

bool Var::operator !=(const Var& that) const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_bool != that.internal_bool;

				case Var::integer:
					return this->internal_bool != that.internal_long;

				case Var::real:
					return this->internal_bool != that.internal_double;

				case Var::null:
					return this->internal_bool != 0;
			}
			break;

		case Var::string:
			switch (that.internal_type)
			{
				case Var::string:
					return this->internal_string != that.internal_string ;

				case Var::integer:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 != that.internal_long;

					return operator double() != that.internal_long;

				case Var::real:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 != that.internal_double;

					return operator double() != that.internal_double;
			}
			break;

		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_long != that.internal_bool;

				case Var::integer:
					return this->internal_long != that.internal_long;

				case Var::real:
					return this->internal_long != that.internal_double;

				case Var::string:
					for (unsigned i = 0; i < that.internal_string.length(); i++)
						if ( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_long != 0;

					return this->internal_long != (double)that;

				case Var::null:
					return this->internal_long != 0;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_double != that.internal_bool;

				case Var::integer:
					return this->internal_double != that.internal_long;

				case Var::real:
					return this->internal_double != that.internal_double;

				case Var::string:
					for (unsigned i = 0; i < that.internal_string.length(); i++)
						if ( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_double != 0;

					return this->internal_double != (double)that;

				case Var::null:
					return this->internal_double != 0;
			}
			break;

		case Var::map_iterator:
			switch (that.internal_type)
			{
				case Var::map_iterator:
					return this->internal_map_iterator != that.internal_map_iterator;
			}
			break;

		case Var::vector_iterator:
			switch (that.internal_type)
			{
				case Var::vector_iterator:
					return this->internal_vector_iterator != that.internal_vector_iterator;
			}
			break;

		case Var::resource:
			if (this->internal_resource != that.internal_resource)
				return true;
			break;

		case Var::null:
			switch (that.internal_type)
			{
				case Var::boolean:
					return 0 != that.internal_bool;

				case Var::integer:
					return 0 != that.internal_long;

				case Var::real:
					return 0 != that.internal_double;

				case Var::string:
					return true;

				case Var::null:
					return false;
			}
			break;
	}

	return true;
}

bool Var::operator <(const Var& that) const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_bool < that.internal_bool;

				case Var::integer:
					return this->internal_bool < that.internal_long;

				case Var::real:
					return this->internal_bool < that.internal_double;

				case Var::null:
					return false;

			}
			break;

		case Var::string:
			switch (that.internal_type)
			{
				case Var::string:
					return this->internal_string < that.internal_string ;

				case Var::integer:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 < that.internal_long;

					return operator double() < that.internal_long;

				case Var::real:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 < that.internal_double;

					return operator double() < that.internal_double;
			}
			break;

		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_long < that.internal_bool;

				case Var::integer:
					return this->internal_long < that.internal_long;

				case Var::real:
					return this->internal_long < that.internal_double;

				case Var::string:
					for (unsigned i = 0; i < that.internal_string.length(); i++)
						if ( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_long < 0;

					return this->internal_long < (double)that;

				case Var::null:
					return this->internal_long < 0;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_double < that.internal_bool;

				case Var::integer:
					return this->internal_double < that.internal_long;

				case Var::real:
					return this->internal_double < that.internal_double;

				case Var::string:
					for (unsigned i = 0; i < that.internal_string.length(); i++)
						if ( (that.internal_string[i] < '0' || that.internal_string[i] > '9') && that.internal_string[i] != '.')
							return this->internal_double < 0;

					return this->internal_double < (double)that;

				case Var::null:
					return this->internal_double < 0;
			}
			break;

		case Var::null:
			switch (that.internal_type)
			{
				case Var::boolean:
					return 0 < that.internal_bool;

				case Var::integer:
					return 0 < that.internal_long;

				case Var::real:
					return 0 < that.internal_double;

				case Var::null:
					return false;
			}
			break;

		case Var::resource:
				return false;
	}

	return false;
}

bool Var::operator >(const Var& that) const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_bool > that.internal_bool;

				case Var::integer:
					return this->internal_bool > that.internal_long;

				case Var::real:
					return this->internal_bool > that.internal_double;

				case Var::null:
					return this->internal_bool > 0;
			}
			break;

		case Var::string:
			switch (that.internal_type)
			{
				case Var::string:
					return this->internal_string > that.internal_string ;

				case Var::integer:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 > that.internal_long;

					return operator double() > that.internal_long;

				case Var::real:
					for (unsigned i = 0; i < this->internal_string.length(); i++)
						if ( (this->internal_string[i] < '0' || this->internal_string[i] > '9') && this->internal_string[i] != '.')
							return 0 > this->internal_double;

					return operator double() > that.internal_double;
			}
			break;

		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_long > that.internal_bool;

				case Var::integer:
					return this->internal_long > that.internal_long;

				case Var::real:
					return this->internal_long > that.internal_double;

				case Var::string:
					return this->internal_long > (double)that;

				case Var::null:
					return this->internal_long > 0;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_double > that.internal_bool;

				case Var::integer:
					return this->internal_double > that.internal_long;

				case Var::real:
					return this->internal_double > that.internal_double;

				case Var::string:
					return this->internal_double > (double)that;

				case Var::null:
					return this->internal_double > 0;
			}
			break;

		case Var::null:
			switch (that.internal_type)
			{
				case Var::boolean:
					return false;

				case Var::integer:
					return 0 > that.internal_long;

				case Var::real:
					return 0 > that.internal_double;

				case Var::null:
					return false;
			}
			break;

		case Var::resource:
			return false;
	}

	return false;
}

bool Var::operator &&(const Var& that) const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_bool && that.internal_bool;

				case Var::integer:
					return this->internal_bool && that.internal_long;

				case Var::real:
					return this->internal_bool && that.internal_double;
			}
			break;

		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_long && that.internal_bool;

				case Var::integer:
					return this->internal_long && that.internal_long;

				case Var::real:
					return this->internal_long && that.internal_double;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_double && that.internal_long;

				case Var::integer:
					return this->internal_double && that.internal_long;

				case Var::real:
					return this->internal_double && that.internal_double;
			}
			break;
	}

	return false;
}

bool Var::operator ||(const Var& that) const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_bool || that.internal_bool;

				case Var::integer:
					return this->internal_bool || that.internal_long;

				case Var::real:
					return this->internal_bool || that.internal_double;
			}
			break;

		case Var::integer:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_long || that.internal_bool;

				case Var::integer:
					return this->internal_long || that.internal_long;

				case Var::real:
					return this->internal_long || that.internal_double;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::boolean:
					return this->internal_double || that.internal_long;

				case Var::integer:
					return this->internal_double || that.internal_long;

				case Var::real:
					return this->internal_double || that.internal_double;
			}
			break;
	}

	return false;
}

long Var::operator &(const Var& that)
{
	switch (this->internal_type)
	{
		case Var::integer:
			switch (that.internal_type)
			{
				case Var::integer:
					return this->internal_long & that.internal_long;

				case Var::real:
					return this->internal_long & (long)that.internal_double;
			}
			break;

		case Var::real:
			switch (that.internal_type)
			{
				case Var::integer:
					return (long)internal_double & that.internal_long;

				case Var::real:
					return (long)internal_double & (long)that.internal_double;
			}
			break;
	}

	return false;
}

long Var::operator |(const Var& that)
{
	switch (this->internal_type)
	{
		case Var::integer:
			switch (that.internal_type)
			{
				case Var::integer:
					return this->internal_long | that.internal_long;

				case Var::real:
					return this->internal_long | (long)that.internal_double;
			}

		case Var::real:
			switch (that.internal_type)
			{
				case Var::integer:
					return (long)internal_double | that.internal_long;

				case Var::real:
					return (long)internal_double | (long)that.internal_double;
			}
	}

	return false;
}

Var& Var::operator [](const Var& that)
{
	if (this->internal_type != Var::map && this->internal_type != Var::vector)
	{
		this->clear();
		this->internal_type = Var::map;
	}

	if (this->internal_type == Var::vector)
	{
		if (that.internal_type == Var::integer)
		{
			long i = that;

			if (i < 0) {
				i += this->internal_vector.size() * (ceil(i/(float)this->internal_vector.size()));
			}

			if (this->internal_vector.size() < (unsigned long)i)
			{
				unsigned long oldSize = this->internal_vector.size() -1;
				this->internal_vector.resize(i + 1);

				for (unsigned long j = oldSize; j < this->internal_vector.size(); j++) {
					this->internal_vector[j] = new Var();
				}
			}

			return (Var&)(*(this->internal_vector[i]));
		}
		else
		{
			for (unsigned i = 0; i < this->internal_vector.size(); i++)
			{
				this->internal_map[Var(i).toString()] = this->internal_vector[i];
				this->internal_vector[i]->clear();
			}

			this->internal_vector.clear();

			this->internal_type = Var::map;
		}
	}

	if (this->internal_map[that.toString()] == NULL) {
		this->internal_map[that.toString()] = new Var();
	}

	return (Var&)(*(this->internal_map[that.toString()]));
}

Var& Var::operator <<(const Var& that)
{
	Var* container = new Var(that);
	if (this->internal_type != Var::vector && this->internal_type != Var::map)
	{
		this->clear();
		this->internal_type = Var::vector;
	}

	if (this->internal_type == Var::vector)
	{
		this->internal_vector.push_back(container);
		return *this;
	}

	Var last = 0;

	for (this->internal_map_iterator = this->internal_map.begin(); this->internal_map_iterator != this->internal_map.end(); this->internal_map_iterator++)
	{
		if (Var(this->internal_map_iterator->first).num().compare(last) ) {
			last = (last > Var(this->internal_map_iterator->first).num() ? last : Var(this->internal_map_iterator->first).num() ) + 1;
		}
	}

	this->internal_map[last.toString()] = container;

	return *this;
}

Var Var::concat(const var& that) const
{
	var result;

	if (this->internal_type == that.internal_type)
	{
		if (this->internal_type == Var::string) {
			result = *this + that;
		} else
		if (this->internal_type == Var::vector)
		{
			result = *this;

			for (unsigned long i = 0; i < that.internal_vector.size(); i++) {
				result << *(that.internal_vector[i]);
			}
		}
	}

	return result;
}

Var Var::indexOf(const Var& searchvalue, const Var& start) const
{
	var result;

	if (this->internal_type == Var::string) {
		result = (long)(this->internal_string.find(searchvalue.toString(), (long)start));
	}

	return result;
}

Var Var::lastIndexOf(const Var& searchvalue) const
{
	var result;

	if (this->internal_type == Var::string) {
		result = (long)(this->internal_string.rfind(searchvalue.toString()));
	}

	return result;
}

Var Var::lastIndexOf(const Var& searchvalue, const Var& start) const
{
	var result;

	if (this->internal_type == Var::string) {
		result = (long)(this->internal_string.rfind(searchvalue.toString(), this->internal_string.size() - (long)start));
	}

	return result;
}

Var Var::slice(const Var& start) const
{
	return this->slice(start, (long)this->internal_string.size());
}

Var Var::slice(const Var& start, const Var& stop) const
{
	var result;

	if (this->internal_type == Var::string)
	{
		unsigned long begin = start;
		unsigned long end = stop;

		begin = begin < 0 ? begin + this->internal_string.size(): begin;
		begin = begin < 0 ? 0 : begin;
		begin = begin > this->internal_string.size()? this->internal_string.size() : begin;

		end = end < 0 ? end + this->internal_string.size() : end;
		end = end < 0 ? 0 : end;
		end = end > this->internal_string.size()? this->internal_string.size() : end;

		result = this->internal_string.substr(begin, end - begin);
	}

	return result;
}

Var Var::charAt(const Var& index) const
{
	var result;

	if (this->internal_type == Var::string) {
		result = this->internal_string.substr((long)index, 1);
	}

	return result;
}

Var Var::charCodeAt(const Var& index) const
{
	var result;

	if (this->internal_type == Var::string) {
		return this->toString()[(long)index];
	}

	return result;
}

Var Var::fromCharCode(const var& that)
{
	char code = (long)that;

	std::string result;
	result.resize(1);
	result[0] = code;

	return result;
}

Var Var::localeCompare(const Var& compareString) const
{
	var result;

	if (this->internal_type == Var::string)
	{
		long compareResult =  (long)this->internal_string.compare(compareString.toString());

		compareResult = compareResult > 0 ? 1 : compareResult;
		compareResult = compareResult < 0 ? -1 : compareResult;

		result = compareResult;
	}

	return result;
}

Var Var::replace(const Var& searchvalue, const var& newvalue) const
{
	var result;

	if (this->internal_type == Var::string)
	{
		const char* search_c  = searchvalue;
		const char* replace_c = newvalue;
		const char* subject_c = *this;

		int i, count = 0;
		int replacelen = strlen(replace_c);
		int searchlen = strlen(search_c);

		for (i = 0; subject_c[i]; ++i)
		{
			if (strstr(&subject_c[i], search_c) == &subject_c[i]) {
				++count, i += searchlen - 1;
			}
		}

		char *ret_c = (char *) calloc(i + 1 + count * (replacelen - searchlen), sizeof(char));

		if (!ret_c) return 0;

		i = 0;

		while (*subject_c)
		{
			if (strstr(subject_c, search_c) == subject_c) {
				strcpy(&ret_c[i], replace_c), i += replacelen,	subject_c += searchlen;
			} else {
				ret_c[i++] = *subject_c++;
			}
		}

		ret_c[i] = '\0';
		var ret = ret_c;
		free(ret_c);

		result = ret;
	}

	return result;
}

Var Var::split(const Var& separator) const
{
	std::string delimiter_cpp = separator.toString();
	std::string string_cpp = this->toString();
	Var ret_Var;
	size_t previous = 0, next = 0;

	while ( (next = string_cpp.find(delimiter_cpp, previous + delimiter_cpp.length()-1)) != std::string::npos)
	{
		ret_Var << string_cpp.substr(previous, next - previous);
		previous = next + delimiter_cpp.length();
	}

	ret_Var << string_cpp.substr(previous);

	return ret_Var;
}

Var Var::substr(const Var& start) const
{
	return this->substring(start, (long)this->internal_string.size());
}

Var Var::substr(const Var& start, const Var& length) const
{
	var result;

	if (this->internal_type == Var::string)
	{
		unsigned long begin = start;
		unsigned long size = length;

		begin = begin < 0 ? begin + this->internal_string.size(): begin;
		begin = begin < 0 ? 0 : begin;
		begin = begin > this->internal_string.size()? this->internal_string.size() : begin;

		result = this->internal_string.substr(begin, size);
	}

	return result;
}

Var Var::substring(const Var& start) const
{
	return this->substring(start, (long)this->internal_string.size());
}

Var Var::substring(const Var& start, const Var& stop) const
{
	var result;

	if (this->internal_type == Var::string)
	{
		unsigned long begin = start;
		unsigned long end = stop;

		begin = begin < 0 ? 0 : begin;
		begin = begin > this->internal_string.size()? this->internal_string.size() : begin;

		end = end < 0 ? 0 : end;
		end = end > this->internal_string.size()? this->internal_string.size() : end;

		if (begin > end)
		{
			begin = begin + end;
			end = begin - end;
			begin = begin - end;
		}

		result = this->internal_string.substr(begin, end - begin);
	}

	return result;
}

Var Var::toLocaleLowerCase() const
{
	return this->toLowerCase();
}

Var Var::toLocaleUpperCase() const
{
	return this->toUpperCase();
}

Var Var::toLowerCase() const
{
	var result;

	if (this->internal_type == Var::string)
	{
		result = this->internal_string;

		int length = result.internal_string.length();

		for (int i = 0; i < length; i++)
		{
			if (65 <= result.internal_string[i] && result.internal_string[i] <= 90) {
				result.internal_string[i] += 32;
			}
		}
	}

	return result;
}

Var Var::toUpperCase() const
{
	var result;

	if (this->internal_type == Var::string)
	{
		result = this->internal_string;

		int length = result.internal_string.length();

		for (int i = 0; i < length; i++)
		{
			if (97 <= result.internal_string[i] && result.internal_string[i] <= 122) {
				result.internal_string[i] -= 32;
			}
		}
	}

	return result;
}

Var Var::trim() const
{
	var result;

	if (this->internal_type == Var::string)
	{
		result = this->internal_string;

		int blankLength = 0;

		while
		(
			result.internal_string[blankLength] == ' '  ||
			result.internal_string[blankLength] == '\n' ||
			result.internal_string[blankLength] == '\t'
		) {
			blankLength++;
		}

		result.internal_string.erase(0, blankLength);

		blankLength = result.internal_string.length() -1;

		if (blankLength >0)
		{
			while
			(
				result.internal_string[blankLength] == ' '  ||
				result.internal_string[blankLength] == '\n' ||
				result.internal_string[blankLength] == '\t'
			) {
				blankLength--;
			}

			result.internal_string.erase(blankLength+1);
		}
	}

	return result;
}

Var Var::join(const Var& separator)
{
		unsigned length = 0;
		std::string glue_cpp = separator.toString();
		std::string ret_cpp;
		Var it;

		for (it = (*this).begin(); it != (*this).end(); it++) {
			length += (*it).size();
		}

		length += separator.size() * (*this).size();
		ret_cpp.reserve(length);

		it = (*this).begin();

		while (true)
		{
			if (Var::type(*it) != Var::map && Var::type(*it) != Var::vector) {
				ret_cpp += (*it).toString();
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

Var Var::pop()
{
	var result;

	if (this->internal_type == Var::vector)
	{
		result = *(this->internal_vector[this->internal_vector.size()-1]);

		delete this->internal_vector[this->internal_vector.size()-1];
		this->internal_vector.pop_back();
	}

	return result;
}

Var Var::reverse()
{
	if (this->internal_type == Var::vector)
	{
		Var* temp = NULL;
		size_t lastIndex = this->internal_vector.size() - 1;

		for (size_t i = 0; i <= (lastIndex-i); i++)
		{
			temp = this->internal_vector[i];
			this->internal_vector[i] = this->internal_vector[lastIndex - i];
			this->internal_vector[lastIndex - i] = temp;
		}
	}

	return Var();
}

Var Var::shift()
{
	var result;

	if (this->internal_type == Var::vector)
	{
		result = *(this->internal_vector[0]);
		delete this->internal_vector[0];
		this->internal_vector.erase(this->internal_vector.begin());
	}

	return result;
}

Var Var::sort()
{
	var result;

	if (this->internal_type == Var::vector) {
		std::sort(this->internal_vector.begin(), this->internal_vector.end(), Var::_sort);
	}

	return result;
}

std::string Var::toString() const
{
	std::string result;
	char* buffer = NULL;

	switch (this->internal_type)
	{
		case Var::null:
			return "";

		case Var::boolean:
			return this->internal_bool ? "true" : "false";

		case Var::string:
			return this->internal_string.c_str();

		case Var::integer:
			buffer = (char*)malloc(32);
			sprintf(buffer,"%ld", this->internal_long);
			break;

		case Var::real:
			buffer = (char*)malloc(32);
			sprintf(buffer,"%f", this->internal_double);
			break;

		default:
			buffer = (char*)malloc(32);
			sprintf(buffer,"0");
			break;
	}

	result = buffer;
	free(buffer);

	return result;
}

bool Var::compare(const Var& that) const
{
	if (this->internal_type != that.internal_type) {
		return false;
	}

	return (*this == that);
}

bool Var::in(Var& that)
{
	switch(that.internal_type)
	{
		case Var::map:
		{
			Var::internal_map_type::iterator i;

			if (this->internal_type == null)
			{
				i = that.internal_map.begin();

				if (i != that.internal_map.end())
				{
					*this = i->first;
					return true;
				}
			}
			else
			{
				i = that.internal_map.find(this->toString());

				if (i != that.internal_map.end())
				{
					i++;
					if (i != that.internal_map.end())
					{
						*this = i-> first;
						return true;
					}
				}
			}
		}
		break;

		case Var::vector:
		{
			if (this->internal_type == null)
			{
				*this = 0;
				if (that.internal_vector.size() != 0) {
					return true;
				}
			}
			else
			if (this->internal_type == Var::integer)
			{
				if (this->internal_long >= 0 && this->internal_long < (long)that.internal_vector.size())
				{
					if (this->internal_long + 1 < (long)that.internal_vector.size())
					{
						this->internal_long++;
						return true;
					}
				}
			}
		}
		break;

		default:
		break;
	}

	return false;
}

Var Var::key()
{
	switch (this->internal_type)
	{
		case Var::map_iterator:
			return (Var&) this->internal_map_iterator->first;

		case Var::vector_iterator:
			return this->internal_long;
	}

	return (Var&) *this;
}

Var& Var::operator *()
{
	switch (this->internal_type)
	{
		case Var::map_iterator:
			return (Var&) *this->internal_map_iterator->second;

		case Var::vector_iterator:
			return (Var&) **this->internal_vector_iterator;
	}

	return (Var&) *this;
}

Var Var::begin()
{
	Var result;

	switch (this->internal_type)
	{
		case Var::map:
			result.internal_map_iterator = this->internal_map.begin();
			result.internal_type = Var::map_iterator;
			return result;

		case Var::vector:
			result.internal_long = 0;
			result.internal_vector_iterator =  this->internal_vector.begin();
			result.internal_type = Var::vector_iterator;
			return result;
	}

	return 0;
}

Var Var::end()
{
	Var result;

	switch (this->internal_type)
	{
		case Var::map:
			result.internal_map_iterator = this->internal_map.end();
			result.internal_type = Var::map_iterator;
			return result;

		case Var::vector:
			result.internal_long = this->internal_vector.size();
			result.internal_vector_iterator = this->internal_vector.end();
			result.internal_type = Var::vector_iterator;
			return result;
	}

	return 0;
}

unsigned long Var::size() const
{
	switch (this->internal_type)
	{
		case Var::string:
			return this->internal_string.length();

		case Var::map:
			return this->internal_map.size();

		case Var::vector:
			return this->internal_vector.size();
	}

	return 0;
}

Var Var::num() const
{
	Var result;
	switch (this->internal_type)
	{
		case Var::string:
			result.internal_double = atof(this->internal_string.c_str());
			result.internal_long = (long)result.internal_double;
			result.internal_type = (result.internal_double == result.internal_long) ? Var::integer : Var::real;
			break;

		case Var::integer:
			result.internal_long = this->internal_long;
			result.internal_type = Var::integer;
			break;

		case Var::real:
			result.internal_double = this->internal_double;
			result.internal_type = Var::real;
			break;

		case Var::null:
			result.internal_long = 0;
			result.internal_type = Var::integer;
			break;
	}

	return result;
}

Var::operator bool() const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			return this->internal_bool;

		case Var::string:
			return atof(this->internal_string.c_str()) ? true : false;

		case Var::integer:
			return this->internal_long ? true : false;

		case Var::real:
			return this->internal_double ? true : false;

		case Var::map:
			return !this->internal_map.empty();

		case Var::vector:
			return !this->internal_vector.empty();

		case Var::resource:
			return this->internal_resource ? true : false;
	}

	return false;
}

Var::operator long() const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			return this->internal_bool ? 1 : 0;

		case Var::string:
			return (long)atof(this->internal_string.c_str());

		case Var::integer:
			return this->internal_long;

		case Var::real:
			return (long)this->internal_double;
	}

	return 0;
}

Var::operator double() const
{
	switch (this->internal_type)
	{
		case Var::boolean:
			return this->internal_bool ? 1 : 0;

		case Var::string:
			return atof(this->internal_string.c_str());

		case Var::integer:
			return (double)this->internal_long;

		case Var::real:
			return this->internal_double;
	}

	return 0;
}

Var::operator void *() const
{
	if (this->internal_type == Var::resource) {
		return this->internal_resource;
	} else {
		return NULL;
	}
}

std::string Var::encode() const
{
	std::string result;
	unsigned int pos = 0;

	switch (this->internal_type)
	{
		case Var::boolean:
		case Var::integer:
		case Var::real:
			return this->toString();

		case Var::string:
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

					case '\b':
						result.replace(pos++, 1, "\\b");
						break;

					case '\f':
						result.replace(pos++, 1, "\\f");
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

		case Var::map:
			if (this->internal_map.size() > 0)
			{
				result = "{";

				for (Var::internal_map_type::const_iterator it = this->internal_map.begin(); it != this->internal_map.end(); it++) {
					result = result + Var(it->first).encode() + ":" + (it->second->encode()) + ",";
				}

				result[result.size()-1] = '}';

				return result;
			}
			else {
				return "{}";
			}

		case Var::vector:
			if (this->internal_vector.size() > 0)
			{
				result = "[";

				for (unsigned i = 0; i < this->internal_vector.size(); i++) {
					result += (this->internal_vector[i]->encode() + ",");
				}

				result[result.size()-1] = ']';

				return result;
			} else {
				return "[]";
			}

		case Var::resource:
			return "\"(resource)\"";

		default:
			return "null";
	}

	return result;
}

void Var::decodeSub(const std::string& data, unsigned& i, Var& value)
{
	value.clear();

	for (; i < data.length(); i++)
	{
		while (data[i] == ' ') i++;

		if ( (data[i] >= '0' && data[i] <= '9') || data[i] == '-') /* [-0-9] */
		{
			Var::decodeNumber(data, i, value.internal_double);

			if (ceil(value.internal_double) == (floor(value.internal_double)))
			{
				value.internal_long = value.internal_double;
				value.internal_type = Var::integer;
			}
			else {
				value.internal_type = Var::real;
			}

			return;
		}

		if ((data[i] >= 'a' && data[i] <= 'z') || (data[i] >= 'A' && data[i] <= 'Z') || data[i] == '$'|| data[i] == '_') /* [_a-zA-Z] */
		{
			Var::decodeSymbol(data, i, value.internal_string);

			if (value.internal_string == "null")
			{
				value.internal_string.clear();
				value.internal_type = Var::null;

				return;
			}

			if (value.internal_string == "true")
			{
				value.internal_string.clear();
				value.internal_type = Var::boolean;
				value.internal_bool = true;

				return;
			}

			if (value.internal_string == "false")
			{
				value.internal_string.clear();
				value.internal_type = Var::boolean;
				value.internal_bool = false;

				return;
			}

			value.internal_type = Var::string;

			return;
		}

		if (data[i] == '"')
		{
			Var::decodeString(data, i, value.internal_string);
			value.internal_type = Var::string;

			return;
		}

		switch (data[i])
		{
			case '[':
			case '(':
				value.internal_type = Var::vector;
				Var::decodeVector(data, i, value.internal_vector);
				return;

			case '{':
				value.internal_type = Var::map;
				Var::decodeMap(data, i, value.internal_map);
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

inline void Var::decodeNumber(const std::string& data, unsigned& i, double& value)
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

inline void Var::decodeSymbol(const std::string& data, unsigned& i, std::string& value)
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

inline void Var::decodeString(const std::string& data, unsigned& i, std::string& value)
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

				case 'b':
					value.replace(j, 2, "\b");
					break;

				case 'f':
					value.replace(j, 2, "\f");
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

inline void Var::decodeVector(const std::string& data, unsigned& i, Var::internal_vector_type& value)
{
	std::list<Var> VarList;
	i++;
	for (; i < data.length(); i++)
	{
		while (data[i] == ',' || data[i] == ' ' || data[i] == '\n' || data[i] == '\r' || data[i] == '\t') i++; /* [,\s]* */

		if (data[i] == ']' || data[i] == ')')
		{
			value.resize(VarList.size());

			unsigned j = 0;
			for (std::list<Var>::iterator it = VarList.begin(); it != VarList.end(); it++)
			{
				value[j] = new Var(*it);
				j++;
			}

			return;
		}

		VarList.push_back(Var());
		decodeSub(data, i, *(VarList.rbegin()));
	}
}

inline void Var::decodeMap(const std::string& data, unsigned& i, Var::internal_map_type& value)
{
	i++;
	Var mapKey;
	Var* mapValue = NULL;
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


		mapValue = new Var();
		decodeSub(data, i, *mapValue);

		value[mapKey.toString()] = mapValue;
	}
}

bool Var::_sort(const Var* a, const Var* b)
{
	return *(a) < *(b);
}

void Var::_push(const Var& item)
{
	if (this->internal_type != Var::vector)
	{
		this->clear();
		this->internal_type = Var::vector;
	}

	this->internal_vector.push_back(new var(item));
}

Var Var::_splice(const Var& index, const Var& howmany, const Var& items)
{
	unsigned long i = 0;
	unsigned long begin = (long)index;
	unsigned long length = (long)howmany;

	begin = begin < 0 ? begin + this->internal_vector.size(): begin;
	begin = begin < 0 ? 0 : begin;
	begin = begin > this->internal_vector.size()? this->internal_vector.size() : begin;

	for (i = begin; i < length; i++) {
		delete this->internal_vector[i];
	}

	this->internal_vector.erase(this->internal_vector.begin() + i, this->internal_vector.begin() + i + length);

	this->internal_vector.insert(this->internal_vector.begin() + i, (long)items.size(), NULL);

	for (i = 0; i < items.size(); i++) {
		this->internal_vector[i+begin] = new Var(*(items.internal_vector[i]));
	}

	return Var();
}

Var& Var::decode(const Var& json)
{
	this->clear();

	if (json.internal_type != Var::string) {
		return *this;
	}

	unsigned i = 0;
	Var::decodeSub(json.internal_string, i, *this);

	return *this;
}

Var Var:: operator +(int a) const { return operator +(Var(a)); }
Var Var:: operator +(const char* a) const { return operator +(Var(a)); }
Var Var:: operator -(int a) const { return operator -(Var(a)); }
bool Var:: operator ==(bool a) const { return operator ==(Var(a)); }
bool Var:: operator ==(int a) const{ return operator ==(Var(a)); }
bool Var:: operator ==(float a) const { return operator ==(Var(a)); }
bool Var:: operator ==(double a) const { return operator ==(Var(a)); }
bool Var:: operator ==(const char* a) const { return operator ==(Var(a)); }
bool Var:: operator !=(int a) const { return operator !=(Var(a)); }
bool Var:: operator !=(const char* a) const { return operator !=(Var(a)); }
bool Var:: operator <(unsigned int a) const { return operator <(Var(a));}
Var& Var:: operator [](int a) { return operator[](Var(a)); }
Var& Var:: operator [](const char* a) { return operator[](std::string(a)); }
Var& Var:: operator <<(int a) { return operator<<(Var(a)); }


int Var::type(const Var& that) {
	return that.internal_type;
}

int Var::exists(const Var& haystack, const Var& needle)
{
	unsigned size = 0;
	switch (haystack.internal_type)
	{
		case Var::map:

			for (Var::internal_map_type::const_iterator iterador = haystack.internal_map.begin(); iterador != haystack.internal_map.end(); iterador++)
			{
				if ((iterador->first).compare(needle.toString())) {
					return 1;
				}
			}

		break;

		case Var::vector:
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
