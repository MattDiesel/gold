
#include <string>
#include <istream>


#ifndef UTIL_IPOSSTREAM_H
#define UTIL_IPOSSTREAM_H


// Represents a position within a file.
struct SourcePos {
	// std::string& File;
	int Line;
	int Column;
	int Abs;
	int LineStart;

	SourcePos();
	SourcePos(int, int, int);
	SourcePos(int, int, int, int);

	friend std::ostream& operator<<(std::ostream&, const SourcePos&);
};


// An input stream that also records character positions.
// Todo: Make this into a fully featured stream class derived from std::istream
class iposstream
{
public:
	iposstream(std::istream&);
	~iposstream();

	int peek();
	int get();
	bool eof();

	SourcePos Pos;
	int TabWidth;

private:
	std::istream& basestream;
	SourcePos next;
};


#endif
