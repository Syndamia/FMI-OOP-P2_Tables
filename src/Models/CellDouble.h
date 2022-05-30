#ifndef HEADER_CELLDOUBLE
#define HEADER_CELLDOUBLE

#include "Cell.h"

class CellDouble : public Cell {
	double value;

public:
	CellDouble() = default;
	CellDouble(double value);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
