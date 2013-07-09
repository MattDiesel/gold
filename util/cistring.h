

#include <string>


struct ci_char_traits : public std::char_traits<char> {
	static bool eq(char, char);
	static bool ne(char, char);
	static bool lt(char, char);
	static int compare(const char*, const char*, size_t);
	static const char* find(const char*, int, char);
};

typedef std::basic_string<char, ci_char_traits> cistring;
