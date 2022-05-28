#ifndef HEADER_CELLDOUBLE
#define HEADER_CELLDOUBLE

#include "Cell.h"

class CellDouble : public Cell<double> {
	double value;

public:
	CellDouble() = default;
	CellDouble(int val);
	CellDouble(String str);

	double getValue() override;
	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
