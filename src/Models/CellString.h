#ifndef HEADER_CELLSTRING
#define HEADER_CELLSTRING

#include "Cell.h"

class CellString : public Cell<String> {
	String value;

public:
	CellString() = default;

	String getValue() override;
	String getValueForPrint() override;
	void parseAndSetValue(const char* str) override;
	void readFromFile(std::ifstream& file) override;
	void writeToFile(std::ofstream& file) override;
};

#endif
