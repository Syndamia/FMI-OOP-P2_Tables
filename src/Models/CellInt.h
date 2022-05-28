#ifndef HEADER_CELLINT
#define HEADER_CELLINT

#include "Cell.h"

class CellInt : public Cell {
	int value;

public:
	CellInt() = default;

	double getNumeralValue() override;
	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
