#ifndef HEADER_CELL
#define HEADER_CELL

#include <fstream>
#include "../Generic/String/String.h"

class Cell {
public:
	virtual String getValueForPrint() = 0;
	virtual void parseAndSetValue(const char* str) = 0;
	virtual void readFromFile(std::ifstream& filePath) = 0;
	virtual void saveToFile(const char* filePath) = 0;

	virtual ~Cell() = default;
};

#endif
