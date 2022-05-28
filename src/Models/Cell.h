#ifndef HEADER_CELL
#define HEADER_CELL

#include "../Generic/String/String.h"

class Cell {
public:
	virtual String getValueForPrint() = 0;
	virtual void parseAndSetValue(const char* str) = 0;
	virtual void readFromFile(const char* filePath) = 0;
	virtual void saveToFile(const char* filePath) = 0;
};

#endif
