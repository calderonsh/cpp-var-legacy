#ifndef CPP_VAR
#define CPP_VAR

#include <string>
#include <list>

enum {
	VAR_NULL,
	VAR_BOOLEAN,
	VAR_INTEGER,
	VAR_FLOAT,
	VAR_STRING,
	VAR_MAP,
	VAR_RESOURCE
};

class var {
	public:
		typedef std::list < std::pair<var, var> > internal_map_type;

	private:
		unsigned type;

		bool		internal_bool;
		long		internal_long;
		double		internal_double;
		std::string	internal_string;
		void*		internal_resource;

		internal_map_type internal_map;

		var num() const;

	public:
		var();

		var(const bool&);
		var(const int&);
		var(const long&);
		var(const double&d);

		var(const char*);
		var(const std::string&);
		var(void*);

		void reset();

		var operator =(const var&);

		var operator +(const var&);
		var operator -(const var&);
		var operator *(const var&);
		var operator /(const var&);

		bool operator ==(const var&);

		bool operator <(const var&);
		bool operator >(const var&);
		bool operator &&(const var&);
		bool operator ||(const var&);

		long operator &(const var&);
		long operator |(const var&);

		var& operator [](const var&);
		var& operator <<(const var&);

		long c_long() const;
		double c_double() const;
		std::string cpp_string() const;
		internal_map_type& cpp_map();

};

#endif
