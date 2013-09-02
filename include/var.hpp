#ifndef CPP_VAR
#define CPP_VAR

#include <string>
#include <list>
#include <vector>

enum {
	VAR_NULL,
	VAR_BOOLEAN,
	VAR_INTEGER,
	VAR_FLOAT,
	VAR_STRING,
	VAR_MAP,
	VAR_MAP_ITERATOR,
	VAR_VECTOR,
	VAR_VECTOR_ITERATOR,
	VAR_RESOURCE
};

class var {
	public:
		typedef std::list < std::pair<var, var> > internal_map_type;
		typedef std::vector <var> internal_vector_type;

	private:
		unsigned	internal_type;

		bool		internal_bool;
		long		internal_long;
		double		internal_double;
		std::string	internal_string;
		void*		internal_resource;

		internal_map_type internal_map;
		internal_map_type::iterator internal_map_iterator;

		internal_vector_type internal_vector;
		internal_vector_type::iterator internal_vector_iterator;

		var num() const;

	public:
		var();

		var(const bool&);
		var(const int&);
		var(const unsigned int&);
		var(const long&);
		var(const double&);

		var(const char*);
		var(const std::string&);
		var(void*);

		void clear();

		var operator =(const var&);

		var operator +(const var&);
		var operator -(const var&);
		var operator *(const var&);
		var operator /(const var&);

		var operator ++(int);
		var operator --(int);

		bool operator ==(const var&);
		bool operator !=(const var&);

		bool operator <(const var&);
		bool operator >(const var&);
		bool operator &&(const var&);
		bool operator ||(const var&);

		long operator &(const var&);
		long operator |(const var&);

		var& operator [](const var&);

		var& operator <<(const var&);

		var operator +(const int&);
		var operator +(const char*);
		bool operator ==(const bool&);
		bool operator ==(const int&);
		bool operator ==(const float&);
		bool operator ==(const double&);
		bool operator ==(const char*);
		bool operator !=(const int&);
		bool operator !=(const char*);
		bool operator <(unsigned int);
		var& operator [](const int&);
		var& operator [](const char*);

		bool compare(const var& param);

		bool fetch(var& key, var& value);

		var key();
		var& operator *();

		var begin();
		var end();

		long size() const;

		friend int var_type(const var&);

		operator bool() const;
		operator int() const;
		operator long() const;
		operator double() const;
		operator const char*() const;
		operator void *() const;
		std::string cpp_string() const;
		internal_map_type& cpp_map();
		internal_vector_type& cpp_vector();

		std::string encode();
		int decode(std::string);
};

var operator+(char* a, var b);
var operator+(const char* a, var b);

int var_type(const var&);


#endif /* CPP_VAR */
