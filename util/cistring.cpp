
#include <cctype>
#include <string>

#include "cistring.h"


bool ci_char_traits::eq(char c1, char c2) {
	return std::toupper(c1) == std::toupper(c2);
}

bool ci_char_traits::ne(char c1, char c2) {
	return std::toupper(c1) != std::toupper(c2);
}

bool ci_char_traits::lt(char c1, char c2) {
	return std::toupper(c1) < std::toupper(c2);
}


int ci_char_traits::compare(const char* s1, const char* s2, size_t n) {
	while( n-- != 0 ) {
		if( ci_char_traits::lt(*s1, *s2) )
			return -1;

		if( ci_char_traits::ne(*s1, *s2) )
			return 1;

		++s1;
		++s2;
	}

	return 0;
}

const char* ci_char_traits::find(const char* s, int n, char a) {
	while( n-- > 0 && ci_char_traits::ne(*s, a) ) {
		++s;
	}

	return s;
}
