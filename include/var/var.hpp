#ifndef __CPP_VAR__
#define __CPP_VAR__

#include <string>
#include <map>
#include <vector>

class Var;
class Var
{
	public:
		enum Var_t
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

		static int type(const Var& that);
		static int exists(const Var& haystack, const Var& needle);


	private:
		unsigned	internal_type;

		bool		internal_bool;
		long		internal_long;
		double		internal_double;
		std::string	internal_string;
		void*		internal_resource;

		typedef std::map <std::string, Var*> internal_map_type;
		typedef std::vector <Var*> internal_vector_type;

		internal_map_type internal_map;
		internal_map_type::iterator internal_map_iterator;

		internal_vector_type internal_vector;
		internal_vector_type::iterator internal_vector_iterator;

		Var num() const;

		static void decodeSub(const std::string& data, unsigned& i, Var& value);
		static void decodeNumber(const std::string& data, unsigned& i, double& value);
		static void decodeSymbol(const std::string& data, unsigned& i, std::string& value);
		static void decodeString(const std::string& data, unsigned& i, std::string& value);
		static void decodeVector(const std::string& data, unsigned& i, internal_vector_type& value);
		static void decodeMap(const std::string& data, unsigned& i, internal_map_type& value);


	public:
		Var();
		Var(Var_t);
		Var(const Var&);

		Var(bool);
		Var(int);
		Var(unsigned int);
		Var(long);
		Var(double);

		Var(const char*);
		Var(const std::string&);
		Var(void*);
		~Var();

		std::string encode() const;
		Var& decode(const Var& json);

		Var& operator =(const Var&);

		Var operator +(const Var&) const;
		Var operator -(const Var&) const;
		Var operator *(const Var&) const;
		Var operator /(const Var&) const;

		Var& operator ++(int);
		Var& operator --(int);

		bool operator ==(const Var&) const;
		bool operator !=(const Var&) const;

		bool operator <(const Var&) const;
		bool operator >(const Var&) const;
		bool operator &&(const Var&) const;
		bool operator ||(const Var&) const;

		long operator &(const Var&);
		long operator |(const Var&);

		Var& operator [](const Var&);

		Var& operator <<(const Var&);

		Var split(const Var& separator);
		Var join(const Var& separator);

		std::string toString() const;

		bool compare(const Var& that) const;

		Var key();
		Var& operator *();

		Var begin();
		Var end();

		unsigned long size() const;
		void clear();

		operator bool() const;
		operator long() const;
		operator double() const;
		inline operator const char*() const { return this->toString().c_str(); }
		operator void *() const;


		Var operator +(int) const;
		Var operator +(const char*) const;
		bool operator ==(bool) const;
		bool operator ==(int) const;
		bool operator ==(float) const;
		bool operator ==(double) const;
		bool operator ==(const char*) const;
		bool operator !=(int) const;
		bool operator !=(const char*) const;
		bool operator <(unsigned int) const;
		Var& operator [](int);
		Var& operator [](const char*);
		Var& operator <<(int);

};

inline Var operator+(char* a, const Var& b) {
	return Var((char*)a) + b;
}
inline Var operator+(const char* a, const Var& b) {
	return Var(a) + b;
}

typedef Var var;

#endif /* __CPP_VAR__ */
