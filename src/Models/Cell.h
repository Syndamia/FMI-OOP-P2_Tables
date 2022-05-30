#ifndef HEADER_CELL
#define HEADER_CELL

#include <fstream>
#include "../Generic/String/String.h"

class Cell {
public:
	virtual double getNumeralValue() const = 0;
	virtual String getValueForPrint() const = 0;
	virtual void parseAndSetValue(const char* str) = 0;
	virtual void writeToFile(std::ofstream& file) = 0;

	virtual ~Cell() = default;
};

#endif
