#pragma once

#include <string> 
#include <sstream> 

template<class Char>
class imatch
{
	const Char* s;
public:
	imatch(const Char* x) :s(x) {}

	template<class Stream>
	friend Stream& operator >> (Stream& st, const imatch& m)
	{
		std::basic_string<Char> x;
		st >> x; //strip spaces, read chars up to space 
		if (x != m.s) st.setstate(st.failbit); //set as "failure" a mismatch 
		return st;
	}
};