#ifndef STRING_H
#define STRING_H

#include <string>

template<class T>
bool isEqual(T begin1, T end1, T begin2){
	for(; begin1 != end1; ++begin1, ++begin2){
		if(*begin1 != *begin2)
			return false;
	}
	return true;
}

inline bool hasSubstring(const string& str, const string& pat){
	for(string::const_iterator it = str.begin(); it != str.end() - pat.size(); ++it){
		if(isEqual(it, it + pat.size(), pat.begin()))
			return true;
	}
	return false;
}

#endif
