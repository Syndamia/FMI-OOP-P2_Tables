#ifndef HEADER_STRING
#define HEADER_STRING

/*! \file String.h
 *  \brief Stores declaration of class String
 */

#include <istream>
#include <ostream>

#define DOUBLE_PRECISION 100

/*! \brief A dynamically-allocated C-style string with extra features
 *
 * \remark There is no buffer allocation, meaning each String takes only the amount of memory it needs and every append operation juggles around memory.
 */
class String {
	char* str;
	unsigned length;

	void free();
	void copyFrom(const String& other);

public:
	//! The underlying array is allocated with length (+ 1) size
	String(unsigned length);
	//! Copies str
	String(const char* str);
	//! Returns internal C-style string
	const char* get_cstr() const;
	//! Returns number of characters in string
	unsigned get_length() const;
	//! Returns a character reference (from the underlying C-style string) at the given index
	char& operator[](unsigned index);

	//! Appends a C-style string
	String& operator+=(const char* str);
	//! Appends a number
	String& operator+=(int number);
	//! Appends a number
	String& operator+=(unsigned number);
	//! Appends a number
	String& operator+=(double number);

	String();
	String(const String& other);
	String& operator=(const String& other);
	~String();

	String(String&& other);
	String& operator=(String&& other);

	//! Reads String from stream
	void read(std::istream& istr);
	//! Writes String to stream
	void write(std::ostream& ostr) const;
	//! Compares two strings
	int compare(const String& other) const;

	//! Reads String from stream with >> operator
	friend std::istream& operator>>(std::istream& istr, String& str);
	//! Writes String to stream with << operator
	friend std::ostream& operator<<(std::ostream& ostr, const String& str);
};

#endif
