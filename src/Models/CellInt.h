#ifndef HEADER_CELLINT
#define HEADER_CELLINT

#include "Cell.h"

class CellInt : public Cell<int> {
	int value;

public:
	CellInt() = default;

	int getValue() override;
	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
