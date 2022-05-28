#ifndef HEADER_CELLSTRING
#define HEADER_CELLSTRING

#include "Cell.h"

class CellString : public Cell {
	String value;

public:
	CellString() = default;

	double getNumeralValue() override;
	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
