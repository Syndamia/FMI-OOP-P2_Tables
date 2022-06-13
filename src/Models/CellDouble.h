#ifndef HEADER_CELLDOUBLE
#define HEADER_CELLDOUBLE

#include "Cell.h"

class CellDouble : public Cell {
	double value;

public:
	CellDouble() = default;
	CellDouble(double value);
	CellDouble(const char* str);

	double getNumeralValue() const override;
	String getValueForPrint() const override;
	void parseAndSetValue(const char* str) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
