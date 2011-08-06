#ifndef CPP_VAR
#define CPP_VAR

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
		typedef list < pair<var, var> > internal_map_type;

	private:
		unsigned type;

		bool	internal_bool;
		long	internal_long;
		double	internal_double;
		string	internal_string;
		void*	internal_resource;

		internal_map_type internal_map;

		var num();

	public:
		var();

		var(bool);
		var(int);
		var(long);
		var(double);

		var(const char*);
		var(string);
		var(void*);

		void reset();

		var operator =(var);

		var operator +(var);
		var operator -(var);
		var operator *(var);
		var operator /(var);

		bool operator ==(var);

		bool operator <(var);
		bool operator >(var);
		bool operator &&(var);
		bool operator ||(var);

		long operator &(var);
		long operator |(var);

		var& operator [](var);
		var& operator <<(var);

		long c_long();
		double c_double();
		string cpp_string();
		internal_map_type& cpp_map();
};

#endif