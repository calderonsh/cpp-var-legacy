#ifndef __CPP_VAR__
#define __CPP_VAR__

#include <string>
#include <map>
#include <vector>

class var;
class var
{
	public:
		enum var_t
		{
			null,
			boolean,
			integer,
			real,
			symbol,
			string,
			map,
			map_iterator,
			vector,
			vector_iterator,
			resource
		};

		static int type(const var& that);
		static int exists(const var& haystack, const var& needle);


	private:
		unsigned	internal_type;

		bool		internal_bool;
		long		internal_long;
		double		internal_double;
		std::string	internal_string;
		void*		internal_resource;

		typedef std::map <std::string, var*> internal_map_type;
		typedef std::vector <var*> internal_vector_type;

		internal_map_type internal_map;
		internal_map_type::iterator internal_map_iterator;

		internal_vector_type internal_vector;
		internal_vector_type::iterator internal_vector_iterator;

		var num() const;

		static void decodeSub(const std::string& data, unsigned& i, var& value);
		static void decodeNumber(const std::string& data, unsigned& i, double& value);
		static void decodeSymbol(const std::string& data, unsigned& i, std::string& value);
		static void decodeString(const std::string& data, unsigned& i, std::string& value);
		static void decodeVector(const std::string& data, unsigned& i, internal_vector_type& value);
		static void decodeMap(const std::string& data, unsigned& i, internal_map_type& value);


	public:
		var();
		var(var_t);
		var(const var&);

		var(bool);
		var(int);
		var(unsigned int);
		var(long);
		var(double);

		var(const char*);
		var(const std::string&);
		var(void*);
		~var();

		std::string encode() const;
		var& decode(const var& json);

		var& operator =(const var&);

		var operator +(const var&) const;
		var operator -(const var&) const;
		var operator *(const var&) const;
		var operator /(const var&) const;

		var& operator ++(int);
		var& operator --(int);

		bool operator ==(const var&) const;
		bool operator !=(const var&) const;

		bool operator <(const var&) const;
		bool operator >(const var&) const;
		bool operator &&(const var&) const;
		bool operator ||(const var&) const;

		long operator &(const var&);
		long operator |(const var&);

		var& operator [](const var&);

		var& operator <<(const var&);

		var split(const var& separator);
		var join(const var& separator);

		std::string toString() const;

		bool compare(const var& that) const;

		var key();
		var& operator *();

		var begin();
		var end();

		unsigned long size() const;
		void clear();

		operator bool() const;
		operator long() const;
		operator double() const;
		inline operator const char*() const { return this->toString().c_str(); }
		operator void *() const;


		var operator +(int) const;
		var operator +(const char*) const;
		bool operator ==(bool) const;
		bool operator ==(int) const;
		bool operator ==(float) const;
		bool operator ==(double) const;
		bool operator ==(const char*) const;
		bool operator !=(int) const;
		bool operator !=(const char*) const;
		bool operator <(unsigned int) const;
		var& operator [](int);
		var& operator [](const char*);
		var& operator <<(int);

};

inline var operator+(char* a, const var& b) {
	return var((char*)a) + b;
}
inline var operator+(const char* a, const var& b) {
	return var(a) + b;
}

typedef var var;

#endif /* __CPP_VAR__ */
