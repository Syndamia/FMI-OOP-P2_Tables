#ifndef HEADER_CELLINT
#define HEADER_CELLINT

#include "Cell.h"

class CellInt : public Cell {
	int value;

public:
	CellInt() = default;
	CellInt(int value);
	CellInt(const char* str);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
